#include "raylib.h"
#include "DialogueSystem.h"

int main() {
    InitWindow(800, 450, "Visual Novel");
    SetTargetFPS(60);

    DialogueSystem dialogue;
    dialogue.LoadFromFile("assets/dialogue.json");
    dialogue.StartScene("intro");

    while (!WindowShouldClose()) {

        // --- Input ---
        if (dialogue.IsActive() && !dialogue.IsShowingChoice()) {
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                dialogue.Advance();
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(BLACK);

        if (dialogue.IsActive()) {
            const auto& line = dialogue.CurrentLine();

            // Dialogue box
            DrawRectangle(0, 320, 800, 130, Fade(BLACK, 0.8f));
            DrawRectangleLines(0, 320, 800, 130, WHITE);

            // Character name
            DrawText(line.character.c_str(), 30, 330, 20, YELLOW);

            // Dialogue text
            DrawText(line.text.c_str(), 30, 360, 18, WHITE);

            // Choices
            if (dialogue.IsShowingChoice()) {
                const auto& choices = dialogue.Choices();
                for (int i = 0; i < (int)choices.size(); i++) {
                    Rectangle btn = { 250, 150.f + i * 50, 300, 40 };
                    bool hover = CheckCollisionPointRec(GetMousePosition(), btn);

                    DrawRectangleRec(btn, hover ? DARKGRAY : GRAY);
                    DrawText(choices[i].label.c_str(), (int)btn.x + 10, (int)btn.y + 10, 18, WHITE);

                    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        dialogue.SelectChoice(i);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}