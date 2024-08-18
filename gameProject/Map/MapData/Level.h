#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "../Physic/constants.h"
#include "../Menu.h"
#include "../Engine.h"
class Knight;
class Monster;

class Level {
public:
    Level() {
        readHighScore();
        // Panel
        int panelWidth = SIZE * 15;
        int panelHeight = SIZE * 12;
        int panelX = (NUM_SCREEN_X * SIZE - panelWidth) / 2;
        int panelY = (NUM_SCREEN_Y * SIZE - panelHeight) / 2;
        pauseMenu.addPanel(std::make_unique<Panel>("PausePanel", "Pause", "panelTexture", panelX, panelY, panelWidth, panelHeight));
        gameOverMenu.addPanel(std::make_unique<Panel>("GameOverPanel", "Game Over", "panelTexture", panelX, panelY, panelWidth, panelHeight));
        // Buttons
        int buttonWidth = SIZE * 7;
        int buttonHeight = SIZE * 1.5;
        int firstButtonY = panelY + SIZE * 2;
        int buttonX = panelX + (panelWidth - buttonWidth) / 2;

        pauseMenu.addButton(std::make_unique<Button>("Continue", "Continue", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY, buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("Settings", "Settings", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + buttonHeight + SIZE, buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("Replay", "Replay", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 2 * (buttonHeight + SIZE), buttonWidth, buttonHeight));
        pauseMenu.addButton(std::make_unique<Button>("BackToMenu", "Back to Menu", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 3 * (buttonHeight + SIZE), buttonWidth, buttonHeight));

       
        gameOverMenu.addLabel(std::make_unique<Label>("Score", "Score: " + std::to_string(score), "fontGame", SDL_Color{ 255, 255, 255, 255 }, buttonX, firstButtonY, buttonWidth, buttonHeight));
        gameOverMenu.addLabel(std::make_unique<Label>("HighScore", "High Score: " + std::to_string(highScore), "fontGame", SDL_Color{ 255, 255, 255, 255 }, buttonX, firstButtonY + buttonHeight + SIZE, buttonWidth, buttonHeight));
        gameOverMenu.addButton(std::make_unique<Button>("Replay", "Replay", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 2 * (buttonHeight + SIZE), buttonWidth, buttonHeight));
        gameOverMenu.addButton(std::make_unique<Button>("BackToMenu", "Back to Menu", "buttonNormalTexture", "buttonHoveredTexture", buttonX, firstButtonY + 3 * (buttonHeight + SIZE), buttonWidth, buttonHeight));
        // Pause Button
        int pauseButtonWidth = SIZE * 1.5;
        int pauseButtonHeight = SIZE * 1.5;
        int pauseButtonX = NUM_SCREEN_X * SIZE - pauseButtonWidth - SIZE;
        int pauseButtonY = SIZE;

        pauseButton = std::make_unique<Button>("Pause", "", "pauseNormalButtonTexture", "pauseHoveredButtonTexture", pauseButtonX, pauseButtonY, pauseButtonWidth, pauseButtonHeight);
        //HeathBar
        _healthBar = new HealthBar(40, 10, 200, 20);
    }

    void loadLayers(const std::vector<Layer*>& layers);
    void loadLayers(std::initializer_list<Layer*> layers);
    void drawLevel() const;
    void clearLayers(); 
    static void loadMatrix(const std::string& path);
    static bool isCollidingMap(SDL_Rect a, int level);
    static std::vector<std::vector<std::vector<int>>> getMatrix();

    // Quản lý Knight và Monster
    
    void addKnight(Knight* knight);
    void addMonster(std::vector<Monster*> monsters);
    std::vector<Monster*> getMonsters() { return _monsters; }
    Knight* getKnight() { return _knight; }
    int getLevelIndex() { return levelIndex; }
    void update(float dt);
    void render();

    ~Level();
    HealthBar* _healthBar;
    Menu pauseMenu;
    Menu gameOverMenu;
    std::unique_ptr<Button> pauseButton;
    int score = 0; // Điểm số của Level
    int highScore = 0; // Điểm cao nhất

    void addScore(int points) {
        score += points;
        if (score > highScore) {
            highScore = score;
        }
    }

    void saveHighScore() {
        std::ofstream outFile(HIGHSCORE_PATH);
        if (outFile.is_open()) {
            outFile << highScore;
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file for writing high score!" << std::endl;
        }
    }

    void readHighScore() {
        std::ifstream inFile(HIGHSCORE_PATH);
        if (inFile.is_open()) {
            inFile >> highScore;
            inFile.close();
        }
        else {
            std::cerr << "Unable to open file for reading high score!" << std::endl;
            highScore = 0; // Khởi tạo HighScore nếu file không tồn tại
        }
    }

private:
    std::vector<Layer*> _layers;
    static std::vector<std::vector<std::vector<int>>> colisionLayerMatrix;
    int levelIndex;
    // Danh sách Knight và Monster
    Knight* _knight;
    std::vector<Monster*> _monsters;
};
