#pragma once
#include "raylib.h"

class Food {
public:
    Food(int cols, int rows, int cellSize);

    void Respawn(int snakeBodyX[], int snakeBodyY[], int snakeLen);
    void Draw() const;

    int GetX() const { return gridX; }
    int GetY() const { return gridY; }

private:
    int gridX, gridY;
    int cols, rows, cellSize;
};