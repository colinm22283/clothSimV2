#include <math.h>
#include <vector>
#include <iostream>

#include <simulation.h>
#include <simConfig.h>

int Simulation::gridWidth = 0;
int Simulation::gridHeight = 0;
clothNode** Simulation::grid = nullptr;

float max(float a, float b) { return a > b ? a : b; }

void Simulation::update()
{
    for (int x = 0; x < gridWidth; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            grid[x][y].update();
            grid[x][y].draw();
        }
    }
}

void Simulation::deleteGrid()
{
    free(grid);

    // for (int x = 0; x < gridWidth; x++)
    // {
    //     for (int y = 0; y < gridHeight; y++)
    //     {
    //         std::cout << grid[x][y].conAmnt << "\n";
    //         free(grid[x][y].cons);
    //     }
    //     free(grid[x]);
    // }
}
void Simulation::generateGrid(float _x, float _y, float w, float h, float spacing)
{
    gridWidth = floor((w - _x) / spacing) + 1;
    gridHeight = floor((h - _y) / spacing) + 1;

    grid = (clothNode**)malloc(sizeof(clothNode*) * gridWidth);
    for (int x = 0; x < gridWidth; x++)
    {
        grid[x] = (clothNode*)malloc(sizeof(clothNode) * gridHeight);
        for (int y = 0; y < gridHeight; y++)
        {
            grid[x][y] = {
                false,
                0, nullptr,
                x * spacing + _x, y * spacing + _y, 0, 0, 0, 0,
                { 0, 255, 0, 0 }
            };
        }
    }

    for (int x = 0; x < gridWidth; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            std::vector<clothNode*> temp;

            if (x > 0)
            {
                temp.push_back(&grid[x - 1][y]);
            }
            if (x < gridWidth - 1)
            {
                temp.push_back(&grid[x + 1][y]);
            }
            if (y > 0)
            {
                temp.push_back(&grid[x][y - 1]);
            }
            if (y < gridHeight - 1)
            {
                temp.push_back(&grid[x][y + 1]);
            }

            grid[x][y].conAmnt = temp.size();
            grid[x][y].cons = (clothNode**)malloc(sizeof(clothNode*) * temp.size());
            for (int i = 0; i < (int)temp.size(); i++) grid[x][y].cons[i] = temp[i];
        }
    }
}

void Simulation::createForce(float _x, float _y, float multiplier)
{
    for (int x = 0; x < Simulation::gridWidth; x++)
    {
        for (int y = 0; y < Simulation::gridHeight; y++)
        {
            float dx = grid[x][y].x - _x;
            float dy = grid[x][y].y - _y;
            float mag = sqrtf32(powf32(dx, 2) + powf32(dy, 2));

            grid[x][y].vx = dx / mag * max(0, 300 - mag) * multiplier * SimConfig::moveMult;
            grid[x][y].vy = dy / mag * max(0, 300 - mag) * multiplier * SimConfig::moveMult;
        }
    }
}

void Simulation::pin(int x, int y) { grid[x][y].fixed = true; }
void Simulation::unpin(int x, int y) { grid[x][y].fixed = false; }