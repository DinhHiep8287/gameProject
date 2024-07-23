#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Tile.h"

const int MAP_WIDTH = 128;
const int MAP_HEIGHT = 28;

class Layer {
public:
    void loadLayer(const std::string& path, int numTileSetX, int numTileSetY, int firstId) {
        std::ifstream mapFile(path);
        if (!mapFile.is_open()) {
            std::cerr << "Failed to open map file: " << path << std::endl;
            return;
        }

        for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; ++i) {
            int id = 0;
            mapFile >> id;
            id = id - firstId + 1;
            int x = (i % MAP_WIDTH) * TILE_SIZE;
            int y = (i / MAP_WIDTH) * TILE_SIZE;
            Tile tile()
            tiles.push_back(tile);
        }
        mapFile.close();
    }
    void drawLayer() const {
        for (const auto& tile : tiles) {
            tile.draw();
        }
    }

private:
    std::vector<Tile> tiles;
};