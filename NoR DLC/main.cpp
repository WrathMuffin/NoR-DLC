#include "raylib.h"
#include "DialogueSystem.h"
#include "Renderer.h"
#include "ui.h"
#include "Rizzermometer.h"
#include "save.h"

int main() {
    InitWindow(800, 450, "Night of Rizzing DLC");
    SetTargetFPS(12); //its a visual novel so 12 fps should be enough

    //loads in the dialogue from the json file
    DialogueSystem dialogue;
    dialogue.LoadFromFile("assets/dialogue.json");
    dialogue.StartScene("intro", 0);

    Renderer renderer;
    renderer.Load();

    UI* rizzermometer = new Rizzermometer(100.0f, 20, 20, 200, 20);

    //load in a save if there is one, if not it will just start the intro
    string savedScene;
    int savedDialogue = 0;
    float  savedScore = 0.0f;

    if (SaveSystem::Load(savedScene, savedDialogue, savedScore)) 
    {
        dialogue.StartScene(savedScene, savedDialogue);
        static_cast<Rizzermometer*>(rizzermometer)->AddScore(savedScore);
    }
    
    else
    {
        dialogue.StartScene("intro", 0);
    }    

    //actual game running
    while (!WindowShouldClose()) 
    {
        dialogue.Tick();

        // get input from the player either from mouse click or spacebar
        if (dialogue.IsActive() && !dialogue.IsShowingChoice()) 
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                dialogue.Advance();

                if (dialogue.GetCurrentSceneId() == "ending_check") 
                {
                    float score = static_cast<Rizzermometer*>(rizzermometer)->GetNormalized();
                    dialogue.CheckScoreBranch(score, "good_ending", "bad_ending");
                }
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
                    static_cast<Rizzermometer*>(rizzermometer)->AddScore(choices[i].scoreChange);
                    dialogue.SelectChoice(i);
                }
            }

        }
        
        //save if S is pressed
        if (IsKeyPressed(KEY_S)) 
        {
            SaveSystem::Save
            (
                dialogue.GetCurrentSceneId(), dialogue.GetCurrentLineId(),
                static_cast<Rizzermometer*>(rizzermometer)->GetScore()
            );
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