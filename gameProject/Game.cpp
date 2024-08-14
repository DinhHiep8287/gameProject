#include "Game.h"
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
std::vector<Layer*> layers(NUM_LAYERS);

// Object
Body testBody;
Knight* player;
std::vector<Monster*> monsters;

void initKnight() {
    player = new Knight(1000, 700, 40, 60, MASS);
}

void initMonsters() {
    for (const auto& info : monstersInfo) {
        int x, y, width, height, mass;
        MonsterType type;
        std::tie(x, y, width, height, mass, type) = info;
        monsters.push_back(new Monster(x, y, width, height, mass, type));
    }
}
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
    layers[TILE_LAYER] = new Layer();
    layers[OBJECT_LAYER1] = new Layer();
    layers[OBJECT_LAYER2] = new Layer();

    layers[TILE_LAYER]->loadLayer(MAP_DATA_PATHS.at("tile_layer"), "tile_set", NUM_TILE_SET_X, NUM_TILE_SET_Y, FIRST_ID_TILE_SET);
    layers[OBJECT_LAYER1]->loadLayer(MAP_DATA_PATHS.at("object_1_layer"), "object_1", NUM_OBJECT_1_X, NUM_OBJECT_1_Y, FIRST_ID_OBJECT_1);
    layers[OBJECT_LAYER2]->loadLayer(MAP_DATA_PATHS.at("object_2_layer"), "object_2", NUM_OBJECT_2_X, NUM_OBJECT_2_Y, FIRST_ID_OBJECT_2);

    level->loadLayers(layers);

    Level::loadMatrix(MAP_DATA_PATHS.at("tile_layer"));

    // Thêm Knight vào Level
    level->addKnight(player);

    // Thêm Monster vào Level
    for (auto& monster : monsters) {
        level->addMonster(monster);
    }
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
    Engine::initTTF();

    initKnight();
    initMonsters();
    initFont();
    initBackground();
    initKnightTexture();
    initMonsterTexture(FLYING_EYE_TEXTURE_PATHS, "FlyingEye");
    initMonsterTexture(GOBLIN_TEXTURE_PATHS, "Goblin");
    initMonsterTexture(MUSHROOM_TEXTURE_PATHS, "Mushroom");
    initMonsterTexture(SKELETON_TEXTURE_PATHS, "Skeleton");
    initMapTexture();
    initLevelData();

    Camera::getInstance()->setPoint(player->getBody()->getPosition());
}

void Game::update()
{
    level->update(deltaTime);
    Camera::getInstance()->update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    renderBackground();

    level->render();

    player->renderText(0, 0);
    //level->getMonsters().at(1)->renderText(0, 0);

    player->renderRectShape();

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

