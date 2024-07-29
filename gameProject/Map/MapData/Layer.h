#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "../Physic/constants.h"

class Layer {
public:
    void loadLayer(const std::string& path, const std::string& textureID, int numTileSetX, int numTileSetY, int firstId);
    void drawLayer() const;

private:
    std::vector<Tile> tiles;
};
