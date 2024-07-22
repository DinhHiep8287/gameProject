#pragma once
#include <SDL.h>
#include <iostream>
#include "Physic/Body.h"
#include "TextureManager.h"
#include "Animation.h"
#include <SDL_image.h>
class Object
{
private:
    Body body;
    float width, height;
    std::string id;
    SDL_RendererFlip flip;
    Vector2D* centerPoint;
    Animation* animation;


public:
    Object(const std::string& textureID, float x, float y, float w, float h, float mass);

    void update(float dt);
    void render(SDL_Renderer* renderer);

    Vector2D getPosition() const { return body.getPosition(); }
    void setPosition(const Vector2D& pos) { body.getPosition() = pos; }
    Vector2D* getCenterPoint() const { return centerPoint; }
    void setCenterPoint(Vector2D* point) { centerPoint = point; }
    
};

