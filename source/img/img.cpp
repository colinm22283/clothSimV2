#include <cstdlib>

#include <color.h>

#include <img/img.h>

img::img()
{
    width = 0;
    height = 0;
}
img::img(int _width, int _height)
{
    width = _width;
    height = _height;
}

img::~img()
{
    for (int x = 0; x < width; x++) free(pixels[x]);
    free(pixels);
}

void img::setPixel(int x, int y, color c)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    pixels[x][y] = c;
}
color img::getPixel(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return { 0, 0, 0, 0 };
    return pixels[x][y];
}