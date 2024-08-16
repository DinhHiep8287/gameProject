#pragma once
#include "SDL.h"
#include "Game.h"
class Input
{
public: Input();
      void listen(SDL_Event& e);
      static Input* intance;
      static Input* getInstance()
      {
          return intance = (intance != nullptr) ? intance : new Input();
      }
      const Uint8* pKeyStates;
      bool getKeyDown(SDL_Scancode key);
      void keyUp();
      void keyDown();
};

