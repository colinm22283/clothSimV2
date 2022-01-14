#include <math.h>
#include <iostream>
#include <random>

#include <render.h>

#include <simConfig.h>
#include <clothNode.h>

float min(float a, float b) { return a < b ? a : b; }
int sgn(float x) { return (0 < x) - (x < 0); }

void clothNode::draw()
{
    Render::setColor(c);
    Render::fillRect(x - 1, y - 1, 3, 3);
}

void clothNode::update()
{
    if (!fixed)
    {
        float tx = 0, ty = 0;

        for (int i = 0; i < conAmnt; i++)
        {
            float dx = cons[i]->x - x;
            float dy = cons[i]->y - y;
            float mag = sqrtf32(powf32(dx, 2) + powf32(dy, 2));

            tx += dx * (mag - SimConfig::lineLength) * SimConfig::clothMult;
            ty += dy * (mag - SimConfig::lineLength) * SimConfig::clothMult;
        }

        tx += vx + SimConfig::vx;
        ty += vy + SimConfig::vy;

        if (abs(tx) < SimConfig::maxForce) x += tx;
        else x += sgn(tx) * SimConfig::maxForce;
        if (abs(ty) < SimConfig::maxForce) y += ty;
        else y += sgn(ty) * SimConfig::maxForce;

        vx *= SimConfig::decay;
        vy *= SimConfig::decay;

        vx += ax + ((float)std::rand() / (float)RAND_MAX * SimConfig::wind);
        vy += ay + SimConfig::gravity;
    }
}