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
    //Simulation::grid[0][35].fixed = true;
    //Simulation::grid[35][35].fixed = true;
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
void Script::mouseClick(int button)
{
}