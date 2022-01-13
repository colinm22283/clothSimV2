#include <math.h>
#include <vector>
#include <iostream>

#include <render.h>

#include <simulation.h>
#include <simConfig.h>
#include <connection.h>
#include <bmp.h>

int Simulation::gridWidth = 0;
int Simulation::gridHeight = 0;
clothNode** Simulation::grid = nullptr;
int Simulation::conAmnt = 0;
connection* Simulation::cons = nullptr;

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

    for (int i = 0; i < conAmnt; i++)
    {
        Render::setColor(grid[cons[i].fx][cons[i].fy].c);

        clothNode g1 = grid[cons[i].fx][cons[i].fy];
        clothNode g2 = grid[cons[i].tx][cons[i].ty];

        Render::drawLine(g1.x, g1.y, g2.x, g2.y);
    }
}

void Simulation::deleteGrid()
{
    free(grid);
    free(cons);
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
                { 255, 0, 0, 0 }
            };
        }
    }

    for (int x = 0; x < gridWidth; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            std::vector<int> tempx;
            std::vector<int> tempy;

            if (x > 0)
            {
                tempx.push_back(x - 1);
                tempy.push_back(y);
            }
            if (x < gridWidth - 1)
            {
                tempx.push_back(x + 1);
                tempy.push_back(y);
            }
            if (y > 0)
            {
                tempx.push_back(x);
                tempy.push_back(y - 1);
            }
            if (y < gridHeight - 1)
            {
                tempx.push_back(x);
                tempy.push_back(y + 1);
            }

            grid[x][y].conAmnt = tempx.size();
            grid[x][y].cons = (clothNode**)malloc(sizeof(clothNode*) * tempx.size());
            for (int i = 0; i < (int)tempx.size(); i++) grid[x][y].cons[i] = &grid[tempx[i]][tempy[i]];
        }
    }

    int conI = 0;
    cons = (connection*)malloc(
        sizeof(connection) *
        (2 * gridWidth * gridHeight - gridWidth - gridHeight)
    );
    conAmnt = 2 * gridWidth * gridHeight - gridWidth - gridHeight;

    for (int x = 0; x < gridWidth; x++)
    {
        for (int y = 0; y < gridHeight; y++)
        {
            if (x < gridWidth - 1)
            {
                cons[conI] = (connection){ x, y, x + 1, y };
                conI++;
            }
            if (y < gridHeight - 1)
            {
                cons[conI] = (connection){ x, y, x, y + 1 };
                conI++;
            }
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
void Simulation::setColor(int x, int y, color c) { grid[x][y].c = c; }
void Simulation::loadImage(std::string path)
{
    bmp img = BMP::loadImage(path);

    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            Simulation::setColor(x, y, img.pixels[x][y]);
        }
    }
}