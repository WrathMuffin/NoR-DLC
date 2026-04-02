#include "DialogueSystem.h"
#include <fstream>
#include <iostream>

//I searched that nlohmann is good
using json = nlohmann::json;

bool DialogueSystem::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open dialogue file: " << path << "\n";
        return false;
    }

    json data = json::parse(file, nullptr, /*exceptions=*/false);
    if (data.is_discarded()) {
        std::cerr << "Failed to parse JSON: " << path << "\n";
        return false;
    }

    for (const auto& s : data["scenes"]) {
        DialogueScene scene;
        scene.id   = s.value("id",   "");
        scene.next = s.value("next", "");

        for (const auto& l : s["lines"]) {
            scene.lines.push_back({
                l.value("character", ""),
                l.value("text",      ""),
                l.value("portrait",  "")
            });
        }

        for (const auto& c : s.value("choices", json::array())) {
            scene.choices.push_back({
                c.value("label",      ""),
                c.value("next_scene", "")
            });
        }

        scenes[scene.id] = std::move(scene);
    }

    std::cout << "Loaded " << scenes.size() << " scenes.\n";
    return true;
}

void DialogueSystem::GoToScene(const std::string& id) {
    auto it = scenes.find(id);
    if (it == scenes.end()) {
        std::cerr << "Scene not found: " << id << "\n";
        active = false;
        return;
    }
    currentScene = &it->second;
    lineIndex    = 0;
    showChoices  = false;
    active       = true;
}

void DialogueSystem::StartScene(const std::string& sceneId) {
    GoToScene(sceneId);
}

void DialogueSystem::Advance() {
    if (!active || showChoices) return;

    lineIndex++;

    // More lines to show
    if (lineIndex < (int)currentScene->lines.size()) return;

    // End of lines — show choices or auto-advance
    if (!currentScene->choices.empty()) {
        showChoices = true;
    } else if (!currentScene->next.empty()) {
        GoToScene(currentScene->next);
    } else {
        active = false; // dialogue complete
    }
}

void DialogueSystem::SelectChoice(int index) {
    if (!showChoices) return;
    if (index < 0 || index >= (int)currentScene->choices.size()) return;

    GoToScene(currentScene->choices[index].nextScene);
}

const DialogueLine& DialogueSystem::CurrentLine() const {
    static DialogueLine empty{};
    if (!currentScene || lineIndex >= (int)currentScene->lines.size())
        return empty;
    return currentScene->lines[lineIndex];
}