#include "renderer.h"

// to load textures, our game is small enough so we chose to just load everything in
void Renderer::Load()
{
    // background = LoadTexture("assets/bg_forest.png");

    spriteSheet[0] = LoadTexture("assets/SUNI_128_x_128.png");
    background[0] = LoadTexture("assets/Office BG.png");
    // spriteSheet[1] = LoadTexture("assets/Suni_128_x_128.png");

    portraits["suniGremlin"] = {0, 0};      // 0
    portraits["suniAngry"] = {1, 0};        // 1
    portraits["suniNeutral"] = {2, 0};      // 2
    portraits["suniBlush"] = {3, 0};        // 3
    portraits["suniBlank"] = {4, 0};        // 4
    portraits["suniPout"] = {5, 0};         // 5
    portraits["suniHappy"] = {6, 0};        // 6
    portraits["suniBack"] = {7, 0};         // 7
    portraits["suniSurprise"] = {8, 0};     // 8
    portraits["suniNervous"] = {9, 0};      // 9
    portraits["suniBruh"] = { 10, 0 };      // 10
    
    portraits["sukiNeutral"] = { 11, 0 };   // 11
    portraits["sukiHappy"] = { 12, 0 };     // 12
    portraits["sukiSurprise"] = { 13, 0 };  // 13
    portraits["sukiNervous"] = { 14, 0 };   // 14
}

// to unload textures to free up memory (at the end of the program)
void Renderer::Unload()
{
    UnloadTexture(background[0]);
    UnloadTexture(spriteSheet[0]);

    /* for (auto& [key, tex] : portraits)
    {
        UnloadTexture(tex);
    } */
}

void Renderer::Draw(const DialogueSystem &dialogue)
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawBackground();

    if (dialogue.IsActive())
    {
        const auto &line = dialogue.CurrentLine();

        if (!line.portrait2.empty())
        {
            DrawPortrait(line.portrait, line.portrait2);
        }
        else
        {
            DrawPortrait(line.portrait);
        }

        //DrawDialogueBox(dialogue);

        if (dialogue.IsShowingChoice())
            DrawChoices(dialogue);
    }

    //EndDrawing();
}

void Renderer::DrawBackground()
{
    DrawTexture(background[0], 0, 0, WHITE);
}

// For drawing one character
void Renderer::DrawPortrait(const string &portrait)
{
    if (portrait.empty() || !portraits.count(portrait))
        return;

    Vector2 frame = portraits[portrait];

    // Crop 128x128 frame from the sheet to get the correct sprite
    Rectangle spriteSrc =
        {
            frame.x * FRAME_SIZE, // x offset into sheet
            frame.y * FRAME_SIZE, // y offset into sheet
            FRAME_SIZE,
            FRAME_SIZE};

    float drawSize = FRAME_SIZE * PORTRAIT_SCALE;

    Rectangle dest =
        {
            (800 - drawSize) / 2,
            320 - drawSize,
            drawSize,
            drawSize};

    // suni sprite sheet
    DrawTexturePro(spriteSheet[0], spriteSrc, dest, {0, 0}, 0.0f, WHITE);
}

// this draws two character at once
void Renderer::DrawPortrait(const string &portrait1, const string &portrait2)
{
    float drawSize = FRAME_SIZE * PORTRAIT_SCALE;

    // left side character
    if (!portrait1.empty() && portraits.count(portrait1))
    {
        Vector2 frame1 = portraits[portrait1];
        Rectangle spriteSrc1 = {
            frame1.x * FRAME_SIZE,
            frame1.y * FRAME_SIZE,
            FRAME_SIZE,
            FRAME_SIZE};
        Rectangle dest1 = {
            (800 / 3.0f) - (drawSize / 2.0f), // 1/3
            320 - drawSize,
            drawSize,
            drawSize};
        DrawTexturePro(spriteSheet[0], spriteSrc1, dest1, {0, 0}, 0.0f, WHITE);
    }

    // right side character
    if (!portrait2.empty() && portraits.count(portrait2))
    {
        Vector2 frame2 = portraits[portrait2];
        Rectangle spriteSrc2 = {
            frame2.x * FRAME_SIZE,
            frame2.y * FRAME_SIZE,
            FRAME_SIZE,
            FRAME_SIZE};
        Rectangle dest2 = {
            (800 * 2.0f / 3.0f) - (drawSize / 2.0f), // 2/3
            320 - drawSize,
            drawSize,
            drawSize};
        DrawTexturePro(spriteSheet[0], spriteSrc2, dest2, { 0, 0 }, 0.0f, WHITE); // REMEMBER TO CHANGE spriteSheet[1]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // nah lell i put evrrything in one sprite sheet lmao
    }
}

/* // dilogue box where the dialogue shows up
void Renderer::DrawDialogueBox(const DialogueSystem &dialogue)
{
    // select current line
    const auto &line = dialogue.CurrentLine();

    //box background and border
    DrawRectangle(0, 320, 800, 130, Fade(BLACK, 0.8f));
    DrawRectangleLines(0, 320, 800, 130, WHITE);

    //character name and dialogue
    DrawText(line.character.c_str(), 30, 330, 20, YELLOW);
    DrawText(line.text.c_str(), 30, 360, 18, WHITE);
} */

// this draws the choice box that will appere when there is a choice
void Renderer::DrawChoices(const DialogueSystem &dialogue)
{
    const auto &choices = dialogue.Choices();

    for (int i = 0; i < (int)choices.size(); i++)
    {
        // button rectangle
        // float x;                // Rectangle top-left corner position x
        // float y;                // Rectangle top-left corner position y
        // float width;            // Rectangle width
        // float height;           // Rectangle height
        Rectangle btn = {250, 150.f + i * 50, 300, 40};
        bool hover = CheckCollisionPointRec(GetMousePosition(), btn);

        // change button color between sleeected or not selected
        DrawRectangleRec(btn, hover ? DARKPURPLE : PINK);

        // choices label
        DrawText(choices[i].label.c_str(), (int)btn.x + 10, (int)btn.y + 10, 18, WHITE);
    }
}