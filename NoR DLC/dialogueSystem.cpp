#include "DialogueSystem.h"
#include <fstream>
#include <iostream>

//I searched that nlohmann is good
using json = nlohmann::json;

bool DialogueSystem::LoadFromFile(const string& path)
{
    ifstream file(path);

    //check and see if the json is able to open or not
    if (!file.is_open())
    {
        cerr << "Failed to open dialogue file: " << path << "\n";
        return false;
    }

    json data = json::parse(file, nullptr, false);

    if (data.is_discarded())
    {
        cerr << "Failed to parse JSON: " << path << "\n";
        return false;
    }

    // grabs json data ID'ed as scenes and set &s
    for (const auto& s : data["scenes"])
    {
        DialogueScene scene;
        scene.sceneId   = s.value("id",   "");
        scene.next = s.value("next", "");

        // lines are nestled within secens (s), so grab data ID'ed as lines from s and assign to &l
        for (const auto& l : s["lines"])
        {
            scene.lines.push_back
            (
                {
                l.value("character", ""),
                l.value("text",      ""),
                l.value("portrait",  ""),
                l.value("portrait2", "")
                }
            );
        }

        // ivce versa as above 
        for (const auto& c : s.value("choices", json::array()))
        {
            scene.choices.push_back
            (
                {
                c.value("label",      ""),
                c.value("next_scene", ""),
                c.value("score_change", 0.0f)
                }
            );
        }

        // convert the scene litss in json into array to use
        scenes[scene.sceneId] = move(scene);
    }

    cout << "Loaded " << scenes.size() << " scenes.\n";
    return true;
}

void DialogueSystem::GoToScene(const string& id, int lineId)
{
    auto sceneId = scenes.find(id);

    if (sceneId == scenes.end())
    {
        cerr << "Scene not found: " << id << "\n";
        active = false;
        return;
    }
    currentScene = &sceneId->second;
    lineIndex    = lineId;
    showChoices  = false;
    active       = true;
}

void DialogueSystem::StartScene(const string& sceneId, int lineId)
{
    // thet starts scne should be intro (based on json id)
    GoToScene(sceneId, lineId);
}

void DialogueSystem::Advance()
{
    if (!active || showChoices) return;

    lineIndex++;

    // More lines to show
    if (lineIndex < (int)currentScene->lines.size()) return;

    // End of lines — show choices or auto-advance
    if (!currentScene->choices.empty()) {

        showChoices = true;
        choiceJustShown = true;
    }

    else if (!currentScene->next.empty())
    {
        GoToScene(currentScene->next, 0);
    } 

    else
    {
        active = false; // dialogue complete
    }
}

void DialogueSystem::SelectChoice(int index)
{
    if (!showChoices) return;

    if (index < 0 || index >= (int)currentScene->choices.size()) return;

    GoToScene(currentScene->choices[index].nextScene, 0);
}

const DialogueLine& DialogueSystem::CurrentLine() const
{
    static DialogueLine empty{};

    if (!currentScene || lineIndex >= (int)currentScene->lines.size()) return empty;
    
    return currentScene->lines[lineIndex];
}

void DialogueSystem::Tick()
{
    if (choiceJustShown) choiceJustShown = false;
}

string DialogueSystem::GetCurrentSceneId() const
{
    if (!currentScene) return "";

    return currentScene->sceneId;
}

int DialogueSystem::GetCurrentLineId() const
{
    if (!lineIndex) return 0;

    return lineIndex;
}

void DialogueSystem::CheckScoreBranch(float normalizedScore, float conditionScore, const string& positiveScene, const string& negativeScene)
{
    if (normalizedScore >= conditionScore)
    {
        GoToScene(positiveScene, 0);
    }
    
    else
    {   
        GoToScene(negativeScene, 0);
    }
}