@echo off
REM ── Snake Game Build Script ──────────────────────────────────
REM Requires: raylib installed at C:\raylib
REM Download from https://github.com/raysan5/raylib/releases

set RAYLIB=C:\raylib
set SRC=main.cpp dialogueSystem.cpp renderer.cpp Rizzermometer.cpp save.cpp
set OUT="Night of Rizzing - Rise of the Rizzler.exe"
set FLAGS=-std=c++17 -O2

g++ %FLAGS% %SRC% -o %OUT% ^
    -I%RAYLIB%\include ^
    -L%RAYLIB%\lib ^
    -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel%==0 (
    echo Build successful! Run: Night of Rizzing - Rise of the Rizzler.exe
) else (
    echo Build FAILED. Check your raylib path.
)