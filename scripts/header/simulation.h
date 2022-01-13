#pragma once

#include <clothNode.h>

namespace Simulation
{
    extern int gridWidth;
    extern int gridHeight;
    extern clothNode** grid;

    void update();
    void deleteGrid();
    void generateGrid(float x, float y, float w, float h, float spacing);
    void createForce(float x, float y, float multiplier);
    void pin(int x, int y);
    void unpin(int x, int y);
}