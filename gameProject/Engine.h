#pragma once
#include <SDL.h>
#include <iostream>
#include "Physic/constants.h"

const std::string WINDOW_TITLE = "STEEL KNIGHT";

class Engine {
public:
    static void logSDLError(std::ostream& os, const std::string& msg, bool fatal);
    static void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
    static void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
};

