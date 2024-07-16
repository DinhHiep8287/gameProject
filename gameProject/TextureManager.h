#pragma once
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

    // Vẽ từng khung hình của một Sprite 
    void drawFrame(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip);

    float textureWidth(std::string id);
    
    float textureHeight(std::string id);
    
    /*void drawHitbox(SDL_Rect* hitbox, SDL_Renderer* ren)
    {
        SDL_Rect tempRect = { hitbox->x - Camera::getInstance()->pos.x , hitbox->y - Camera::getInstance()->pos.y , hitbox->w , hitbox->h };
        SDL_RenderDrawRect(ren, &tempRect);
    }*/

};

