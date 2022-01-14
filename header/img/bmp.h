#pragma once

#include <string>

#include <color.h>

#include <img/img.h>

class bmp : public img
{
public:
    bmp(std::string path);
};