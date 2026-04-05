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
    string portrait2;
};

struct DialogueChoice {
    string label;
    string nextScene;
    float scoreChange = 0.0f;
};

struct DialogueScene {
    string sceneId, lineId; // gto grabs the scene name and current dialogue text
    string next; //advance if no choices
    vector<DialogueLine>   lines;
    vector<DialogueChoice> choices;
};

class DialogueSystem {
public:
    bool LoadFromFile(const string& path);

    void StartScene(const string& sceneId, int lineId);
    void Advance();          // next line or scene
    void SelectChoice(int index);

    bool IsActive()       const { return active; }
    bool IsShowingChoice()const { return showChoices; }
    

    const DialogueLine& CurrentLine() const;
    const vector<DialogueChoice>& Choices()   const { return currentScene->choices; }

    void Tick();

    string GetCurrentSceneId() const;
    int GetCurrentLineId() const;

    void CheckScoreBranch(float normalizedScore, const string& positiveScene, const string& negativeScene);

private:
    unordered_map<string, DialogueScene> scenes;
    const DialogueScene* currentScene = nullptr;
    int  lineIndex  = 0;
    bool active     = false;
    bool showChoices= false;
    bool choiceJustShown = false;

    void GoToScene(const string& id, int lineIndex); // aded ability to jump lines for save :D
};