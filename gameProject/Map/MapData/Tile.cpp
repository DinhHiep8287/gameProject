#include "Tile.h"
#include "../Physic/constants.h"

Tile::Tile(const std::string& _textureID, int _mapX, int _mapY, int _id, int _numTilesetX, int _numTilesetY, int _width, int _height)
    : textureID(_textureID), mapX(_mapX), mapY(_mapY), width(_width), height(_height) {
    textureX = (_id % _numTilesetX == 0) ? (_numTilesetX - 1) * TILE_SIZE : (_id % _numTilesetX - 1) * TILE_SIZE;
    textureY = (_id % _numTilesetX == 0) ? (_id / _numTilesetX - 1) * TILE_SIZE : (_id / _numTilesetX) * TILE_SIZE;
}

void Tile::draw() const {
    AssetManager* assetManager = AssetManager::GetInstance();
    if (assetManager) {
        if (!textureID.empty()) {
            assetManager->renderObject(textureID, textureX, textureY, width, height, mapX, mapY);
        }
        else {
            std::cerr << "Invalid textureID: " << textureID << std::endl;
        }
    }
    else {
        std::cerr << "AssetManager instance is not initialized!" << std::endl;
    }
}
