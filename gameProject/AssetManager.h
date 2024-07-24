#pragma once
#include "Game.h"
#include "Camera.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
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
    std::map<std::string, TTF_Font*> _fontMap;
    std::map<std::string, Mix_Chunk*> _soundMap;


    bool loadTexture(std::string id, std::string fileName);
    bool loadFont(std::string id, std::string fileName, int fontSize);
    bool loadSound(std::string id, std::string fileName);


    void dropTexture(std::string id);
    void dropFont(std::string id);
    void dropSound(std::string id);

    void renderBackground(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed);

    void renderObject(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip);

    void renderObject(std::string id, float textureX, float textureY, float width, float height, float mapX, float mapY);

    void renderRect(SDL_Rect rect);

    void playSound(std::string id);

    void renderText(SDL_Renderer* renderer, std::string message, std::string fontId, SDL_Color color, int x, int y);

    float textureWidth(std::string id);
    
    float textureHeight(std::string id);
    

};

