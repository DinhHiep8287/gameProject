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
    Body* body;
    float textureWidth, textureHeight;
    std::string textureID;
    SDL_RendererFlip flip;
    Vector2D* centerPoint;
    Animation* animation;

public:
    Object(const std::string& _textureID, float x, float y, float w, float h, float mass)
        : textureID(_textureID), textureWidth(w), textureHeight(h), flip(SDL_FLIP_NONE), centerPoint(new Vector2D(w / 2, h / 2)), animation(new Animation())
    {
        body = new Body();
        body->setPosition(x, y);
        body->setMass(mass);
    }

    virtual ~Object()
    {
        delete centerPoint;
        delete body;
        delete animation;
    }

    virtual bool update(float dt) = 0;
    virtual bool render() = 0;
    virtual bool clean() = 0;

    void setAnimation(std::string _id, SDL_RendererFlip _flip, int _row, int _AnimationSpeed, int _frameCount, int _frame) {
        this->animation->SetAnimation(_id, _flip, _row, _AnimationSpeed, _frameCount, _frame);
        setTextureWidth(AssetManager::GetInstance()->textureWidth(_id) / this->getAnimation()->frameCount);
        setTextureHeight(AssetManager::GetInstance()->textureHeight(_id));
    }

    void setBody(float bodyWidth, float bodyHeight) {
        centerPoint->setX(body->getPosition()->getX() + textureWidth / 2);
        centerPoint->setY(body->getPosition()->getY() + textureHeight / 2);
        
        body->setRectX(centerPoint->getX() - bodyWidth / 2);
        body->setRectY(centerPoint->getY() - bodyHeight / 2);
        body->setRectWidth(bodyWidth);
        body->setRectHeight(bodyHeight);
    }

    Vector2D getPosition() const { return *body->getPosition(); }
    void setPosition(const Vector2D& pos) { *body->getPosition() = pos; }
    Body* getBody() const { return body; }
    void setBody(Body* _body) { body = _body; }
    Vector2D* getCenterPoint() const { return centerPoint; }
    void setCenterPoint(Vector2D* point) { centerPoint = point; }
    float getTextureWidth() const { return textureWidth; }
    void setTextureWidth(float width) { textureWidth = width; }
    float getTextureHeight() const { return textureHeight; }
    void setTextureHeight(float height) { textureHeight = height; }
    void setAnimation(Animation* anim) { animation = anim; }
    Animation* getAnimation() const { return animation; }
    void setFlip(SDL_RendererFlip f) { flip = f; }
    std::string getTextureID() const { return textureID; }
    void setTextureID(const std::string& _textureID) { textureID = _textureID; }
    SDL_RendererFlip getFlip() const { return flip; }

    void renderText(int startX, int startY) const
    {
        SDL_Color color = { 255, 255, 255, 255 }; // White color

        AssetManager* assetManager = AssetManager::GetInstance();
        std::string fontId = "default"; 

        std::string textureIDText = "TextureID: " + this->getTextureID();
        std::string positionText = "Position: (" + std::to_string(this->getPosition().getX()) + ", " + std::to_string(this->getPosition().getY()) + ")";
        std::string centerPointText = "CenterPoint: (" + std::to_string(this->getCenterPoint()->getX()) + ", " + std::to_string(this->getCenterPoint()->getY()) + ")";
        std::string textureWidthText = "TextureWidth: " + std::to_string(this->getTextureWidth());
        std::string textureHeightText = "TextureHeight: " + std::to_string(this->getTextureHeight());
        std::string flipText = "Flip: " + std::to_string(this->getFlip());
        std::string massText = "Mass: " + std::to_string(this->getBody()->getMass());
        std::string gravityText = "Gravity: " + std::to_string(this->getBody()->getGravity());
        std::string forceText = "Force: (" + std::to_string(this->getBody()->getForce().getX()) + ", " + std::to_string(this->getBody()->getForce().getY()) + ")";
        std::string frictionText = "Friction: (" + std::to_string(this->getBody()->getFriction().getX()) + ", " + std::to_string(this->getBody()->getFriction().getY()) + ")";
        std::string velocityText = "Velocity: (" + std::to_string(this->getBody()->getVelocity().getX()) + ", " + std::to_string(this->getBody()->getVelocity().getY()) + ")";
        std::string accelerationText = "Acceleration: (" + std::to_string(this->getBody()->getAcceleration().getX()) + ", " + std::to_string(this->getBody()->getAcceleration().getY()) + ")";

        assetManager->renderText(Game::GetInstance()->renderer, textureIDText, fontId, color, startX, startY);
        assetManager->renderText(Game::GetInstance()->renderer, positionText, fontId, color, startX, startY + 20);
        assetManager->renderText(Game::GetInstance()->renderer, centerPointText, fontId, color, startX, startY + 40);
        assetManager->renderText(Game::GetInstance()->renderer, textureWidthText, fontId, color, startX, startY + 60);
        assetManager->renderText(Game::GetInstance()->renderer, textureHeightText, fontId, color, startX, startY + 80);
        assetManager->renderText(Game::GetInstance()->renderer, flipText, fontId, color, startX, startY + 100);
        assetManager->renderText(Game::GetInstance()->renderer, massText, fontId, color, startX, startY + 120);
        assetManager->renderText(Game::GetInstance()->renderer, gravityText, fontId, color, startX, startY + 140);
        assetManager->renderText(Game::GetInstance()->renderer, forceText, fontId, color, startX, startY + 160);
        assetManager->renderText(Game::GetInstance()->renderer, frictionText, fontId, color, startX, startY + 180);
        assetManager->renderText(Game::GetInstance()->renderer, velocityText, fontId, color, startX, startY + 200);
        assetManager->renderText(Game::GetInstance()->renderer, accelerationText, fontId, color, startX, startY + 220);
    }
};
