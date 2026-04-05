#pragma once
#include <string>

using namespace std;

class SaveSystem {
public:
    // scenen id = location, line id = what line ur on, scor eis for the rizzeromometer, path default
    static bool Save(const string& sceneId, int lineId, float score, const string& path = "save.txt");

    // ditto above brehh
    static bool Load(string& outSceneId, int& outLineId, float& outScore, const string& path = "save.txt");
};