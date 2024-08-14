#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "../Physic/constants.h"

class Knight;
class Monster;

class Level {
public:
    void loadLayers(const std::vector<Layer*>& layers);
    void loadLayers(std::initializer_list<Layer*> layers);
    void drawLevel() const;
    void clearLayers();
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

private:
    std::vector<Layer*> _layers;
    static std::vector<std::vector<std::vector<int>>> colisionLayerMatrix;
    int levelIndex;
    // Danh sách Knight và Monster
    Knight* _knight;
    std::vector<Monster*> _monsters;
};
