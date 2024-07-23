#include "Game.h"
#include "Input.h"
#include "Engine.h"
#include "Physic/Body.h"
#include "Physic/constants.h"
#include "Camera.h"
#include "AssetManager.h"
#include "Knight.h"

Game* Game::instance = nullptr;

Body testBody;

Knight testKnight("KnightIdle", 0, 0, 100, 200, MASS);

void initBackground() {
    for (const auto& pair : backgroundPaths) {
        AssetManager::GetInstance()->load(pair.first, pair.second);
    }
}

void renderBackground() {
    AssetManager::GetInstance()->renderBackground("background_1", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.5);
    AssetManager::GetInstance()->renderBackground("background_2", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.6);
    AssetManager::GetInstance()->renderBackground("background_3", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.7);
    AssetManager::GetInstance()->renderBackground("background_4", 0, 50, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.8);
    AssetManager::GetInstance()->renderBackground("background_5", 200, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.9);
}

void initKnightTexture() {
    for (const auto& pair : knightTexturePaths) {
        AssetManager::GetInstance()->load(pair.first, pair.second);
    }
}

void renderTest() {
    // init test Body
    SDL_Rect fillRect = { testBody.getPosition()->getX() - Camera::getInstance()->position.getX(), testBody.getPosition()->getY() - Camera::getInstance()->position.getY() , 20, 20 }; // Một hình chữ nhật đại diện cho Body
    SDL_SetRenderDrawColor(Game::GetInstance()->renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(Game::GetInstance()->renderer, &fillRect);
}

void Game::init()
{
    Engine::initSDL(window, renderer);
    initBackground();
    initKnightTexture();

    Camera::getInstance()->setPoint(testBody.getPosition());
}

void Game::update()
{
    /*if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
        testBody.setForceX(10); 
    }
    else if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
        testBody.setForceX(-10); 
    }
    else {
        testBody.unsetForce();
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
        testBody.jump();
    }*/

    testBody.update(deltaTime);
    testKnight.update(deltaTime);

    Camera::getInstance()->update(deltaTime);

}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    renderBackground();

    renderTest();

    testKnight.render();

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

void Game::quit()
{
    running = false;
    menu = false;
}

