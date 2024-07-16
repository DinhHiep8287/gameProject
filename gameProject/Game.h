#pragma once
#include <SDL.h>
class Game
{
public:
    static Game* instance;
    static Game* GetInstance() {
        return instance = (instance != nullptr) ? instance : new Game;
    }
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running = true;
    bool menu = true;
    
    bool isRunning() { return running; }
    bool isMenu() { return menu; }
    void init();
    void quit();
    void update();
    void render();
    void event();
    void cleanSDL();

};

