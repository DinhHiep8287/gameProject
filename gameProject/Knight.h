#pragma once
#include "Character.h"
#include "Physic/constants.h"
#include "Input.h"

const float knightMaxHealth = 100.0f;
const float ATTACK_RANGE = 50.0f;

const float KNIGHT_ATTACK_DAMAGE = 30.0f;

class Knight : public Character {
public:
    float attackCooldown = 5.0f;
    float attackTimer = 0.0f;
    Knight(float x, float y, float w, float h, float mass)
        : Character(x, y, w, h, mass, knightMaxHealth, defaultDirection)
    {
    }

    bool findMonsterInRange(const Vector2D& monsterPos);

    void handleInput();
    void handleState();
    bool attack() override;
    bool takeDamage(float damage);
    void jump() override;
    bool update(float dt) override;
    bool render() override;
    bool clean() override;
};
