@echo off

set DebugCompilerOptions=-Fetetris.exe -Oi -WX -W4 -EHsc -wd4100 -wd4189 -wd4201 -wd4505 -wd4456 -wd4996 -wd4091 -nologo -Zi -FAsc 

set ReleaseCompilerOptions=-O2 -WX -W4 -EHsc -wd4100 -wd4189 -wd4201 -wd4505 -wd4456 -wd4996 -nologo -FAsc

set LinkerOptions=-opt:ref SDL2.lib SDL2_ttf.lib /LIBPATH:..\dependencies\SDL2\lib\x86 /LIBPATH:..\dependencies\SDL2_ttf\lib\x86 /SUBSYSTEM:CONSOLE

set IncludeDirectories=/I "..\dependencies\SDL2_ttf\include" /I "..\dependencies\SDL2\include"

if not exist ..\build mkdir ..\build
pushd ..\build

set FilesToCompile=..\src\main.cpp ..\src\game.cpp ..\src\graphics\graphics.cpp

REM Debug build
cl %DebugCompilerOptions% %IncludeDirectories% %FilesToCompile% /link %LinkerOptions% 


popd

REM Compiler Flags:

REM Zi  : debug info (Z7 older debug format for complex builds)
REM Zo  : More debug info for optimized builds
REM FC  : Full path on errors (will be deprecated soon, use -Fasc instead)
REM Oi  : Always do intrinsics with you can
REM Od  : No optimizations
REM O2  : Full optimizations
REM MT  : Use C static lib instead of searching for dll at run-time
REM MTd : Sabe as MT but using the debug version of CRT
REM GR- : Turn off C++ run-time type info
REM Gm- : Turn off incremental build
REM EHa-: Turn off exception handling
REM EHsc: Enable unwind semantics (c++ exception handling)
REM WX  : Treat warning as errors
REM W4  : Set Warning level to 4 (Wall to all levels)
REM wd  : Ignore warning
REM fp:fast    : Ignores the rules in some cases to optimize fp operations
REM Fmfile.map : Outputs a map file (mapping of the functions on the exr)

REM Linker Options:

REM subsystem:windows,5.1 : Make exe compatible with Windows XP (only works on x86)
REM opt:ref               : Eliminates functions and data that are never referenced
REM incremental:no        : Don't need to do incremental builds
REM LD                    : Build a dll
REM PDB:file.pdb          : Change the .pdb's path