@echo off
REM ── Snake Game Build Script ──────────────────────────────────
REM Requires: raylib installed at C:\raylib
REM Download from https://github.com/raysan5/raylib/releases

set RAYLIB=C:\Users\spamt\Downloads\SnakeGame\raylib
set SRC=main.cpp snake.cpp food.cpp renderer.cpp
set OUT=snake.exe
set FLAGS=-std=c++17 -O2

g++ %FLAGS% %SRC% -o %OUT% ^
    -I%RAYLIB%\include ^
    -L%RAYLIB%\lib ^
    -lraylib -lopengl32 -lgdi32 -lwinmm

if %errorlevel%==0 (
    echo Build successful! Run: snake.exe
) else (
    echo Build FAILED. Check your raylib path.
)