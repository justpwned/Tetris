#include <iostream>
#include <cstdlib>
#include <time.h>

#include "game.hpp"
#include "palette.hpp"
#include "menu.hpp"
#include "info.hpp"
#include "highscores.hpp"

using namespace core;
using namespace core::graphics;
using namespace core::gameplay;

Game::Game(const char *t_title, i32 t_xPos, i32 t_yPos, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName)
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
        
        m_font = TTF_OpenFont(t_fontName, 24);
        
        if (m_font)
        {
            std::cout << "Font " << t_fontName << " has been loaded\n";
        }
        else
        {
            std::cerr << "Font " << t_fontName << " has not been loaded\n";
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
    
    m_input = {};
    
    m_game = {};
    m_game.board = new gameplay::Board(BOARD_ROWS, BOARD_COLS, BOARD_VISIBLE_ROWS, BOARD_GRID_SIZE);
    m_game.stats = new Stats();
    m_game.piece = new Piece(m_game.board, &m_game.time, m_game.stats, 0, 0, 0, 0);
    m_game.menu = new Menu(&m_input, m_font);
    m_game.info = new Info(&m_input, m_font, "info.txt");
    m_game.highscores = new Highscores(&m_input, m_font, "highscores.data");
    m_game.highscores->LoadRecords();
    
    m_game.seed = (u32)time(0);
    srand(m_game.seed);
    std::cout << "Game seed: " << m_game.seed << "\n";
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
        else if (e.type == SDL_KEYDOWN)
        {
            if (SDL_IsTextInputActive())
            {
                if (e.key.keysym.sym == SDLK_RETURN && m_game.highscoreName.length() > 0)
                {
                    m_game.highscores->WriteRecord(m_game.highscoreName.c_str(), m_game.stats->GetPoints());
                    SDL_StopTextInput();
                }
                else if(e.key.keysym.sym == SDLK_BACKSPACE && m_game.highscoreName.length() > 0)
                {
                    m_game.highscoreName.pop_back();
                }
                else if(e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                {
                    SDL_SetClipboardText(m_game.highscoreName.c_str());
                }
                else if(e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                {
                    m_game.highscoreName= SDL_GetClipboardText();
                }
            }
        }
        else if (e.type == SDL_TEXTINPUT)
        {
            if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V')))
            {
                if (m_game.highscoreName.length() < 12)
                {
                    m_game.highscoreName += e.text.text;
                }
            }
        }
    }
}

void Game::HandleInput()
{
    i32 keyCount;
    const u8 *keyStates = SDL_GetKeyboardState(&keyCount);
    
    if (keyStates)
    {
        if (keyStates[SDL_SCANCODE_Q])
        {
            Quit();
        }
        
        InputState prevInput = m_input;
        
        m_input.left    = keyStates[SDL_SCANCODE_LEFT];
        m_input.right   = keyStates[SDL_SCANCODE_RIGHT];
        m_input.up      = keyStates[SDL_SCANCODE_UP];
        m_input.down    = keyStates[SDL_SCANCODE_DOWN];
        m_input.space   = keyStates[SDL_SCANCODE_SPACE];
        m_input.enter   = keyStates[SDL_SCANCODE_RETURN];
        m_input.z       = keyStates[SDL_SCANCODE_Z];
        m_input.escape  = keyStates[SDL_SCANCODE_ESCAPE];
        
        m_input.dleft   = m_input.left - prevInput.left;
        m_input.dright  = m_input.right - prevInput.right;
        m_input.dup     = m_input.up - prevInput.up;
        m_input.ddown   = m_input.down - prevInput.down;
        m_input.dspace  = m_input.space - prevInput.space;
        m_input.denter  = m_input.enter - prevInput.enter;
        m_input.dz      = m_input.z - prevInput.z;
        m_input.descape = m_input.escape - prevInput.escape;
    }
}

void Game::UpdateGameStart()
{
    if (m_input.dup > 0)
    {
        m_game.stats->SetStartLevel(m_game.stats->GetStartLevel() + 1);
    }
    
    if (m_input.ddown > 0 && m_game.stats->GetStartLevel() > 0)
    {
        m_game.stats->SetStartLevel(m_game.stats->GetStartLevel() - 1);
    }
    
    if (m_input.denter > 0)
    {
        m_game.board->Clear();
        m_game.stats->SetLevel(m_game.stats->GetStartLevel());
        m_game.stats->SetLineCount(0);
        m_game.stats->SetPoints(0);
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
    
    if (m_input.descape > 0)
    {
        m_game.phase = GAME_PHASE_MENU;
    }
    
    while (m_game.time.time >= m_game.time.nextDropTime)
    {
        m_game.piece->SoftDrop();
    }
    
    m_game.board->FindLines(m_game.stats);
    if (m_game.stats->GetPendingLineCount() > 0)
    {
        m_game.phase = GAME_PHASE_LINE;
        m_game.time.highlightEndTime = m_game.time.time + 0.35f;
    }
    
    if (!m_game.board->IsRowEmpty(0))
    {
        i32 score = m_game.stats->GetPoints();
        if (m_game.highscores->IsHighscore(score))
        {
            SDL_StartTextInput();
        }
        
        m_game.phase = GAME_PHASE_OVER;
    }
}

void Game::UpdateGameLine()
{
    if (m_game.time.time >= m_game.time.highlightEndTime)
    {
        m_game.board->ClearLines(m_game.stats);
        m_game.stats->SetLineCount(m_game.stats->GetLineCount() +
                                   m_game.stats->GetPendingLineCount());
        m_game.stats->ComputePoints();
        
        if (m_game.stats->GetLineCount() >= m_game.stats->GetLinesForNextLevel())
        {
            m_game.stats->SetLevel(m_game.stats->GetLevel() + 1);
        }
        
        m_game.phase = GAME_PHASE_PLAY;
    }
}

void Game::UpdateGameOver()
{
    if (m_input.denter > 0)
    {
        m_game.phase = GAME_PHASE_MENU;
    }
}

void Game::Update()
{
    switch (m_game.phase)
    {
        case GAME_PHASE_MENU:
        {
            m_game.phase = m_game.menu->Update();
        } break;
        
        case GAME_PHASE_HIGHSCORES:
        {
            m_game.phase = m_game.highscores->Update();
        } break;
        
        case GAME_PHASE_INFO:
        {
            m_game.phase = m_game.info->Update();
        } break;
        
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
        
        case GAME_PHASE_EXIT:
        {
            Quit();
        } break;
    }
}

void Game::RenderGameStart(i32 t_xOffset, i32 t_yOffset)
{
    i32 xPos = BOARD_COLS * BOARD_GRID_SIZE / 2;
    i32 yPos = (BOARD_ROWS * BOARD_GRID_SIZE + t_yOffset) / 2;
    Graphics::Instance()->DrawText(m_font, "Press Enter to start", xPos, yPos, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    
    char buffer[4096];
    snprintf(buffer, sizeof(buffer), "STARTING LEVEL: %d", m_game.stats->GetStartLevel());
    Graphics::Instance()->DrawText(m_font, buffer, xPos, yPos + 30, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    
    Graphics::Instance()->DrawFillRect(0, t_yOffset, BOARD_COLS * BOARD_GRID_SIZE,(BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE, Palette::s_backColor);
    RenderGameStats(0, 0);
}

void Game::RenderGamePlay(i32 t_xOffset, i32 t_yOffset)
{
    m_game.board->DrawBoard(0, t_yOffset);
    m_game.piece->DrawPiece(0, t_yOffset);
    
    Piece piece = *(m_game.piece);
    
    while (piece.IsValid())
    {
        piece.SetRowOffset(piece.GetRowOffset() + 1);
    }
    piece.SetRowOffset(piece.GetRowOffset() - 1);
    piece.DrawPiece(0, t_yOffset, true);
    
    Graphics::Instance()->DrawFillRect(0, t_yOffset, BOARD_COLS * BOARD_GRID_SIZE,(BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE, Palette::s_backColor);
    RenderGameStats(0, 0);
}

void Game::RenderGameLine(i32 t_xOffset, i32 t_yOffset)
{
    m_game.board->DrawBoard(0, t_yOffset);
    
    for (i32 row = 0; row < BOARD_ROWS; ++row)
    {
        if (m_game.stats->GetLines()[row])
        {
            i32 xPos = 0;
            i32 yPos = row * BOARD_GRID_SIZE + t_yOffset;
            Graphics::Instance()->DrawFillRect(xPos, yPos, BOARD_COLS * BOARD_GRID_SIZE, BOARD_GRID_SIZE, Palette::s_highlightColor);
        }
    }
    
    Graphics::Instance()->DrawFillRect(0, t_yOffset, BOARD_COLS * BOARD_GRID_SIZE,(BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE, Palette::s_backColor);
    RenderGameStats(0, 0);
}

void Game::RenderGameOver(i32 t_xOffset, i32 t_yOffset)
{
    i32 xPos = BOARD_COLS * BOARD_GRID_SIZE / 2;
    i32 yPos = (BOARD_ROWS * BOARD_GRID_SIZE + t_yOffset) / 2;
    Graphics::Instance()->DrawText(m_font, "GAME OVER", xPos, yPos, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    
    Graphics::Instance()->DrawFillRect(0 , t_yOffset, BOARD_COLS * BOARD_GRID_SIZE,(BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE, Palette::s_backColor);
    RenderGameStats(0, 0);
}

void Game::RenderGameStats(i32 t_xOffset, i32 t_yOffset)
{
    char buffer[4096];
    
    i32 xPos = 5;
    i32 yPos = 20;
    
    snprintf(buffer, sizeof(buffer), "LEVEL: %d", m_game.stats->GetLevel());
    Graphics::Instance()->DrawText(m_font, buffer, xPos, yPos, TEXT_ALIGN_LEFT, Palette::s_highlightColor);
    
    yPos += 30;
    snprintf(buffer, sizeof(buffer), "LINES: %d", m_game.stats->GetLineCount());
    Graphics::Instance()->DrawText(m_font, buffer, xPos, yPos, TEXT_ALIGN_LEFT, Palette::s_highlightColor);
    
    yPos += 30;
    snprintf(buffer, sizeof(buffer), "POINTS: %d", m_game.stats->GetPoints());
    Graphics::Instance()->DrawText(m_font, buffer, xPos, yPos, TEXT_ALIGN_LEFT, Palette::s_highlightColor);
}

void Game::Render()
{
    Graphics::Instance()->FillBackground(Palette::s_backColor);
    i32 yMargin = (BOARD_ROWS - BOARD_VISIBLE_ROWS) * BOARD_GRID_SIZE;
    
    switch (m_game.phase)
    {
        case GAME_PHASE_MENU:
        {
            m_game.menu->Render(m_gameWidth / 2, 200, BUTTON_ALIGN_CENTER);
        } break;
        
        case GAME_PHASE_HIGHSCORES:
        {
            m_game.highscores->Render(m_gameWidth / 2, 200);
        } break;
        
        case GAME_PHASE_INFO:
        {
            m_game.info->Render(m_gameWidth / 2, 200);
        } break;
        
        case GAME_PHASE_START:
        {
            RenderGameStart(0, yMargin);
        } break;
        
        case GAME_PHASE_PLAY:
        {
            RenderGamePlay(0, yMargin);
        } break;
        
        case GAME_PHASE_LINE:
        {
            RenderGameLine(0, yMargin);
        } break;
        
        case GAME_PHASE_OVER:
        {
            RenderGameOver(0, yMargin);
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