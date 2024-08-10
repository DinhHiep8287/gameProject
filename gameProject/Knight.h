#pragma once
#include "Character.h"
#include "Physic/constants.h"
#include "Input.h"

const float knightMaxHealth = 50.0f;
const float ATTACK_RANGE = 200.0f;
const float KNIGHT_ATTACK_DAMAGE = 30.0f;
const float DEFAULT_KNIGHT_ATTACK_SPEED = 150;

class Knight : public Character {
public:
    Knight(float x, float y, float w, float h, float mass)
        : Character(x, y, w, h, mass, knightMaxHealth, defaultDirection, DEFAULT_KNIGHT_ATTACK_SPEED)
    {
        maxAttackFrame = attackSpeed * 0.3f;
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
