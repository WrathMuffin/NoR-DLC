#include "raylib.h"
#include "snake.h"
#include "food.h"
#include "renderer.h"

// ── Grid / window settings ────────────────────────────────────
const int CELL_SIZE = 24;
const int COLS      = 30;
const int ROWS      = 25;
const int SCREEN_W  = CELL_SIZE * COLS;
const int SCREEN_H  = CELL_SIZE * ROWS;

enum GameState { STATE_START, STATE_PLAYING, STATE_GAMEOVER };

int main() {
    Renderer renderer(SCREEN_W, SCREEN_H, CELL_SIZE, COLS, ROWS);

    Snake  snake(COLS / 2, ROWS / 2, CELL_SIZE);
    Food   food(COLS, ROWS, CELL_SIZE);
    int    score     = 0;
    GameState state  = STATE_START;

    while (!WindowShouldClose()) {

        // ── Input ──────────────────────────────────────────────
        if (state == STATE_START) {
            if (IsKeyPressed(KEY_ENTER)) state = STATE_PLAYING;
        }
        else if (state == STATE_PLAYING) {
            if (IsKeyPressed(KEY_W)) snake.SetDirection(DIR_UP);
            if (IsKeyPressed(KEY_S)) snake.SetDirection(DIR_DOWN);
            if (IsKeyPressed(KEY_A)) snake.SetDirection(DIR_LEFT);
            if (IsKeyPressed(KEY_D)) snake.SetDirection(DIR_RIGHT);
        }
        else if (state == STATE_GAMEOVER) {
            if (IsKeyPressed(KEY_R)) {
                snake  = Snake(COLS / 2, ROWS / 2, CELL_SIZE);
                food   = Food(COLS, ROWS, CELL_SIZE);
                score  = 0;
                state  = STATE_PLAYING;
            }
        }

        // ── Update ─────────────────────────────────────────────
        if (state == STATE_PLAYING) {
            snake.Move();

            if (snake.CheckWallCollision(COLS, ROWS) || snake.CheckSelfCollision())
                state = STATE_GAMEOVER;

            if (snake.GetHeadX() == food.GetX() && snake.GetHeadY() == food.GetY()) {
                snake.Grow();
                score += 10;
                food.Respawn(snake.bodyX, snake.bodyY, snake.GetLength());
            }
        }

        // ── Draw ───────────────────────────────────────────────
        renderer.BeginFrame();
        renderer.DrawGrid();

        if (state == STATE_START) {
            renderer.DrawStartScreen();
        } else {
            renderer.DrawSnake(snake);
            renderer.DrawFood(food);
            renderer.DrawScore(score);
            if (state == STATE_GAMEOVER)
                renderer.DrawGameOver(score);
        }

        renderer.EndFrame();
    }

    return 0;
}