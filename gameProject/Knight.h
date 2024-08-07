#pragma once
#include "Object.h"
#include "Physic/constants.h"
#include "Input.h"
#include "Map/MapData/Level.h" 

const float knightMaxHealth = 100.0f;
const dir defaultDirection = RIGHT;


class Knight : public Object
{
private:
    int health;
    dir direction;

public:
    Knight(const std::string& textureID, float x, float y, float w, float h, float mass)
        : Object(textureID, x, y, w, h, mass), health(knightMaxHealth), direction(defaultDirection)
    {
    }

    void handleInput();
    void handleColission(SDL_Rect& rect, const SDL_Rect oldRect, const SDL_Rect newRect,
        const Vector2D oldPosition, const Vector2D newPostion);

    bool attack();
    void jump();
    bool update(float dt) override;
    bool render() override;
    bool clean() override;


    int getHealth() const { return health; }
    void setHealth(int health) { this->health = health; }
    dir getDirection() const { return direction; }
    void setDirection(dir direction) { this->direction = direction; }
};
