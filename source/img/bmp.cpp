#include <string>
#include <fstream>
#include <iostream>

#include <color.h>
#include <render.h>

#include <img/bmp.h>
#include <img/img.h>

bmp::bmp(std::string path)
{
    std::ifstream file(path, std::ios::binary);

    file.seekg(2);
    uint32_t size;
    file.read((char*)&size, sizeof(uint32_t));

    file.seekg(10);
    uint32_t pixOffset;
    file.read((char*)&pixOffset, sizeof(uint32_t));

    file.seekg(18);
    uint32_t _width;
    file.read((char*)&_width, sizeof(uint32_t));

    file.seekg(22);
    uint32_t _height;
    file.read((char*)&_height, sizeof(uint32_t));

    width = _width;
    height = _height;
    pixels = (color**)malloc(sizeof(color*) * width);
    for (int i = 0; i < (int)width; i++) pixels[i] = (color*)malloc(sizeof(color) * height);

    file.seekg(pixOffset);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < (int)width; x++)
        {
            file.read((char*)&pixels[x][y].b, sizeof(uint8_t));
            file.read((char*)&pixels[x][y].g, sizeof(uint8_t));
            file.read((char*)&pixels[x][y].r, sizeof(uint8_t));
        }
    }
}