#pragma once

#include <color.h>

struct clothNode
{
    bool fixed = false;

    int conAmnt;
    clothNode** cons;

    float x = 0; float y = 0;
    float vx = 0; float vy = 0;
    float ax = 0; float ay = 0;

    color c;

    void draw();
    void update();
};