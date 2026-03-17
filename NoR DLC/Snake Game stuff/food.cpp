#include "food.h"
#include <cstdlib>
#include <ctime>

Food::Food(int cols, int rows, int cellSize)
    : cols(cols), rows(rows), cellSize(cellSize), gridX(0), gridY(0)
{
    srand((unsigned)time(0));
    gridX = rand() % cols;
    gridY = rand() % rows;
}

void Food::Respawn(int snakeBodyX[], int snakeBodyY[], int snakeLen) {
    bool onSnake = true;
    while (onSnake) {
        gridX = rand() % cols;
        gridY = rand() % rows;
        onSnake = false;
        for (int i = 0; i < snakeLen; i++) {
            if (snakeBodyX[i] == gridX && snakeBodyY[i] == gridY) {
                onSnake = true;
                break;
            }
        }
    }
}

void Food::Draw() const {
    DrawRectangle(gridX * cellSize + 4, gridY * cellSize + 4,
                  cellSize - 8, cellSize - 8, RED);
}