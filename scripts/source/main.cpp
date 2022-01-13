#include <math.h>
#include <iostream>

#include <global.h>
#include <script.h>
#include <engine.h>
#include <console.h>
#include <render.h>
#include <input.h>
#include <consoleParser.h>
#include <font.h>

#include <simulation.h>
#include <simConfig.h>

void Script::exit()
{
    Console::print("Exit");

    Engine::quit = true;
}

void Script::keyDown(SDL_Keysym keysym) { }

void Script::start()
{
    Global::fpsLimit = 1000;
    Global::fpsOutput = true;

    Simulation::generateGrid(50, 50, 400, 400, 10);
    Simulation::grid[0][0].fixed = true;
    Simulation::grid[35][0].fixed = true;
}
void Script::update()
{
    Render::clearScreen({ 255, 255, 255, 255 });
    
    Simulation::update();
}

void Script::mouseDown(int button)
{
    if (button == SDL_BUTTON_LEFT) Simulation::createForce(Input::mouseX, Input::mouseY, -1);
    if (button == SDL_BUTTON_RIGHT) Simulation::createForce(Input::mouseX, Input::mouseY, 1);
}
void Script::mouseClick(int button) { }

bool Script::setVar(std::string var, std::string value)
{
    if (var == "linelength") SimConfig::lineLength = std::stof(value);
    else if (var == "decay") SimConfig::decay = std::stof(value);
    else if (var == "gravity") SimConfig::gravity = std::stof(value);
    else return false;
    return true;
}
bool Script::command(std::string cmd, std::string params)
{
    std::string second = params.substr(0, params.find(' '));
    std::string nstr2 = params.substr(params.find(' ') + 1);
    std::string third = nstr2.substr(0, nstr2.find(' '));

    if (cmd == "generategrid")
    {
        std::string nstr3 = nstr2.substr(nstr2.find(' ') + 1);
        std::string fourth = nstr3.substr(0, nstr3.find(' '));
        std::string nstr4 = nstr3.substr(nstr3.find(' ') + 1);
        std::string fifth = nstr4.substr(0, nstr4.find(' '));
        std::string nstr5 = nstr4.substr(nstr4.find(' ') + 1);
        std::string sixth = nstr5.substr(0, nstr5.find(' '));

        Simulation::deleteGrid();
        Simulation::generateGrid(
            std::stof(second), std::stof(third),
            std::stof(fourth), std::stof(fifth),
            std::stof(sixth)
        );
    }
    else if (cmd == "pin") Simulation::pin(
        std::stoi(second),
        std::stoi(third)
    );
    else if (cmd == "unpin") Simulation::unpin(
        std::stoi(second),
        std::stoi(third)
    );
    else return false;
    return true;
}