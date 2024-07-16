#include "Game.h"
#include "Input.h"
#include "Engine.h"
#include "Physic/Body.h"
#include "Physic/constants.h"
#include "Camera.h"

Game* Game::instance = nullptr;

Body body;

void Game::init()
{
    Engine::initSDL(window, renderer);
}

void Game::quit()
{
    running = false;
    menu = false;
}

void Game::update()
{
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
        body.setForceX(10); 
    }
    else if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
        body.setForceX(-10); 
    }
    else {
        body.unsetForce();
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
        body.jump();
    }

    body.update(deltaTime);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_Rect rect = body.getRectShape();
    Camera::getInstance()->setPoint(body.getPosition());
    SDL_Rect fillRect = { body.getPosition().getX() - Camera::getInstance()->getPoint().getX(), body.getPosition().getY() - Camera::getInstance()->getPoint().getY() , 20, 20}; // Một hình chữ nhật đại diện cho Body
    Camera::getInstance()->update(deltaTime);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Màu xanh
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderPresent(renderer);

    body.print();
}

void Game::render()
{
    SDL_RenderPresent(renderer);
}

void Game::event()
{
    Input::getInstance()->listen();
}

void Game::cleanSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
