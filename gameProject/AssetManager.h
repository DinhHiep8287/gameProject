#pragma once
#include "Game.h"
#include "Camera.h"
#include <SDL_image.h>
#include <iostream>
#include <map>
class AssetManager
{
public:
    static AssetManager* instance;
    static AssetManager* GetInstance() {
        return instance = (instance != nullptr) ? instance : new AssetManager;
    }
    
    std::map<std::string, SDL_Texture*> _textureMap;

    bool load(std::string id, std::string fileName);

    void drop(std::string id);

    void renderBackground(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed);

    void renderObject(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip);

    void renderObject(std::string id, float textureX, float textureY, float width, float height, float mapX, float mapY);

    float textureWidth(std::string id);
    
    float textureHeight(std::string id);
    

};

