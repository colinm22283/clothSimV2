#pragma once

#include <string>

#include <color.h>

struct bmp
{
    int width; int height;
    color** pixels;
};

namespace BMP
{
    bmp loadImage(std::string path);
    void draw(bmp b);
}