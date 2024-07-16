#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    //Khởi tạo
    Game::GetInstance()->init();
    // GAMELOOP
    while (Game::GetInstance()->isRunning())
    {
        Game::GetInstance()->event();
        Game::GetInstance()->update();
        Game::GetInstance()->render();
    }
    // THOÁT //
    Game::GetInstance()->cleanSDL();

    return 0;
}
