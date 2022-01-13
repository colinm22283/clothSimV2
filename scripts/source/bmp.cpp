#include <string>
#include <fstream>
#include <iostream>

#include <color.h>
#include <render.h>

#include <bmp.h>

bmp BMP::loadImage(std::string path)
{
    bmp proto = { 0, 0, nullptr };

    std::ifstream file(path, std::ios::binary);

    file.seekg(2);
    uint32_t size;
    file.read((char*)&size, sizeof(uint32_t));

    file.seekg(10);
    uint32_t pixOffset;
    file.read((char*)&pixOffset, sizeof(uint32_t));

    file.seekg(18);
    uint32_t width;
    file.read((char*)&width, sizeof(uint32_t));

    file.seekg(22);
    uint32_t height;
    file.read((char*)&height, sizeof(uint32_t));

    proto.width = width;
    proto.height = height;
    proto.pixels = (color**)malloc(sizeof(color*) * width);
    for (int i = 0; i < (int)width; i++) proto.pixels[i] = (color*)malloc(sizeof(color) * height);

    file.seekg(pixOffset);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < (int)width; x++)
        {
            file.read((char*)&proto.pixels[x][y].b, sizeof(uint8_t));
            file.read((char*)&proto.pixels[x][y].g, sizeof(uint8_t));
            file.read((char*)&proto.pixels[x][y].r, sizeof(uint8_t));
        }
    }

    return proto;
}

void BMP::draw(bmp b)
{
    for (int x = 0; x < b.width; x++)
    {
        for (int y = 0; y < b.height; y++)
        {
            Render::fillRect(x * 10, y * 10, 10, 10, b.pixels[x][y]);
        }
    }
}