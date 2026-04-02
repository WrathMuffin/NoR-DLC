#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "json.hpp"

struct DialogueLine {
    std::string character;
    std::string text;
    std::string portrait;
};

struct DialogueChoice {
    std::string label;
    std::string nextScene;
};

struct DialogueScene {
    std::string id;
    std::string next;                    // auto-advance if no choices
    std::vector<DialogueLine>   lines;
    std::vector<DialogueChoice> choices;
};

class DialogueSystem {
public:
    bool LoadFromFile(const std::string& path);

    void StartScene(const std::string& sceneId);
    void Advance();          // next line or scene
    void SelectChoice(int index);

    bool IsActive()       const { return active; }
    bool IsShowingChoice()const { return showChoices; }
    

    const DialogueLine& CurrentLine() const;
    const std::vector<DialogueChoice>& Choices()   const { return currentScene->choices; }

private:
    std::unordered_map<std::string, DialogueScene> scenes;
    const DialogueScene* currentScene = nullptr;
    int  lineIndex  = 0;
    bool active     = false;
    bool showChoices= false;

    void GoToScene(const std::string& id);
};