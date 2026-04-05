#pragma once
#include "ui.h"
#include "DialogueSystem.h"

class DialogueBox : public UI {
public:
    //constructor
    DialogueBox(int x, int y, int width, int height);

    void Update() override;
    void Draw()   override;

    void SetDialogue(const DialogueSystem* dialogue);

private:
    //sizes
    int x, y, w, h;
    //pointer to current dialogue system
    const DialogueSystem* dialogue = nullptr;
};