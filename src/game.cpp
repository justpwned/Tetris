#include <iostream>
#include <time.h>

#include "game.hpp"
#include "palette.hpp"

using namespace core;
using namespace core::graphics;
using namespace core::gameplay;

Game::Game(const char *t_title, i32 t_xPos, i32 t_yPos, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName, i32 t_fontSize)
{
    if (!SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "SDL has been initialized successfully\n";
        
        m_window = SDL_CreateWindow(t_title, t_xPos, t_yPos, t_windowWidth,
                                    t_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        
        if (m_window)
        {
            std::cout << "SDL window has been created successfully\n";
            
            m_renderer = SDL_CreateRenderer(m_window, -1, 
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            
            if (m_renderer)
            {
                std::cout << "SDL renderer has been created successfully\n";
            }
            else
            {
                std::cerr << "Renderer could not be created. SDL error: " 
                    << SDL_GetError() << "\n";
                exit(1);
            }
        }
        else
        {
            std::cerr << "Window could not be created. SDL error: " << SDL_GetError() << "\n";
            exit(1);
        }
    }
    else
    {
        std::cerr << "Unable to intialize SDL. SDL error: " << SDL_GetError() << "\n";
        exit(1);
    }
    
    if (!TTF_Init())
    {
        std::cout << "SDL_TTF has been initialized successfully\n";
        
        m_font = TTF_OpenFont(t_fontName, t_fontSize);
        
        if (m_font)
        {
            std::cout << "Font " << t_fontName << "(" << t_fontSize 
                << ") has been loaded\n";
        }
        else
        {
            std::cerr << "Font " << t_fontName << "(" << t_fontSize 
                << ") has not been loaded\n";
            exit(1);
        }
    }
    else
    {
        std::cerr << "Unable to initialize SDL_TTF. SDL_TTF error: " << TTF_GetError() << "\n";
        exit(1);
    }
    
    m_gameWidth = t_windowWidth;
    m_gameHeight = t_windowHeight;
    m_running = true;
    
    Graphics::Instance()->SetRenderer(m_renderer);
    
    m_game = {};
    m_game.board = new gameplay::Board(BOARD_ROWS, BOARD_COLS, BOARD_VISIBLE_ROWS, BOARD_GRID_SIZE);
    
    m_game.piece = new gameplay::Piece(m_game.board, &m_game.time, &m_game.stats, 0, 0, 0, 0);
    
    m_input = {};
    
    srand((u32)time(NULL));
}

void Game::HandleEvents()
{
    m_game.time.time = SDL_GetTicks() / 1000.0f;
    
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            Quit();
        }
    }
}

void Game::HandleInput()
{
    i32 keyCount;
    const u8 *keyStates = SDL_GetKeyboardState(&keyCount);
    
    if (keyStates)
    {
        if (keyStates[SDL_SCANCODE_ESCAPE])
        {
            Quit();
        }
        
        InputState prevInput = m_input;
        
        m_input.left   = keyStates[SDL_SCANCODE_LEFT];
        m_input.right  = keyStates[SDL_SCANCODE_RIGHT];
        m_input.up     = keyStates[SDL_SCANCODE_UP];
        m_input.down   = keyStates[SDL_SCANCODE_DOWN];
        m_input.space  = keyStates[SDL_SCANCODE_SPACE];
        m_input.enter  = keyStates[SDL_SCANCODE_RETURN];
        m_input.z      = keyStates[SDL_SCANCODE_Z];
        
        m_input.dleft  = m_input.left - prevInput.left;
        m_input.dright = m_input.right - prevInput.right;
        m_input.dup    = m_input.up - prevInput.up;
        m_input.ddown  = m_input.down - prevInput.down;
        m_input.dspace = m_input.space - prevInput.space;
        m_input.denter = m_input.enter - prevInput.enter;
        m_input.dz      = m_input.z - prevInput.z;
    }
}

void Game::UpdateGameStart()
{
    if (m_input.dup > 0)
    {
        ++m_game.stats.startLevel;
    }
    
    if (m_input.ddown > 0 && m_game.stats.startLevel > 0)
    {
        --m_game.stats.startLevel;
    }
    
    if (m_input.denter > 0)
    {
        m_game.board->Clear();
        m_game.stats.level = m_game.stats.startLevel;
        m_game.stats.lineCount = 0;
        m_game.stats.points = 0;
        m_game.piece->SpawnNewPiece();
        m_game.phase = GAME_PHASE_PLAY;
    }
    
}

void Game::UpdateGamePlay()
{
    Piece piece = *(m_game.piece);
    
    if (m_input.dleft > 0)
    {
        piece.SetColOffset(piece.GetColOffset() - 1);
    }
    
    if (m_input.dright > 0)
    {
        piece.SetColOffset(piece.GetColOffset() + 1);
    }
    
    if (m_input.dup > 0)
    {
        piece.SetRotation(piece.GetRotation() + 1);
    }
    
    if (piece.IsValid())
    {
        *(m_game.piece) = piece;
    }
    
    if (m_input.ddown > 0)
    {
        m_game.piece->SoftDrop();
    }
    
    if (m_input.dz > 0)
    {
        m_game.piece->HardDrop();
    }
    
    while (m_game.time.time >= m_game.time.nextDropTime)
    {
        m_game.piece->SoftDrop();
    }
    
    m_game.board->FindLines(&m_game.stats);
    if (m_game.stats.pendingLineCount > 0)
    {
        m_game.phase = GAME_PHASE_LINE;
        m_game.time.highlightEndTime = m_game.time.time + 0.5f;
    }
    
    if (!m_game.board->IsRowEmpty(0))
    {
        m_game.phase = GAME_PHASE_OVER;
    }
}

void Game::UpdateGameLine()
{
    if (m_game.time.time >= m_game.time.highlightEndTime)
    {
        m_game.board->ClearLines(m_game.stats);
        m_game.stats.lineCount += m_game.stats.pendingLineCount;
        m_game.stats.points += ComputePoints(m_game.stats);
        
    }
}

void Game::UpdateGameOver()
{
    if (m_input.denter > 0)
    {
        m_game.phase = GAME_PHASE_START;
    }
}

void Game::Update()
{
    switch (m_game.phase)
    {
        case GAME_PHASE_START:
        {
            UpdateGameStart();
        } break;
        
        case GAME_PHASE_PLAY:
        {
            UpdateGamePlay();
        } break;
        
        case GAME_PHASE_LINE:
        {
            UpdateGameLine();
        } break;
        
        case GAME_PHASE_OVER:
        {
            UpdateGameOver();
        } break;
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);
    
    char buffer[4096];
    
    i32 yMargin = (BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE;
    
    m_game.board->DrawBoard(0, yMargin);
    
    switch (m_game.phase)
    {
        case GAME_PHASE_START:
        {
            i32 xPos = BOARD_COLS * BOARD_GRID_SIZE / 2;
            i32 yPos = (BOARD_ROWS * BOARD_GRID_SIZE + yMargin) / 2;
            Graphics::Instance()->DrawText(m_font, "Press Enter to start", xPos, yPos, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
        } break;
        
        case GAME_PHASE_PLAY:
        {
            // Haven't done with rendering part yet 
            m_game.piece->DrawPiece(0, yMargin);
            
            Piece piece = *(m_game.piece);
            
            while (piece.IsValid())
            {
                piece.SetRowOffset(piece.GetRowOffset() + 1);
            }
            piece.SetRowOffset(piece.GetRowOffset() - 1);
            piece.DrawPiece(0, yMargin, true);
        } break;
        
        case GAME_PHASE_LINE:
        {
            
        } break;
        
        case GAME_PHASE_OVER:
        {
            
        } break;
    }
}

void Game::MainLoop()
{
    while (Running())
    {
        HandleEvents();
        HandleInput();
        
        Update();
        Render();
        
        SDL_RenderPresent(m_renderer);
    }
}

void Game::Clean()
{
    std::cout << "Closing the game. Cleaning up all the mess...\n";
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}