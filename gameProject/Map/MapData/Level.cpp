#include "Level.h"
#include <iostream>
#include <fstream>
#include "../Knight.h"
#include "../Monster.h"
// Định nghĩa biến static
std::vector<std::vector<std::vector<int>>> Level::colisionLayerMatrix;

void Level::loadLayers(const std::vector<Layer*>& layers) {
    for (auto layer : layers) {
        _layers.push_back(layer);
    }
}

void Level::loadLayers(std::initializer_list<Layer*> layers) {
    for (auto layer : layers) {
        _layers.push_back(layer);
    }
}

void Level::drawLevel() const {
    for (const auto& layer : _layers) {
        layer->drawLayer();
    }
}

void Level::clearLayers() {
    for (auto layer : _layers) {
        delete layer;
    }
    _layers.clear();
}

void Level::loadMatrix(const std::string& path) {
    std::ifstream mapFile(path);
    if (!mapFile.is_open()) {
        std::cerr << "Failed to open matrix file: " << path << std::endl;
        return;
    }

    std::vector<std::vector<int>> tempColisionLayerMatrix(NUM_MAP_Y, std::vector<int>(NUM_MAP_X, 0));

    for (int i = 0; i < NUM_MAP_Y; ++i) {
        for (int j = 0; j < NUM_MAP_X; ++j) {
            if (!(mapFile >> tempColisionLayerMatrix[i][j])) {
                std::cerr << "Error reading matrix file: " << path << std::endl;
                return;
            }
        }
    }

    colisionLayerMatrix.push_back(tempColisionLayerMatrix);

    mapFile.close();
    std::cout << "Matrix load successful: " << path << std::endl;
}

bool Level::isCollidingMap(SDL_Rect a, int level) {
    int tileSize = TILE_SIZE;
    int mapWidth = colisionLayerMatrix[level][0].size();
    int mapHeight = colisionLayerMatrix[level].size();

    int leftTile = a.x / tileSize;
    int rightTile = (a.x + a.w) / tileSize;
    int topTile = a.y / tileSize;
    int botTile = (a.y + a.h) / tileSize;

    leftTile = std::max(0, std::min(leftTile, mapWidth - 1));
    rightTile = std::max(0, std::min(rightTile, mapWidth - 1));
    topTile = std::max(0, std::min(topTile, mapHeight - 1));
    botTile = std::max(0, std::min(botTile, mapHeight - 1));

    if (a.x < 0 || a.x + a.w > mapWidth * tileSize) {
        return true;
    }

    for (int i = leftTile; i <= rightTile; ++i) {
        for (int j = topTile; j <= botTile; ++j) {
            if (colisionLayerMatrix[level][j][i] > 0) {
                return true;
            }
        }
    }

    return false;
}

const std::vector<std::vector<std::vector<int>>>& Level::getMatrix() const {
    return colisionLayerMatrix;
}

void Level::addKnight(Knight* knight) {
    _knight = knight;
}

void Level::addMonster(Monster* monster) {
    _monsters.push_back(monster);
}

void Level::update(float dt) {
    for (auto monster : _monsters) {
        if (monster) {
            monster->update(dt);
            if (_knight && monster->findKnightInRange(_knight->getPosition()) && monster->getIsDamageFrame()) {
                std::cout << "gay sat thuong\n";
                _knight->takeDamage(MONSTER_ATTACK_DAMAGE);
                std::cout << _knight->getHealth() << std::endl;
            }
        }
    }
    if (_knight) {
        _knight->update(dt);
        if (_knight->getState() == ATTACKING && _knight->getIsDamageFrame()) {
            for (auto monster : _monsters) {
                if (monster && _knight->findMonsterInRange(monster->getPosition())) {
                    std::cout << "gay sat thuong\n";
                    monster->takeDamage(KNIGHT_ATTACK_DAMAGE);
                    std::cout << monster->getHealth() << std::endl;
                }
            }
        }
    }

}


void Level::render() {
    drawLevel();

    for (auto monster : _monsters) {
        if (monster) {
            monster->render();
        }
    }

    if (_knight) {
        _knight->render();
    }
}

Level::~Level() {
    clearLayers();
}
