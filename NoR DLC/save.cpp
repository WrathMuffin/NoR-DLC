#include "save.h"
#include <fstream>
#include <iostream>

bool SaveSystem::Save(const string& sceneId, int lineId, float score, const string& path)
{
    // readfile from path
    ofstream file(path);

    // cant open txt file
    if (!file.is_open())
    {
        cerr << "Failed to open save file for writing: " << path << "\n";
        return false;
    }

    // grabs the value per line and assign to scenen id, lineid, and score from file
    file << sceneId << "\n";
    file << lineId << "\n";
    file << score << "\n";

    cout << "\nGame saved to " << path << " succesfully!\n";
    return true;
}

bool SaveSystem::Load(string& outSceneId, int& outLineId, float& outScore, const string& path)
{
    // read save file
    ifstream file(path);

    // error stufffe
    if (!file.is_open())
    {
        cerr << "\nNo save file found at: " << path << "\n";
        return false;
    }

    if (!(getline(file, outSceneId)&& file >> outLineId && file >> outScore ))
    {
        cerr << "Save file is corrupted, RIP lol, check: " << path << "?\n";
        return false;
    }

    // loaded save file sucesfully yeeyeyye
    cout << "\nGame loaded! Have fun gamers! \nCurrent scene: " << outSceneId << "\nCurrent line: " << outLineId << "\n" << "\nRizz score: " << outScore << "\n";
    return true;
}