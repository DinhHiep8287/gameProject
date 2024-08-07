#pragma once
#include "Character.h"
#include "Physic/constants.h"
#include "Input.h"
#include "Map/MapData/Level.h" 

const float knightMaxHealth = 100.0f;
const dir defaultDirection = RIGHT;

class Knight : public Character {
public:
    Knight(float x, float y, float w, float h, float mass)
        : Character(x, y, w, h, mass, knightMaxHealth, defaultDirection)
    {
    }

    void handleInput();
    void handleColission(SDL_Rect& rect, const SDL_Rect oldRect, const SDL_Rect newRect,
        const Vector2D oldPosition, const Vector2D newPosition);
    void handleState();
    bool attack() override;
    void jump() override;
    bool update(float dt) override;
    bool render() override;
    bool clean() override;
};
