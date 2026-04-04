#pragma once
#include "ui.h"
#include <string>

using namespace std;

class Rizzermometer : public UI{
public:
    Rizzermometer(float max, float x, float y, float width, float height);

    void Update() override;
    void Draw()   override;

    void  AddScore(float score);
    float GetScore() const 
    { 
        return score; 
    }

    float GetNormalized() const 
    { 
        //for the UI display percentage
        return score / maxScore; 
    } 

private:
    float score;
    float displayScore;
    float maxScore;

    float x, y, w, h;
};