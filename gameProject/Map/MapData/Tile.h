#pragma once
#include <SDL.h>
#include "../AssetManager.h"
#include "../Camera.h"

const int TILE_SIZE = 32;

class Tile {
public:
    Tile(std::string textureID, int mapX, int mapY, int id, int numTilesetX, int numTilesetY, int width = TILE_SIZE, int height = TILE_SIZE);

    void draw() const;

private:
    std::string textureID;
    int mapX;
    int mapY;
    int textureX;
    int textureY;
    int width;
    int height;
};

Tile::Tile(std::string textureID, int mapX, int mapY, int id, int numTilesetX, int numTilesetY, int width, int height)
    :  mapX(mapX), mapY(mapY), width(width), height(height) {
    textureX = (id % numTilesetX == 0) ? (numTilesetX - 1) * TILE_SIZE : (id % numTilesetX - 1) * TILE_SIZE;
    textureY = (id % numTilesetX == 0) ? (id / numTilesetX - 1) * TILE_SIZE : (id / numTilesetX) * TILE_SIZE;
}

void Tile::draw() const{
    AssetManager::GetInstance()->renderObject(textureID, textureX, textureY, width, height, mapX, mapY);
}
