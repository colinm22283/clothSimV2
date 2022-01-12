#include <math.h>
#include <iostream>

#include <render.h>

#include <simConfig.h>
#include <clothNode.h>

float min(float a, float b) { return a < b ? a : b; }
int sgn(float x) { return (0 < x) - (x < 0); }

void clothNode::draw()
{
    Render::setColor({ 255, 0, 0, 0 });
    Render::fillRect(x - 1, y - 1, 3, 3);

    for (int i = 0; i < conAmnt; i++)
    {
        Render::drawLine(x, y, cons[i]->x, cons[i]->y);
    }
}

void clothNode::update()
{
    Render::setColor({ 255, 0, 0, 0 });
    Render::fillRect(x - 2, y - 2, 4, 4);

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

        vx += ax;
        vy += ay + SimConfig::gravity;
    }
}