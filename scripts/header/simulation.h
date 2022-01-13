#pragma once

#include <color.h>

#include <clothNode.h>
#include <connection.h>

namespace Simulation
{
    extern int gridWidth;
    extern int gridHeight;
    extern clothNode** grid;
    extern int conAmnt;
    extern connection* cons;

    void update();
    void deleteGrid();
    void generateGrid(float x, float y, float w, float h, float spacing);
    void createForce(float x, float y, float multiplier);
    void pin(int x, int y);
    void unpin(int x, int y);
    void setColor(int x, int y, color c);
    void loadImage(std::string path);
}