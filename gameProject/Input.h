#pragma once
#include "SDL.h"
#include "Game.h"
class Input
{
public: Input();
      static Input* intance;
      static Input* getInstance()
      {
          return intance = (intance != nullptr) ? intance : new Input();
      }
      const Uint8* pKeyStates;
      SDL_Event e;
      void listen();
      bool getKeyDown(SDL_Scancode key);
      void keyUp();
      void keyDown();
};

