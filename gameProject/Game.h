#pragma once
#include <SDL.h>

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    SETTINGS,
    EXIT
};

class Game
{
public:
    static Game* instance;
    static Game* GetInstance() {
        return instance = (instance != nullptr) ? instance : new Game;
    }
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameState state = MENU;

    void init();
    void quit();
    void update();
    void render();
    void event();
    void cleanSDL();

};

