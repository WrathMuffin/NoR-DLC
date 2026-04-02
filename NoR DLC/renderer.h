#pragma once
#include "raylib.h"
#include "DialogueSystem.h"
#include <unordered_map>
#include <string>

using namespace std;

class Renderer {
public:
    void Load();
    void Unload();
    void Draw(const DialogueSystem& dialogue);

private:
    void DrawBackground();
    void DrawPortrait(const string& portrait);
    void DrawDialogueBox(const DialogueSystem& dialogue);
    void DrawChoices(const DialogueSystem& dialogue);

    Texture2D background;
    unordered_map<string, Texture2D> portraits;
};