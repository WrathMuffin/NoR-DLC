#include "snake.h"
#include "raylib.h"

Snake::Snake(int startX, int startY, int cellSize)
    : length(4), cellSize(cellSize), dir(DIR_RIGHT), nextDir(DIR_RIGHT)
{
    for (int i = 0; i < length; i++) {
        bodyX[i] = startX - i;
        bodyY[i] = startY;
    }
}

void Snake::SetDirection(Direction newDir) {
    // Prevent reversing
    if (newDir == DIR_UP    && dir == DIR_DOWN)  return;
    if (newDir == DIR_DOWN  && dir == DIR_UP)    return;
    if (newDir == DIR_LEFT  && dir == DIR_RIGHT) return;
    if (newDir == DIR_RIGHT && dir == DIR_LEFT)  return;
    nextDir = newDir;
}

void Snake::Move() {
    dir = nextDir;

    // Shift body segments back
    for (int i = length - 1; i > 0; i--) {
        bodyX[i] = bodyX[i - 1];
        bodyY[i] = bodyY[i - 1];
    }

    // Move head
    if (dir == DIR_UP)    bodyY[0]--;
    if (dir == DIR_DOWN)  bodyY[0]++;
    if (dir == DIR_LEFT)  bodyX[0]--;
    if (dir == DIR_RIGHT) bodyX[0]++;
}

bool Snake::CheckSelfCollision() const {
    for (int i = 1; i < length; i++)
        if (bodyX[0] == bodyX[i] && bodyY[0] == bodyY[i])
            return true;
    return false;
}

bool Snake::CheckWallCollision(int cols, int rows) const {
    return bodyX[0] < 0 || bodyX[0] >= cols ||
           bodyY[0] < 0 || bodyY[0] >= rows;
}

void Snake::Draw(int cellSize) const {
    for (int i = 0; i < length; i++) {
        Color c = (i == 0) ? GREEN : LIME;
        DrawRectangle(bodyX[i] * cellSize + 1, bodyY[i] * cellSize + 1,
                      cellSize - 2, cellSize - 2, c);
    }
}