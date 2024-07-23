#include "Game.h"
#include "Input.h"
#include "Engine.h"
#include "Physic/Body.h"
#include "Physic/constants.h"
#include "Camera.h"
#include "AssetManager.h"

Game* Game::instance = nullptr;

Body body;


void initBackground() {
    AssetManager::GetInstance()->load("background_1", backgroundPath1);
    AssetManager::GetInstance()->load("background_2", backgroundPath2);
    AssetManager::GetInstance()->load("background_3", backgroundPath3);
    AssetManager::GetInstance()->load("background_4", backgroundPath4);
    AssetManager::GetInstance()->load("background_5", backgroundPath5);
}

void renderBackground() {
    AssetManager::GetInstance()->renderBackground("background_1", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.5);
    AssetManager::GetInstance()->renderBackground("background_2", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.6);
    AssetManager::GetInstance()->renderBackground("background_3", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.7);
    AssetManager::GetInstance()->renderBackground("background_4", 0, 50, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.8);
    AssetManager::GetInstance()->renderBackground("background_5", 200, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.9);
}

void Game::init()
{
    Engine::initSDL(window, renderer);
    initBackground();
    Camera::getInstance()->setPoint(body.getPosition());
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
    //Camera::getInstance()->setPoint(body.getPosition());
    SDL_Rect fillRect = { body.getPosition()->getX() - Camera::getInstance()->position.getX(), body.getPosition()->getY() - Camera::getInstance()->position.getY() , 20, 20}; // Một hình chữ nhật đại diện cho Body
    Camera::getInstance()->update(deltaTime);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
    SDL_RenderFillRect(renderer, &fillRect);
    SDL_RenderPresent(renderer);

    //body.print();
}

void Game::render()
{
    renderBackground();

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
