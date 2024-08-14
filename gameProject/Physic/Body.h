#pragma once
#include "Vector2D.h"
#include <SDL.h>
#include <iostream>
#include "constants.h"
#include "../AssetManager.h"
#include <string>

class Body
{
private:
    float _mass;
    float _gravity;
    Vector2D _force;
    Vector2D _friction;
    SDL_Rect _rectShape;
    Vector2D* _position;
    Vector2D _velocity;
    Vector2D _acceleration;
    bool _isGrounded;

public:
    Body()
        : _mass(MASS), _gravity(GRAVITY), _force(0, 0), _friction(0, 0), _rectShape{ 0,0,0,0 }, _position(new Vector2D(0, 0)), _velocity(0, 0), _acceleration(0, 0), _isGrounded(false)
    {
    }

    ~Body()
    {
        delete _position;
    }

    void updateRectShape()
    {
        _rectShape.x = static_cast<int>(_position->getX() - _rectShape.w / 2);
        _rectShape.y = static_cast<int>(_position->getY() - _rectShape.h / 2);
    }

    // Setter
    inline void setMass(float mass) { _mass = mass; }
    inline void setGravity(float gravity) { _gravity = gravity; }
    inline void setForce(const Vector2D& force) { _force = force; }
    inline void setForceX(float forceX) { _force.setX(forceX); }
    inline void setForceY(float forceY) { _force.setY(forceY); }
    inline void unsetForce() { _force = Vector2D(0, 0); }
    inline void setFriction(const Vector2D& friction) { _friction = friction; }
    inline void unsetFriction() { _friction = Vector2D(0, 0); }
    inline void setIsGrounded(bool isGrounded) { _isGrounded = isGrounded; };
    inline void setAccelerationX(float accelerationX) { _acceleration.setX(accelerationX); };
    inline void setAccelerationY(float accelerationY) { _acceleration.setY(accelerationY); };
    inline void unsetVelocity() { _velocity = Vector2D(0, 0); }
    inline void unsetVelocityX() { _velocity.setX(0); }
    inline void unsetVelocityY() { _velocity.setY(0); }


    void setPosition(float x, float y)
    {
        _position->setX(x);
        _position->setY(y);
        _rectShape.x = static_cast<int>(x - _rectShape.w / 2);
        _rectShape.y = static_cast<int>(y - _rectShape.h / 2);
    }
    void setRectWidth(float w) { _rectShape.w = static_cast<int>(w); updateRectShape(); }
    void setRectHeight(float h) { _rectShape.h = static_cast<int>(h); updateRectShape(); }
    void setRectX(float x) { _rectShape.x = static_cast<int>(x); }
    void setRectY(float y) { _rectShape.y = static_cast<int>(y); }
    void setVelocity(const Vector2D& newVelocity) {
        this->_velocity = newVelocity;
    }
    // Getter
    float getMass() const { return _mass; }
    float getGravity() const { return _gravity; }
    Vector2D getForce() const { return _force; }
    Vector2D getFriction() const { return _friction; }
    SDL_Rect getRectShape() const { return _rectShape; }
    Vector2D getAcceleration() const { return _acceleration; }
    Vector2D& getVelocity() { return _velocity; }
    const Vector2D& getVelocity() const { return _velocity; }
    Vector2D* getPosition() const { return _position; }
    bool isGrounded() const { return _isGrounded; }

    // Update method
    void update(float dt)
    {
        // Tính toán gia tốc dựa trên lực và ma sát
        _acceleration.setX((_force.getX() - _friction.getX()) / _mass);
        _acceleration.setY((_gravity + (_force.getY() - _friction.getY())) / _mass);

        // Cập nhật vận tốc với ma sát
        if (_force.getX() == 0)
        {
            // Áp dụng ma sát theo phương x nếu vận tốc đang di chuyển
            if (fabs(_velocity.getX()) < 0.01f) // Nếu vận tốc gần như bằng 0
            {
                _velocity.setX(0); // Đặt vận tốc theo phương x về 0
            }
            else
            {
                _velocity.setX(_velocity.getX() * FRICTION);
            }
        }
        else
        {
            _velocity.setX(_velocity.getX() + _acceleration.getX() * dt);
        }

        _velocity.setY(_velocity.getY() + _acceleration.getY() * dt);

        // Giới hạn vận tốc tối đa
        if (_velocity.getX() > MAX_VELOCITY_X) _velocity.setX(MAX_VELOCITY_X);
        if (_velocity.getX() < -MAX_VELOCITY_X) _velocity.setX(-MAX_VELOCITY_X);
        if (_velocity.getY() > MAX_VELOCITY_Y) _velocity.setY(MAX_VELOCITY_Y);
        if (_velocity.getY() < -MAX_VELOCITY_Y) _velocity.setY(-MAX_VELOCITY_Y);

        *_position = *_position + (_velocity * dt);

        updateRectShape();
    }

    void renderText(int startX, int startY) const
    {
        SDL_Color color = { 255, 255, 255, 255 }; // White color

        AssetManager* assetManager = AssetManager::GetInstance();
        std::string fontId = "default"; 

        std::string massText = "Mass: " + std::to_string(this->getMass());
        std::string gravityText = "Gravity: " + std::to_string(this->getGravity());
        std::string forceText = "Force: (" + std::to_string(this->getForce().getX()) + ", " + std::to_string(this->getForce().getY()) + ")";
        std::string frictionText = "Friction: (" + std::to_string(this->getFriction().getX()) + ", " + std::to_string(this->getFriction().getY()) + ")";
        std::string positionRectText = "PositionRect: (" + std::to_string(this->getRectShape().x) + ", " + std::to_string(this->getRectShape().y) + ")";
        std::string positionPointerText = "PositionPointer: (" + std::to_string(this->getPosition()->getX()) + ", " + std::to_string(this->getPosition()->getY()) + ")";
        std::string velocityText = "Velocity: (" + std::to_string(this->getVelocity().getX()) + ", " + std::to_string(this->getVelocity().getY()) + ")";
        std::string accelerationText = "Acceleration: (" + std::to_string(this->getAcceleration().getX()) + ", " + std::to_string(this->getAcceleration().getY()) + ")";
        std::string isGroundedText = "IsGrounded: " + std::to_string(this->_isGrounded);

        assetManager->renderText(Game::GetInstance()->renderer, massText, fontId, color, startX, startY);
        assetManager->renderText(Game::GetInstance()->renderer, gravityText, fontId, color, startX, startY + 20);
        assetManager->renderText(Game::GetInstance()->renderer, forceText, fontId, color, startX, startY + 40);
        assetManager->renderText(Game::GetInstance()->renderer, frictionText, fontId, color, startX, startY + 60);
        assetManager->renderText(Game::GetInstance()->renderer, positionRectText, fontId, color, startX, startY + 80);
        assetManager->renderText(Game::GetInstance()->renderer, positionPointerText, fontId, color, startX, startY + 100);
        assetManager->renderText(Game::GetInstance()->renderer, velocityText, fontId, color, startX, startY + 120);
        assetManager->renderText(Game::GetInstance()->renderer, accelerationText, fontId, color, startX, startY + 140);
        assetManager->renderText(Game::GetInstance()->renderer, isGroundedText, fontId, color, startX, startY + 160);


    }
};
