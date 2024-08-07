#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include "../Physic/constants.h"

class Level {
public:
    void loadLayers(const std::vector<Layer*>& layers);
    void loadLayers(std::initializer_list<Layer*> layers);
    void drawLevel() const;
    void clearLayers();
    static void loadMatrix(const std::string& path);
    static bool isCollidingMap(SDL_Rect a, int level);
    static bool isCollidingMapX(SDL_Rect a, int level);
    static bool isCollidingMapY(SDL_Rect a, int level);
    const std::vector<std::vector<std::vector<int>>>& getMatrix() const;
    ~Level();

private:
    std::vector<Layer*> _layers;
    static std::vector<std::vector<std::vector<int>>> colisionLayerMatrix;
};
