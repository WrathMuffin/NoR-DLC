#pragma once
#include "snake.h"
#include "food.h"

class Renderer {
public:
    Renderer(int screenW, int screenH, int cellSize, int cols, int rows);
    ~Renderer();

    void BeginFrame() const;
    void EndFrame()   const;

    void DrawGrid()             const;
    void DrawSnake(const Snake& snake) const;
    void DrawFood(const Food& food)    const;
    void DrawScore(int score)          const;
    void DrawGameOver(int score)       const;
    void DrawStartScreen()             const;

private:
    int screenW, screenH, cellSize, cols, rows;
};