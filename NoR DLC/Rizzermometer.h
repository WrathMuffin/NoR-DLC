#pragma once
#include "ui.h"
#include <string>

using namespace std;

class Rizzermometer : public UI{
public:
    // rectangle properties
    Rizzermometer(float max, float x, float y, float width, float height);

    void Update() override;
    void Draw() override;

    void AddScore(float score);
    
    float GetScore() const
    { 
        return score; 
    }

    float GetNormalized() const 
    { 
        //for the UI display percentage and for checking the ending condition
        return score / maxScore; 
    } 

private:
    //rizzerommoteter's scores stuff
    float score;
    float displayScore;
    float maxScore;

    // rectangle borders
    float x, y, w, h;
};