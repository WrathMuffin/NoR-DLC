#include "renderer.h"

//to load textures, our game is small enough so we chose to just load everything in
void Renderer::Load() {
    //background = LoadTexture("assets/bg_forest.png");

    portraits["aria_neutral"] = LoadTexture("assets/Suni_128_x_128.png");
}

//to unload textures to free up memory (at the end of the program)
void Renderer::Unload() 
{
    UnloadTexture(background);
    for (auto& [key, tex] : portraits)
    {
        UnloadTexture(tex);
    }
}

void Renderer::Draw(const DialogueSystem& dialogue) 
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawBackground();

    if (dialogue.IsActive()) 
    {
        DrawPortrait(dialogue.CurrentLine().portrait);
        DrawDialogueBox(dialogue);

        if (dialogue.IsShowingChoice())
            DrawChoices(dialogue);
    }

    EndDrawing();
}

void Renderer::DrawBackground() {
    DrawTexture(background, 0, 0, WHITE);
}

void Renderer::DrawPortrait(const string& portrait) 
{
    if (portrait.empty() || !portraits.count(portrait)) return;

    Texture2D& tex = portraits[portrait];
    int x = (800 - tex.width) / 2;
    int y = 320 - tex.height;
    DrawTexture(tex, x, y, WHITE);
}

void Renderer::DrawDialogueBox(const DialogueSystem& dialogue) 
{
    const auto& line = dialogue.CurrentLine();

    DrawRectangle(0, 320, 800, 130, Fade(BLACK, 0.8f));
    DrawRectangleLines(0, 320, 800, 130, WHITE);
    DrawText(line.character.c_str(), 30, 330, 20, YELLOW);
    DrawText(line.text.c_str(), 30, 360, 18, WHITE);
}

//this draws the choice box that will appere when there is a choice
void Renderer::DrawChoices(const DialogueSystem& dialogue) 
{
    const auto& choices = dialogue.Choices();
    for (int i = 0; i < (int)choices.size(); i++) 
    {
        Rectangle btn = { 250, 150.f + i * 50, 300, 40 };
        bool hover = CheckCollisionPointRec(GetMousePosition(), btn);

        DrawRectangleRec(btn, hover ? DARKGRAY : GRAY);
        DrawText(choices[i].label.c_str(), (int)btn.x + 10, (int)btn.y + 10, 18, WHITE);
    }
}