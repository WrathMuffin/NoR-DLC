#pragma once
#include "raylib.h"

class UI {
public:
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    //virtual destructor
    virtual ~UI(){}
};