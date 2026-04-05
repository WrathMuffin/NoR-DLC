#pragma once
#include "raylib.h"

// for rizzerometer
class UI {
public:
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    //virtual destructor
    virtual ~UI(){}
};