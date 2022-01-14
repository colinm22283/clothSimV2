#pragma once

#include <color.h>

class img
{
public:
    img();
    img(int _width, int _height);
    
    ~img();

    int width;
    int height;

    void setPixel(int x, int y, color c);
    color getPixel(int x, int y);

    void draw();
    void draw(int x, int y);
    void draw(int x, int y, float scale);
protected:
    color** pixels;
};