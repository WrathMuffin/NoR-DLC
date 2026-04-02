#include "raylib.h"
#include "DialogueSystem.h"
#include "Renderer.h"

int main() {
    InitWindow(800, 450, "Night of Rizzing DLC");
    SetTargetFPS(10); //its a visual novel so 10 fps should be enough

    //loads in the dialogue from the json file
    DialogueSystem dialogue;
    dialogue.LoadFromFile("assets/dialogue.json");
    dialogue.StartScene("intro");

    Renderer renderer;
    renderer.Load();

    while (!WindowShouldClose()) 
    {
        // get input from the player either from mouse click or spacebar
        if (dialogue.IsActive() && !dialogue.IsShowingChoice()) 
        {
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                dialogue.Advance();
            }
        }

        if (dialogue.IsShowingChoice()) 
        {
            const auto& choices = dialogue.Choices();
            for (int i = 0; i < (int)choices.size(); i++) 
            {
                Rectangle btn = { 250, 150.f + i * 50, 300, 40 };
                if (CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    dialogue.SelectChoice(i);
                }
            }
        }

        // Draw
        renderer.Draw(dialogue);
    }

    renderer.Unload();
    CloseWindow();
    return 0;
}