#include "renderer.h"
#include "raylib.h"
#include <string>

Renderer::Renderer(int screenW, int screenH, int cellSize, int cols, int rows)
    : screenW(screenW), screenH(screenH),
      cellSize(cellSize), cols(cols), rows(rows)
{
    InitWindow(screenW, screenH, "Snake - Raylib");
    SetTargetFPS(10);
}

Renderer::~Renderer() {
    CloseWindow();
}

void Renderer::BeginFrame() const { BeginDrawing(); ClearBackground(BLACK); }
void Renderer::EndFrame()   const { EndDrawing(); }

void Renderer::DrawGrid() const {
    for (int x = 0; x <= cols; x++)
        DrawLine(x * cellSize, 0, x * cellSize, screenH, { 30, 30, 30, 255 });
    for (int y = 0; y <= rows; y++)
        DrawLine(0, y * cellSize, screenW, y * cellSize, { 30, 30, 30, 255 });
}

void Renderer::DrawSnake(const Snake& snake) const { snake.Draw(cellSize); }
void Renderer::DrawFood(const Food& food)    const { food.Draw(); }

void Renderer::DrawScore(int score) const {
    std::string text = "Score: " + std::to_string(score);
    DrawText(text.c_str(), 10, 10, 20, WHITE);
}

void Renderer::DrawGameOver(int score) const {
    DrawText("GAME OVER", screenW / 2 - 90, screenH / 2 - 30, 40, RED);
    std::string s = "Final Score: " + std::to_string(score);
    DrawText(s.c_str(), screenW / 2 - 80, screenH / 2 + 20, 24, WHITE);
    DrawText("Press R to restart", screenW / 2 - 90, screenH / 2 + 60, 20, GRAY);
}

void Renderer::DrawStartScreen() const {
    DrawText("SNAKE",        screenW / 2 - 60, screenH / 2 - 50, 50, GREEN);
    DrawText("Press ENTER",  screenW / 2 - 80, screenH / 2 + 20, 24, WHITE);
    DrawText("W A S D  to move", screenW / 2 - 90, screenH / 2 + 55, 20, GRAY);
}