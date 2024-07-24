#include "Game.h"
#include "Input.h"
#include "Engine.h"
#include "Physic/Body.h"
#include "Physic/constants.h"
#include "Camera.h"
#include "AssetManager.h"
#include "Knight.h"
#include "SDL_ttf.h"

Game* Game::instance = nullptr;

Body testBody;

Knight testKnight("KnightIdle", 0, 0, 0, 0, MASS);

void initBackground() {
    for (const auto& pair : backgroundPaths) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void renderBackground() {
    AssetManager::GetInstance()->renderBackground("background_1", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.5);
    AssetManager::GetInstance()->renderBackground("background_2", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.6);
    AssetManager::GetInstance()->renderBackground("background_3", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.7);
    AssetManager::GetInstance()->renderBackground("background_4", 0, 50, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.8);
    AssetManager::GetInstance()->renderBackground("background_5", 200, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.9);
}

void initFont() {
    for (const auto& pair : FONTS_PATHS) {
        AssetManager::GetInstance()->loadFont(pair.first, pair.second, DEFAULT_FONT_SIZE);
    }
}

void initKnightTexture() {
    for (const auto& pair : KNIGHT_TEXTURE_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}



void renderKnight() {
    testKnight.render();
    SDL_Rect tempRect = { testKnight.getPosition().getX(), testKnight.getPosition().getY(), testKnight.getTextureWidth(), testKnight.getTextureHeight() };
    AssetManager::GetInstance()->renderRect(tempRect);
    AssetManager::GetInstance()->renderRect(testKnight.getBody()->getRectShape());
    testKnight.getBody()->renderText(0, 0);
    //testKnight.renderText(0, 0);
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
    Engine::initTTF();

    initFont();
    initBackground();
    initKnightTexture();

    Camera::getInstance()->setPoint(testKnight.getBody()->getPosition());
}

void Game::update()
{
    testKnight.update(deltaTime);

    Camera::getInstance()->update(deltaTime);


}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    renderBackground();

    renderKnight();

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

