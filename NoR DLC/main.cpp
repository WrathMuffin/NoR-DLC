#include "raylib.h"
#include "DialogueSystem.h"
#include "Renderer.h"
#include "ui.h"
#include "Rizzermometer.h"
#include "save.h"
#include "dialogueBox.h"

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
    UI* dialogueBox   = new DialogueBox(0, 320, 800, 130);

    static_cast<DialogueBox*>(dialogueBox)->SetDialogue(&dialogue);

    //load in a save if there is one, if not it will just start the intro
    string savedScene;
    int savedDialogue = 0;
    float  savedScore = 0.0f;

    // start scene at intro, and at dialgoue 0 (fist dialogue)
    dialogue.StartScene("intro", 0);

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

                if (dialogue.GetCurrentSceneId() == "evening_endings")
                {
                    dialogue.Advance();
                    float score = static_cast<Rizzermometer*>(rizzermometer)->GetNormalized();
                    dialogue.CheckScoreBranch(score, 0.5f, "evening_good", "evening_bad");
                    
                }
                
                else if (dialogue.GetCurrentSceneId() == "night_3_endings")
                {
                    dialogue.Advance();
                    float score = static_cast<Rizzermometer*>(rizzermometer)->GetNormalized();
                    dialogue.CheckScoreBranch(score, 0.6f, "night_good_neutral_endings", "night_bad");
                }
                
                else if (dialogue.GetCurrentSceneId() == "night_good_neutral_endings")
                {
                    dialogue.Advance();
                    float score = static_cast<Rizzermometer*>(rizzermometer)->GetNormalized();
                    dialogue.CheckScoreBranch(score, 0.7f, "night_good", "night_neutral");
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

        if (IsKeyPressed(KEY_L))
        {
            if (SaveSystem::Load(savedScene, savedDialogue, savedScore))
            {
                dialogue.StartScene(savedScene, savedDialogue);
                static_cast<Rizzermometer*>(rizzermometer)->AddScore(-100); // reset to 0
                static_cast<Rizzermometer*>(rizzermometer)->AddScore(savedScore); // then add saved scroe
            }

            else
            {
                dialogue.StartScene("intro", 0);
            }

        }

        //update
        rizzermometer->Update();
        dialogueBox->Update(); //it's here but does nothing :(
        
        //draw
        renderer.Draw(dialogue);
        rizzermometer->Draw();
        dialogueBox->Draw();

        EndDrawing();
    }

    //free up memory by unloading textures and deleting stuff from the heap
    renderer.Unload();
    delete rizzermometer;
    delete dialogueBox;


    CloseWindow();
    return 0;
}