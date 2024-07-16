#include "Input.h"
#include <iostream>
using namespace std;
Input* Input::intance = nullptr;
Input::Input()
{
    pKeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::listen()
{
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            Game::GetInstance()->quit();
            break;
        case SDL_KEYDOWN:
            keyDown();
            break;
        case SDL_KEYUP: 
            keyUp();
            break;
        default:
            break;
        }
    }
}

bool Input::getKeyDown(SDL_Scancode key)
{
    return (pKeyStates[key] == 1);
}

void Input::keyUp()
{
    pKeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown()
{
    pKeyStates = SDL_GetKeyboardState(nullptr);
}
