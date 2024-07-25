#pragma once
#include <string>
#include <vector>
#include "Layer.h"
#include <initializer_list> 

class Level {
public:
    void loadLayers(const std::vector<Layer*>& layers) {
        for (auto layer : layers) {
            _layers.push_back(layer);
        }
    }

    void loadLayers(std::initializer_list<Layer*> layers) {
        for (auto layer : layers) {
            _layers.push_back(layer);
        }
    }


    void drawLevel() const {
        for (const auto& layer : _layers) {
            layer->drawLayer();
        }
    }

    void clearLayers() {
        for (auto layer : _layers) {
            delete layer;
        }
        _layers.clear();
    }

    ~Level() {
        clearLayers();
    }

private:
    std::vector<Layer*> _layers;
};

