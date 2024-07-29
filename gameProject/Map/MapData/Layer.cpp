#include "Layer.h"
#include "../Camera.h"

void Layer::loadLayer(const std::string& path, const std::string& textureID, int numTileSetX, int numTileSetY, int firstId) {
    std::ifstream mapFile(path);
    if (!mapFile.is_open()) {
        std::cerr << "Failed to open map file: " << path << std::endl;
        return;
    }
    else {
        std::cout << "Open Success : " << path << std::endl;
    }

    int id = 0;
    for (int i = 0; i < NUM_MAP_X * NUM_MAP_Y; ++i) {
        mapFile >> id;
        if (mapFile.fail()) {
            std::cerr << "Error reading map file: " << path << std::endl;
            break;
        }
        id = id - firstId + 1;
        int x = (i % NUM_MAP_X) * TILE_SIZE;
        int y = (i / NUM_MAP_X) * TILE_SIZE;

        Tile tile(textureID, x, y, id, numTileSetX, numTileSetY);
        tiles.push_back(tile);
    }
    mapFile.close();
    std::cout << "Load successful: " << path << std::endl;
}

void Layer::drawLayer() const {
    for (const auto& tile : tiles) {
        if (Camera::getInstance()->isInViewBox(tile.getMapX(), tile.getMapY(), tile.tWidth(), tile.getHeight())) {
            tile.draw();
        }
    }
}
