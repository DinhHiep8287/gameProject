﻿#include "Game.h"
#include "Menu.h"
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
// Game
Game* Game::instance = nullptr;
Menu mainMenu;
Setting settingsMenu(100, 100, 300, 400);
// Level
Level* level = new Level();
std::vector<Layer*> layers(NUM_LAYERS);

// Object
Knight* player;
std::vector<Monster*> monsters;
void initSound() {
    std::cout << "--Khoi tao Sound: " << std::endl;
    for (const auto& pair : SOUND_PATHS) {
        AssetManager::GetInstance()->loadSound(pair.first, pair.second);
    }
}

void initMusic() {
    std::cout << "--Khoi tao Music: " << std::endl;
    for (const auto& pair : MUSIC_PATHS) {
        AssetManager::GetInstance()->loadMusic(pair.first, pair.second);
    }
}

void initMenuItems() {
    int panelWidth = SIZE * 8;
    int panelHeight = SIZE * 10;
    int panelX = (NUM_SCREEN_X * SIZE - panelWidth) / 2;
    int panelY = (NUM_SCREEN_Y * SIZE - panelHeight) / 2;

    // Thêm Panel vào Menu
    mainMenu.addPanel(std::make_unique<Panel>("Panel", "Menu", "panelTexture", panelX, panelY, panelWidth, panelHeight));

    // Tính toán vị trí của các nút
    int buttonWidth = SIZE * 6; // Ví dụ: mỗi nút có chiều rộng 6 ô
    int buttonHeight = SIZE * 1.5; // Ví dụ: mỗi nút có chiều cao 1.5 ô
    int buttonX = panelX + (panelWidth - buttonWidth) / 2; // Căn giữa trong Panel

    int startButtonY = panelY + SIZE * 2; // Vị trí Y của nút "Start" cách đỉnh Panel 2 ô
    int settingsButtonY = startButtonY + buttonHeight + SIZE * 0.5; // Vị trí Y của nút "Settings" dưới nút "Start" một khoảng nhỏ
    int quitButtonY = settingsButtonY + buttonHeight + SIZE * 0.5; // Vị trí Y của nút "Quit" dưới nút "Settings" một khoảng nhỏ

    // Thêm Button "Start" vào Menu
    mainMenu.addButton(std::make_unique<Button>("Start", "Start", "buttonNormalTexture", "buttonHoveredTexture", buttonX, startButtonY, buttonWidth, buttonHeight));

    // Thêm Button "Settings" vào Menu
    mainMenu.addButton(std::make_unique<Button>("Settings", "Settings", "buttonNormalTexture", "buttonHoveredTexture", buttonX, settingsButtonY, buttonWidth, buttonHeight));

    // Thêm Button "Quit" vào Menu
    mainMenu.addButton(std::make_unique<Button>("Quit", "Quit", "buttonNormalTexture", "buttonHoveredTexture", buttonX, quitButtonY, buttonWidth, buttonHeight));
}

void initKnight() {
    player = new Knight(250, 700, 40, 60, MASS);
}

void initMonsters() {
    for (const auto& info : monstersInfo) {
        int x, y, mass;
        MonsterType type;
        std::tie(x, y, mass, type) = info;
        monsters.push_back(new Monster(x, y, mass, type));
    }
}

void initBackground() {
    std::cout << "--Khoi tao Background: " << std::endl;
    for (const auto& pair : BACKGROUND_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initFont() {
    std::cout << "--Khoi tao Font: " << std::endl;
    for (const auto& pair : FONTS_PATHS) {
        const std::string& fontName = pair.first;
        const std::string& fontPath = pair.second.first;
        int fontSize = pair.second.second;
        AssetManager::GetInstance()->loadFont(fontName, fontPath, fontSize);
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

void initMenuTexture() {
    std::cout << "--Khoi tao texture Menu: " << std::endl;
    for (const auto& pair : MENU_TEXTURE_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initMapTexture() {
    std::cout << "--Khoi tao texture Map: " << std::endl;
    for (const auto& pair : MAP_TEXTURE_PATHS) {
        AssetManager::GetInstance()->loadTexture(pair.first, pair.second);
    }
}

void initMatrix() {
    Level::loadMatrix(MAP_DATA_PATHS.at("tile_layer"));
}

void initLevelData() {
    std::cout << "--Khoi tao du lieu Level: " << std::endl;
    layers[TILE_LAYER] = new Layer();
    layers[OBJECT_LAYER1] = new Layer();
    layers[OBJECT_LAYER2] = new Layer();

    layers[TILE_LAYER]->loadLayer(MAP_DATA_PATHS.at("tile_layer"), "tile_set", NUM_TILE_SET_X, NUM_TILE_SET_Y, FIRST_ID_TILE_SET);
    layers[OBJECT_LAYER1]->loadLayer(MAP_DATA_PATHS.at("object_1_layer"), "object_1", NUM_OBJECT_1_X, NUM_OBJECT_1_Y, FIRST_ID_OBJECT_1);
    layers[OBJECT_LAYER2]->loadLayer(MAP_DATA_PATHS.at("object_2_layer"), "object_2", NUM_OBJECT_2_X, NUM_OBJECT_2_Y, FIRST_ID_OBJECT_2);

    level->loadLayers(layers);

    // Thêm Knight vào Level
    level->addKnight(player);

    // Thêm Monster vào Level
    level->addMonster(monsters);
}

void renderBackground() {
    AssetManager::GetInstance()->renderBackground("background_1", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.5);
    AssetManager::GetInstance()->renderBackground("background_2", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.6);
    AssetManager::GetInstance()->renderBackground("background_3", 0, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.7);
    AssetManager::GetInstance()->renderBackground("background_4", 0, 50, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.8);
    AssetManager::GetInstance()->renderBackground("background_5", 200, 0, backgroundWidth, backgroundHeight, SDL_FLIP_NONE, 0.9);
}

void resetLevel() {
    // Dọn dẹp Knight
    if (player) {
        player->clean();
        delete player;
        player = nullptr;
    }

    // Dọn dẹp Monsters
    for (auto monster : monsters) {
        if (monster) {
            monster->clean();
            delete monster;
        }
    }
    monsters.clear();

    // Dọn dẹp các Layer
    level->clearLayers();

    level->score = 0;

    std::cout << "Level da duoc don dep." << std::endl;

    // Tạo lại Knight và Monsters sau khi dọn dẹp
    initKnight();
    initMonsters();

    // Tạo lại dữ liệu level
    initLevelData();

    // Đặt lại camera
    Camera::getInstance()->setPoint(player->getBody()->getPosition());

    std::cout << "Level da duoc reset." << std::endl;
}

void Game::init()
{
    Engine::initSDL(window, renderer);
    Engine::initTTF();
    Engine::initMixer();
    
    initSound();
    initMusic();
    initKnight();
    initMonsters();
    initFont();
    initBackground();
    initKnightTexture();
    initMonsterTexture(FLYING_EYE_TEXTURE_PATHS, "FlyingEye");
    initMonsterTexture(GOBLIN_TEXTURE_PATHS, "Goblin");
    initMonsterTexture(MUSHROOM_TEXTURE_PATHS, "Mushroom");
    initMonsterTexture(SKELETON_TEXTURE_PATHS, "Skeleton");
    initMenuTexture();
    initMapTexture();
    initMatrix();
    initLevelData();
    initMenuItems();

    Camera::getInstance()->setPoint(player->getBody()->getPosition());
}

void Game::update()
{
    if (state == PAUSED || state == MENU || state == SETTINGS) {
        return; // Dừng cập nhật khi game đang ở trạng thái PAUSED
    }
    if (state == PLAYING) {
        level->update(deltaTime);
        Camera::getInstance()->update(deltaTime);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    if (state == PLAYING)
    {
        renderBackground();

        level->render();

    }
    else if (state == MENU ) {
        renderBackground();
        AssetManager::GetInstance()->renderText(renderer, "Steel Knight", "DungeonFont", { 0, 0, 0 }, 275, 25);
        mainMenu.render(renderer);
    }
    else if (state == SETTINGS) {
        renderBackground();
        settingsMenu.render(renderer);
    }
    else if (state == PAUSED) {
        renderBackground();

        level->render();

        level->pauseMenu.render(renderer);
    }
    else if (state == GAMEOVER) {
        renderBackground();

        level->render();

        level->gameOverMenu.updateLabel("Score", std::to_string(level->score));
        level->gameOverMenu.updateLabel("HighScore", std::to_string(level->highScore));

        level->gameOverMenu.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::event() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        // Lắng nghe các sự kiện chung thông qua Input
        Input::getInstance()->listen(e);

        // Xử lý sự kiện dựa trên trạng thái game
        if (state == MENU) {
            // Phát nhạc
            AssetManager::GetInstance()->playMusic("menuMusic", -1);

            int selectedItem = mainMenu.handleEvent(e);

            // Kiểm tra chỉ mục của Button đã được nhấn
            if (selectedItem != -1) {
                switch (selectedItem) {
                case 0: // Button "Start"
                    state = PLAYING; // Start Game
                    break;
                case 1: // Button "Settings"
                    previousState = MENU;
                    state = SETTINGS; // Open Settings
                    break;
                case 2: // Button "Quit"
                    quit(); // Quit Game
                    break;
                default:
                    break;
                }
            }
        }
        else if (state == PLAYING) {
            // Phát nhạc
            AssetManager::GetInstance()->playMusic("gameMusic", -1);

            if (level->pauseButton && level->pauseButton->handleEvent(e)) {
                state = PAUSED;
            }
        }
        else if (state == SETTINGS) {
            // Phát nhạc hoặc âm thanh cài đặt nếu cần
            AssetManager::GetInstance()->playMusic("menuMusic", -1);

            int selectedSetting = settingsMenu.handleEvent(e);

            if (selectedSetting != -1) {
                switch (selectedSetting) {
                case 0: // Increase Music Volume
                    AssetManager::GetInstance()->increaseMusicVolume();
                    settingsMenu.updateLabel("MusicVolume", std::to_string(AssetManager::GetInstance()->getMusicVolume()));
                    break;
                case 1: // Decrease Music Volume
                    AssetManager::GetInstance()->decreaseMusicVolume();
                    settingsMenu.updateLabel("MusicVolume", std::to_string(AssetManager::GetInstance()->getMusicVolume()));
                    break;
                case 2: // Increase SFX Volume
                    AssetManager::GetInstance()->increaseSFXVolume();
                    settingsMenu.updateLabel("SFXVolume", std::to_string(AssetManager::GetInstance()->getSFXVolume()));
                    break;
                case 3: // Decrease SFX Volume
                    AssetManager::GetInstance()->decreaseSFXVolume();
                    settingsMenu.updateLabel("SFXVolume", std::to_string(AssetManager::GetInstance()->getSFXVolume()));
                    break;
                case 4: // Mute/Unmute
                    if (AssetManager::GetInstance()->isMuted()) {
                        AssetManager::GetInstance()->unmuteVolume();
                        settingsMenu.updateButtonTexture("Mute", "unmuteNormalButtonTexture", "unmuteHoveredButtonTexture");
                    }
                    else {
                        AssetManager::GetInstance()->muteVolume();
                        settingsMenu.updateButtonTexture("Mute", "muteNormalButtonTexture", "muteHoveredButtonTexture");
                    }
                    break;
                case 5: // Back
                    state = previousState; // Quay lại trạng thái trước đó
                    break;
                default:
                    break;
                }
            }
        }

        else if (state == PAUSED) {
            // Xử lý các sự kiện liên quan đến trạng thái PAUSED
            int selectedPauseOption = level->pauseMenu.handleEvent(e);

            if (selectedPauseOption != -1) {
                switch (selectedPauseOption) {
                case 0: // Continue
                    state = PLAYING; // Tiếp tục game
                    break;
                case 1: // Settings
                    previousState = PAUSED; // Lưu trạng thái hiện tại
                    state = SETTINGS; // Mở cài đặt
                    break;
                case 2: // Replay
                    resetLevel(); // Chơi lại
                    state = PLAYING;
                    break;
                case 3: // Back to Menu
                    state = MENU; // Quay lại menu chính
                    break;
                default:
                    break;
                }
            }
        }
        else if (state == GAMEOVER) {
            int selectedPauseOption = level->gameOverMenu.handleEvent(e);

            if (selectedPauseOption != -1) {
                switch (selectedPauseOption) {
                case 0: // Replay
                    resetLevel(); // Chơi lại
                    state = PLAYING;
                    break;
                case 1: // Back to Menu
                    state = MENU; // Quay lại menu chính
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void Game::cleanSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::quit()
{
    level->saveHighScore();
    state = EXIT;
}

