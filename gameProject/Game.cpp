﻿#include "Game.h"
#include "Input.h"
#include "Engine.h"
#include "Physic/Body.h"
#include "Physic/constants.h"
#include "Camera.h"
#include "AssetManager.h"
#include "Knight.h"
#include "Map/MapData/Level.h"
#include "SDL_ttf.h"
#include "Monster.h"
Game* Game::instance = nullptr;

// Level
Level* level = new Level();
Layer* tileLayer = new Layer(); 
Layer* objectLayer1 = new Layer(); 
Layer* objectLayer2 = new Layer();


// Object
Body testBody;
Knight testKnight(100, 100, 40, 60, MASS);

Monster monster1(400, 450, 40, 100, MASS, FLYING_EYE);
Monster monster2(1250, 500, 40, 100, MASS, GOBLIN);
Monster monster3(2700, 550, 40, 100, MASS, SKELETON);
Monster monster4(3600, 560, 40, 100, MASS, MUSHROOM);
Monster monster5(3100, 200, 40, 100, MASS, GOBLIN);
Monster monster6(2300, -110, 40, 100, MASS, SKELETON);
Monster monster7(2300, 300, 40, 100, MASS, FLYING_EYE);
Monster monster8(1850, 570, 40, 100, MASS, MUSHROOM);
Monster monster9(1800, 100, 40, 100, MASS, SKELETON);
Monster monster10(1400, 200 , 40, 100, MASS, FLYING_EYE);
Monster monster11(3600, 200, 40, 100, MASS, GOBLIN);
//
void initBackground() {
    std::cout << "--Khoi tao Background: " << std::endl;
    for (const auto& pair : BACKGROUND_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initFont() {
    std::cout << "--Khoi tao Font: " << std::endl;
    for (const auto& pair : FONTS_PATHS) {
        AssetManager::GetInstance()->loadFont(pair.first, pair.second, DEFAULT_FONT_SIZE);
    }
}

void initKnightTexture() {
    std::cout << "--Khoi tao texture Knight: " << std::endl;
    for (const auto& pair : KNIGHT_TEXTURE_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initMonsterTexture(const std::map<std::string, std::string>& texturePaths, std::string monsterType) {
    std::cout << "--Khoi tao texture " << monsterType << ": " << std::endl;
    for (const auto& pair : texturePaths) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}


void initMapTexture() {
    std::cout << "--Khoi tao texture Map: " << std::endl;
    for (const auto& pair : MAP_TEXTURE_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initLevelData() {
    std::cout << "--Khoi tao du lieu ma tran map: " << std::endl;

    tileLayer->loadLayer(MAP_DATA_PATHS.at("tile_layer"), "tile_set", NUM_TILE_SET_X, NUM_TILE_SET_Y, FIRST_ID_TILE_SET);
    objectLayer1->loadLayer(MAP_DATA_PATHS.at("object_1_layer"), "object_1", NUM_OBJECT_1_X, NUM_OBJECT_1_Y, FIRST_ID_OBJECT_1);
    objectLayer2->loadLayer(MAP_DATA_PATHS.at("object_2_layer"), "object_2", NUM_OBJECT_2_X, NUM_OBJECT_2_Y, FIRST_ID_OBJECT_2);
    level->loadLayers({tileLayer, objectLayer1, objectLayer2});
    Level::loadMatrix(MAP_DATA_PATHS.at("tile_layer"));

    // Thêm Knight vào Level
    level->addKnight(&testKnight);

    // Thêm Monster vào Level
    level->addMonster(&monster1);
    level->addMonster(&monster2);
    level->addMonster(&monster3);
    level->addMonster(&monster4);
    level->addMonster(&monster5);
    level->addMonster(&monster6);
    level->addMonster(&monster7);
    level->addMonster(&monster8);
    level->addMonster(&monster9);
    level->addMonster(&monster10);
    level->addMonster(&monster11);
}

void renderBackground() {
    AssetManager::GetInstance()->renderBackground("background_1", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.5);
    AssetManager::GetInstance()->renderBackground("background_2", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.6);
    AssetManager::GetInstance()->renderBackground("background_3", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.7);
    AssetManager::GetInstance()->renderBackground("background_4", 0, 50, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.8);
    AssetManager::GetInstance()->renderBackground("background_5", 200, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.9);
}

void renderKnight() {
    testKnight.render();
    //SDL_Rect tempRect = { testKnight.getPosition().getX() - testKnight.getTextureWidth()/2, testKnight.getPosition().getY() - testKnight.getTextureHeight()/2, testKnight.getTextureWidth(), testKnight.getTextureHeight()};
    //AssetManager::GetInstance()->renderRect(tempRect);
    //AssetManager::GetInstance()->renderRect(testKnight.getBody()->getRectShape());
    testKnight.getBody()->renderText(0, 0);
    //testKnight.renderText(0, 0);
}

void renderMonster() {
    monster1.render();
    //SDL_Rect tempRect = { testMonster.getPosition().getX() - testMonster.getTextureWidth() / 2, testMonster.getPosition().getY() - testMonster.getTextureHeight() / 2, testMonster.getTextureWidth(), testMonster.getTextureHeight() };
    //AssetManager::GetInstance()->renderRect(testMonster.getBody()->getRectShape());
    //AssetManager::GetInstance()->renderRect(tempRect);
    //testMonster.renderText(0, 0);
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
    initMonsterTexture(FLYING_EYE_TEXTURE_PATHS, "FlyingEye");
    initMonsterTexture(GOBLIN_TEXTURE_PATHS, "Goblin");
    initMonsterTexture(MUSHROOM_TEXTURE_PATHS, "Mushroom");
    initMonsterTexture(SKELETON_TEXTURE_PATHS, "Skeleton");
    initMapTexture();
    initLevelData();

    Camera::getInstance()->setPoint(testKnight.getBody()->getPosition());
}

void Game::update()
{
    /*testKnight.update(deltaTime);
    testMonster.update(deltaTime);*/
    level->update(deltaTime);
    Camera::getInstance()->update(deltaTime);


}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    renderBackground();

    //level->drawLevel();

    level->render();

    testKnight.renderText(0, 0);

    //renderKnight();

    //renderMonster();

    //testMonster.renderText(0,0); 

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

