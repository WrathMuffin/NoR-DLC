#pragma once
#include <string>

using namespace std;

class SaveSystem {
public:
    static bool Save(const string& sceneId, float score, const string& path = "save.txt");
    static bool Load(string& outSceneId, float& outScore, const string& path = "save.txt");
};