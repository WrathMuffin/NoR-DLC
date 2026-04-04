#include "renderer.h"

// to load textures, our game is small enough so we chose to just load everything in
void Renderer::Load()
{
    // background = LoadTexture("assets/bg_forest.png");

    spriteSheet[0] = LoadTexture("assets/Suni_128_x_128.png");
    // spriteSheet[1] = LoadTexture("assets/Suni_128_x_128.png");

    portraits["suniNeutral"] = {0, 0};
    portraits["suniAngry"] = {1, 0};
    portraits["suniHappy"] = {2, 0};
    portraits["suniDizzy"] = {3, 0};
    portraits["suniBlank"] = {4, 0};
}

// to unload textures to free up memory (at the end of the program)
void Renderer::Unload()
{
    UnloadTexture(background[3]);
    UnloadTexture(spriteSheet[2]);

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
        const auto& line = dialogue.CurrentLine();

        if (!line.portrait2.empty())
        {
            DrawPortrait(line.portrait, line.portrait2);
        }
        else
        {
            DrawPortrait(line.portrait);
        }

        DrawDialogueBox(dialogue);

        if (dialogue.IsShowingChoice())
            DrawChoices(dialogue);
    }

    EndDrawing();
}

void Renderer::DrawBackground()
{
    DrawTexture(background[0], 0, 0, WHITE);
}

//For drawing one character
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
            drawSize
        };

    // suni sprite sheet
    DrawTexturePro(spriteSheet[0], spriteSrc, dest, {0, 0}, 0.0f, WHITE);
}

//this draws two character at once
void Renderer::DrawPortrait(const string &portrait1, const string &portrait2)
{
    float drawSize = FRAME_SIZE * PORTRAIT_SCALE;

    //left side character
    if (!portrait1.empty() && portraits.count(portrait1))
    {
        Vector2 frame1 = portraits[portrait1];
        Rectangle spriteSrc1 = {
            frame1.x * FRAME_SIZE,
            frame1.y * FRAME_SIZE,
            FRAME_SIZE,
            FRAME_SIZE
        };
        Rectangle dest1 = {
            (800 / 3.0f) - (drawSize / 2.0f),  //1/3
            320 - drawSize,
            drawSize,
            drawSize
        };
        DrawTexturePro(spriteSheet[0], spriteSrc1, dest1, {0, 0}, 0.0f, WHITE);
    }

    //right side character
    if (!portrait2.empty() && portraits.count(portrait2))
    {
        Vector2 frame2 = portraits[portrait2];
        Rectangle spriteSrc2 = {
            frame2.x * FRAME_SIZE,
            frame2.y * FRAME_SIZE,
            FRAME_SIZE,
            FRAME_SIZE
        };
        Rectangle dest2 = {
            (800 * 2.0f / 3.0f) - (drawSize / 2.0f),  //2/3
            320 - drawSize,
            drawSize,
            drawSize
        };
        DrawTexturePro(spriteSheet[0], spriteSrc2, dest2, {0, 0}, 0.0f, WHITE);  //REMEMBER TO CHANGE spriteSheet[1]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
}

// dilogue box where the dialogue shows up
void Renderer::DrawDialogueBox(const DialogueSystem &dialogue)
{
    // select current line
    const auto &line = dialogue.CurrentLine();

    // the box
    DrawRectangle(0, 320, 800, 130, Fade(BLACK, 0.8f));
    DrawRectangleLines(0, 320, 800, 130, WHITE);

    // charaater name
    DrawText(line.character.c_str(), 30, 330, 20, YELLOW);

    // characetr dialogue
    DrawText(line.text.c_str(), 30, 360, 18, WHITE);
}

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
        DrawRectangleRec(btn, hover ? DARKGRAY : GRAY);

        // choices label
        DrawText(choices[i].label.c_str(), (int)btn.x + 10, (int)btn.y + 10, 18, WHITE);
    }
}