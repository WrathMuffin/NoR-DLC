#include "dialogueBox.h"

//constructor
DialogueBox::DialogueBox(int x, int y, int width, int height)
    : x(x), y(y), w(width), h(height) {}

void DialogueBox::SetDialogue(const DialogueSystem* d) 
{
    dialogue = d;
}

void DialogueBox::Update() 
{
    //did not add anything but it is required because of UI Update() being pure virtual
}

void DialogueBox::Draw() 
{
    if (!dialogue || !dialogue->IsActive()) return;

    //select current line
    const auto& line = dialogue->CurrentLine();

    //box background and border
    DrawRectangle(x, y, w, h, Fade(BLACK, 0.8f));
    DrawRectangleLines(x, y, w, h, WHITE);

    //character name and dialogue
    DrawText(line.character.c_str(), x + 30, y + 10, 20, YELLOW);
    DrawText(line.text.c_str(),      x + 30, y + 40, 18, WHITE);
}