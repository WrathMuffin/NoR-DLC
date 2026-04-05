#pragma once
#include <string>

using namespace std;

class SaveSystem {
public:
    static bool Save(const string& sceneId, int lineId, float score, const string& path = "save.txt");

    static bool Load(string& outSceneId, int& outLineId, float& outScore, const string& path = "save.txt");
};