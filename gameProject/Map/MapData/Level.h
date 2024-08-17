#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "../Physic/constants.h"
#include "../Menu.h"
class Knight;
class Monster;

class Level {
public:
    Level() {
        // Panel
        int panelWidth = SIZE * 15;
        int panelHeight = SIZE * 12;
        int panelX = (NUM_SCREEN_X * SIZE - panelWidth) / 2;
        int panelY = (NUM_SCREEN_Y * SIZE - panelHeight) / 2;
        pauseMenu.addPanel(std::make_unique<Panel>("PausePanel", "Pause", "panelTexture", panelX, panelY, panelWidth, panelHeight));

        // Buttons
        int buttonWidth = SIZE * 7;
        int buttonHeight = SIZE * 1.5;
        int firstButtonY = panelY + SIZE * 2;
        int buttonX = panelX + (panelWidth - buttonWidth) / 2;

        pauseMenu.addButton(std::make_unique<Button>("Continue", "Continue", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY, buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("Settings", "Settings", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + buttonHeight + SIZE, buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("Replay", "Replay", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 2 * (buttonHeight + SIZE), buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("BackToMenu", "Back to Menu", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 3 * (buttonHeight + SIZE), buttonWidth, buttonHeight));

        // Pause Button
        int pauseButtonWidth = SIZE * 1.5;
        int pauseButtonHeight = SIZE * 1.5;
        int pauseButtonX = NUM_SCREEN_X * SIZE - pauseButtonWidth - SIZE;
        int pauseButtonY = SIZE;
        pauseButton = std::make_unique<Button>("Pause", "", "pauseNormalButtonTexture", "pauseHoveredButtonTexture", pauseButtonX, pauseButtonY, pauseButtonWidth, pauseButtonHeight);
    }

    void loadLayers(const std::vector<Layer*>& layers);
    void loadLayers(std::initializer_list<Layer*> layers);
    void drawLevel() const;
    void clearLayers();
    void resetLevel(); 
    static void loadMatrix(const std::string& path);
    static bool isCollidingMap(SDL_Rect a, int level);
    static std::vector<std::vector<std::vector<int>>> getMatrix();

    // Quản lý Knight và Monster
    
    void addKnight(Knight* knight);
    void addMonster(Monster* monster);
    std::vector<Monster*> getMonsters() { return _monsters; }
    Knight* getKnight() { return _knight; }
    int getLevelIndex() { return levelIndex; }
    void update(float dt);
    void render();

    ~Level();

    Menu pauseMenu;
    std::unique_ptr<Button> pauseButton;

private:
    std::vector<Layer*> _layers;
    static std::vector<std::vector<std::vector<int>>> colisionLayerMatrix;
    int levelIndex;
    // Danh sách Knight và Monster
    Knight* _knight;
    std::vector<Monster*> _monsters;
};
