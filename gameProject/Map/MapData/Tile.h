#pragma once
#include <SDL.h>
#include "../AssetManager.h"
#include "../Camera.h"

const int TILE_SIZE = 32;

class Tile {
public:
    Tile(const std::string& textureID, int mapX, int mapY, int id, int numTilesetX, int numTilesetY, int width = TILE_SIZE, int height = TILE_SIZE);

    void draw() const;

    const std::string& getTextureID() const { return textureID; }
    int getMapX() const { return mapX; }
    int getMapY() const { return mapY; }
    int getTextureX() const { return textureX; }
    int getTextureY() const { return textureY; }
    int tWidth() const { return width; }
    int getHeight() const { return height; }

private:
    std::string textureID;
    int mapX;
    int mapY;
    int textureX;
    int textureY;
    int width;
    int height;
};
