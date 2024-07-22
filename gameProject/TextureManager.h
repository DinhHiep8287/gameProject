﻿#pragma once
#include "Game.h"
#include "Camera.h"
#include <SDL_image.h>
#include <iostream>
#include <map>
class TextureManager
{
public:
    static TextureManager* instance;
    static TextureManager* GetInstance() {
        return instance = (instance != nullptr) ? instance : new TextureManager;
    }
    
    std::map<std::string, SDL_Texture*> _textureMap;

    bool load(std::string id, std::string fileName);

    void drop(std::string id);
    // vẽ 1 frame 
    void draw(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed);

    void drawFrame(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip);

    float textureWidth(std::string id);
    
    float textureHeight(std::string id);
    

};

