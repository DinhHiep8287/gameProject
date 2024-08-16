#include "Game.h"
#include "FrameRateController.h"

const int FPS = 60;

int main(int argc, char* argv[]) {
    //Khởi tạo
    FrameRateController frameRateController(FPS);
    Game::GetInstance()->init();
    // GAMELOOP
    while (Game::GetInstance()->state != EXIT)
    {
        frameRateController.startFrame();

        Game::GetInstance()->event();
        Game::GetInstance()->update();
        Game::GetInstance()->render();

        frameRateController.endFrame();
        
        //frameRateController.printFPS();
    }
    // THOÁT //
    Game::GetInstance()->cleanSDL();

    return 0;
}
