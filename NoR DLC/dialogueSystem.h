#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"

using namespace std;

struct DialogueLine {
    string character;
    string text;
    string portrait;
};

struct DialogueChoice {
    string label;
    string nextScene;
};

struct DialogueScene {
    string id;
    string next;                    // auto-advance if no choices
    vector<DialogueLine>   lines;
    vector<DialogueChoice> choices;
};

class DialogueSystem {
public:
    bool LoadFromFile(const string& path);

    void StartScene(const string& sceneId);
    void Advance();          // next line or scene
    void SelectChoice(int index);

    bool IsActive()       const { return active; }
    bool IsShowingChoice()const { return showChoices; }
    

    const DialogueLine& CurrentLine() const;
    const vector<DialogueChoice>& Choices()   const { return currentScene->choices; }

private:
    unordered_map<string, DialogueScene> scenes;
    const DialogueScene* currentScene = nullptr;
    int  lineIndex  = 0;
    bool active     = false;
    bool showChoices= false;

    void GoToScene(const string& id);
};