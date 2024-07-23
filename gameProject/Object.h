#pragma once
#include <SDL.h>
#include <iostream>
#include "Physic/Body.h"
#include "AssetManager.h"
#include "Animation.h"
#include <SDL_image.h>

class Object
{
private:
    Body body;
    float textureWidth, textureHeight;
    std::string id;
    SDL_RendererFlip flip;
    Vector2D* centerPoint;
    Animation* animation;

public:
    Object(const std::string& textureID, float x, float y, float w, float h, float mass)
        : id(textureID), textureWidth(w), textureHeight(h), flip(SDL_FLIP_NONE), centerPoint(new Vector2D(w / 2, h / 2)), animation(nullptr)
    {
        body.setPosition(x, y);
        body.setMass(mass);
    }

    virtual ~Object()
    {
        delete centerPoint;
        delete animation;
    }

    virtual bool update(float dt) = 0; 
    virtual bool render() = 0; 
    virtual bool clean() = 0; 

    Vector2D getPosition() const { return *body.getPosition(); }
    void setPosition(const Vector2D& pos) { *body.getPosition() = pos; }
    Vector2D* getCenterPoint() const { return centerPoint; }
    void setCenterPoint(Vector2D* point) { centerPoint = point; }
    float getTextureWidth() const { return textureWidth; }
    void setTextureWidth(float width) { textureWidth = width; }
    float getTextureHeight() const { return textureHeight; }
    void setTextureHeight(float height) { textureHeight = height; }
    void setAnimation(Animation* anim) { animation = anim; }
    void setFlip(SDL_RendererFlip f) { flip = f; }
    std::string getId() const { return id; }
    void setId(const std::string& textureID) { id = textureID; }
    SDL_RendererFlip getFlip() const { return flip; }
};