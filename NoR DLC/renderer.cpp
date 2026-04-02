#include "renderer.h"

//to load textures, our game is small enough so we chose to just load everything in
void Renderer::Load() {
    //background = LoadTexture("assets/bg_forest.png");

    spriteSheet = LoadTexture("assets/Suni_128_x_128.png");

    portraits["neutral"] = {0,0};
    portraits["angry"] = {1,0};
    portraits["happy"] = {2,0};
    portraits["dizzy"] = {3,0};
    portraits["blank"] = {4,0};
}

//to unload textures to free up memory (at the end of the program)
void Renderer::Unload() 
{
    UnloadTexture(background);
    UnloadTexture(spriteSheet);

    /* for (auto& [key, tex] : portraits)
    {
        UnloadTexture(tex);
    } */
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

    Vector2 frame = portraits[portrait];

    // Crop 128x128 frame from the sheet to get the correct sprite
    Rectangle spriteSrc = 
    {
        frame.x * FRAME_SIZE,   // x offset into sheet
        frame.y * FRAME_SIZE,   // y offset into sheet
        FRAME_SIZE,
        FRAME_SIZE
    };
    
    float drawSize = FRAME_SIZE * PORTRAIT_SCALE;


    Rectangle dest = 
    {
        (800 - drawSize) / 2,
        320 - drawSize,
        drawSize,
        drawSize
    };

    DrawTexturePro(spriteSheet, spriteSrc, dest, { 0, 0 }, 0.0f, WHITE);
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