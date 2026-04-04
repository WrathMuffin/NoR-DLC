#pragma once
#include "raylib.h"
#include "DialogueSystem.h"
#include <unordered_map>
#include <string>

using namespace std;

class Renderer
{
public:
    void Load();
    void Unload();
    void Draw(const DialogueSystem &dialogue);

private:
    void DrawBackground();
    void DrawPortrait(const string &portrait);
    void DrawDialogueBox(const DialogueSystem &dialogue);
    void DrawChoices(const DialogueSystem &dialogue);

    Texture2D background[3];
    Texture2D spriteSheet[2];

    // this contains the name and the column + row from the spriteSheet, key(string name) and value(column and row)
    unordered_map<string, Vector2> portraits;

    static constexpr int FRAME_SIZE = 128;
    static constexpr float PORTRAIT_SCALE = 2.0f;
};