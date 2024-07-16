#pragma once
#include "Vector2D.h"
#include <SDL.h>
#include <iostream>
#include "constants.h"


class Body
{
private:
    float _mass;
    float _gravity;
    Vector2D _force;
    Vector2D _friction;
    SDL_Rect _rectShape;
    Vector2D _position;
    Vector2D _velocity;
    Vector2D _acceleration;
    bool _isGrounded;

public:
    Body()
        : _mass(MASS), _gravity(GRAVITY), _force(0, 0), _friction(0, 0), _rectShape{ 0,0,0,0 }, _velocity(0, 0), _acceleration(0, 0), _isGrounded(true)
    {
    }

    //Setter
    inline void setMass(float mass) { _mass = mass; }
    inline void setGravity(float gravity) { _gravity = gravity; }
    inline void setForce(const Vector2D& force) { _force = force; }
    inline void setForceX(float forceX) { _force.setX(forceX); }
    inline void setForceY(float forceY) { _force.setY(forceY); }
    inline void unsetForce() { _force = Vector2D(0, 0); }
    inline void setFriction(const Vector2D& friction) { _friction = friction; }
    inline void unsetFriction() { _friction = Vector2D(0, 0); }
    void setPosition(float x, float y)
    {
        _position.setX(x);
        _position.setY(y);
        _rectShape.x = static_cast<int>(x);
        _rectShape.y = static_cast<int>(y);
    }

    //Getter
    float getMass() const { return _mass; }
    SDL_Rect getRectShape() const { return _rectShape; }
    Vector2D getAcceleration() const { return _acceleration; }
    Vector2D getVelocity() const { return _velocity; }
    Vector2D getPosition() const { return _position; }

    // Method to jump
    void jump()
    {
        if (_isGrounded)
        {
            _velocity.setY(-JUMP_FORCE); 
            _isGrounded = false;
        }
    }

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


        // Cập nhật vị trí
        _position = _position + (_velocity * dt);
        _rectShape.x = static_cast<int>(_position.getX());
        _rectShape.y = static_cast<int>(_position.getY());

        // Đảm bảo đối tượng không rơi qua mặt đất
        if (_rectShape.y > 300) 
        {
            _rectShape.y = 300;
            _velocity.setY(0); 
            _isGrounded = true; 
        }
    }

    void print() const
    {

        std::cout << "Mass: " << _mass << std::endl;
        std::cout << "Gravity: " << _gravity << std::endl;
        std::cout << "Force: (" << _force.getX() << ", " << _force.getY() << ")" << std::endl;
        std::cout << "Friction: (" << _friction.getX() << ", " << _friction.getY() << ")" << std::endl;
        std::cout << "Position: (" << _rectShape.x << ", " << _rectShape.y << ")" << std::endl;
        std::cout << "Velocity: (" << _velocity.getX() << ", " << _velocity.getY() << ")" << std::endl;
        std::cout << "Acceleration: (" << _acceleration.getX() << ", " << _acceleration.getY() << ")" << std::endl;
        
    }
};
