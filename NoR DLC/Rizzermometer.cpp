#include "Rizzermometer.h"
#include <algorithm>

//constructor
Rizzermometer::Rizzermometer(float max, float x, float y, float width, float height)
    : score(0), displayScore(0), maxScore(max), x(x), y(y), w(width), h(height) {}

void Rizzermometer::AddScore(float change)
{
    score = clamp(score + change, (float)0, maxScore);
}

void Rizzermometer::Update()
{
    //This basically lerps the score bar so it is smooth
    float speed = GetFrameTime() * 2;

    //lerp towards current score
    if (displayScore < score) 
    {
        displayScore = min(displayScore + speed * maxScore, score);
    }

    if (displayScore > score) 
    {
        displayScore = max(displayScore - speed * maxScore, score);
    }
}

// the bar, may replace with a sprite
void Rizzermometer::Draw()
{
    float fill = (displayScore / maxScore) * w;

    //Background
    DrawRectangle((int)x, (int)y, (int)w, (int)h, DARKGRAY);

    //Filled portion — color shifts green to red based on score
    Color barColor = ColorLerp(WHITE, PINK, displayScore / maxScore);
    DrawRectangle((int)x, (int)y, (int)fill, (int)h, barColor);

    //Border
    DrawRectangleLines((int)x, (int)y, (int)w, (int)h, WHITE);

    //Label
    DrawText("Rizzermometer", (int)x, (int)y -20, 16, WHITE);
}