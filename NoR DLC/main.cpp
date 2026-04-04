#include "raylib.h"
#include "DialogueSystem.h"
#include "Renderer.h"
#include "ui.h"
#include "Rizzermometer.h"

int main() {
    InitWindow(800, 450, "Night of Rizzing DLC");
    SetTargetFPS(10); //its a visual novel so 10 fps should be enough

    //loads in the dialogue from the json file
    DialogueSystem dialogue;
    dialogue.LoadFromFile("assets/dialogue.json");
    dialogue.StartScene("intro");

    Renderer renderer;
    renderer.Load();

    UI* rizzermometer = new Rizzermometer(100.0f, 20, 20, 200, 20);

    while (!WindowShouldClose()) 
    {
        dialogue.Tick();

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
                    static_cast<Rizzermometer*>(rizzermometer)->AddScore(choices[i].scoreChange * 100.0f);
                    dialogue.SelectChoice(i);
                }
            }
        }

        rizzermometer->Update();

        // Draw
        renderer.Draw(dialogue);
        rizzermometer->Draw();
    }

    renderer.Unload();
    CloseWindow();
    return 0;
}