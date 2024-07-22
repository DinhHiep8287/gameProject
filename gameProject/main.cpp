#include "Game.h"
#include "FrameRateController.h"

const int FPS = 120;

int main(int argc, char* argv[]) {
    //Khởi tạo
    FrameRateController frameRateController(FPS);
    Game::GetInstance()->init();
    // GAMELOOP
    while (Game::GetInstance()->isRunning())
    {
        frameRateController.startFrame();

        Game::GetInstance()->event();
        Game::GetInstance()->update();
        Game::GetInstance()->render();

        frameRateController.endFrame();
    }
    // THOÁT //
    Game::GetInstance()->cleanSDL();

    return 0;
}
