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
    std::string textureID;
    SDL_RendererFlip flip;
    Vector2D* centerPoint;
    Animation animation;

public:
    Object(const std::string& _textureID, float x, float y, float w, float h, float mass)
        : textureID(_textureID), textureWidth(w), textureHeight(h), flip(SDL_FLIP_NONE), centerPoint(new Vector2D(w / 2, h / 2))
    {
        body.setPosition(x, y);
        body.setMass(mass);
    }

    virtual ~Object()
    {
        delete centerPoint;
    }

    virtual bool update(float dt) = 0; 
    virtual bool render() = 0; 
    virtual bool clean() = 0; 

    Vector2D getPosition() const { return *body.getPosition(); }
    void setPosition(const Vector2D& pos) { *body.getPosition() = pos; }
    Body getBody() const { return body; }
    void setBody(Body _body) { body = _body; }
    Vector2D* getCenterPoint() const { return centerPoint; }
    void setCenterPoint(Vector2D* point) { centerPoint = point; }
    float getTextureWidth() const { return textureWidth; }
    void setTextureWidth(float width) { textureWidth = width; }
    float getTextureHeight() const { return textureHeight; }
    void setTextureHeight(float height) { textureHeight = height; }
    void setAnimation(Animation anim) { animation = anim; }
    Animation getAnimation() const { return animation; }
    void setFlip(SDL_RendererFlip f) { flip = f; }
    std::string getTextureID() const { return textureID; }
    void setTextureID(const std::string& _textureID) { textureID = _textureID; }
    SDL_RendererFlip getFlip() const { return flip; }
};