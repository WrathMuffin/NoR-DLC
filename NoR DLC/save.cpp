#include "save.h"
#include <fstream>
#include <iostream>

bool SaveSystem::Save(const string& sceneId, float score, const string& path) {
    ofstream file(path);
    if (!file.is_open()) {
        cerr << "Failed to open save file for writing: " << path << "\n";
        return false;
    }

    file << sceneId << "\n";
    file << score   << "\n";

    cout << "Game saved." << endl;
    return true;
}

bool SaveSystem::Load(string& outSceneId, float& outScore, const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "No save file found at: " << path << "\n";
        return false;
    }

    if (!(getline(file, outSceneId) && file >> outScore)) {
        cerr << "Save file is corrupted: " << path << "\n";
        return false;
    }

    cout << "Game loaded. Scene: " << outSceneId << " Score: " << outScore << "\n";
    return true;
}