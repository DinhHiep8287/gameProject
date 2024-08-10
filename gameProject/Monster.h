#pragma once
#include "Character.h"

const float DEFAULT_MONSTER_HEALTH = 100.0f;
const float MONSTER_ATTACK_RANGE = 100.0f;
const float MONSTER_ATTACK_DAMAGE = 10.0f;
const int DEFAULT_MONSTER_ATTACK_SPEED = 200;

class Monster : public Character
{
private:
    MonsterType type;

public:
    Monster(float x, float y, float w, float h, float mass, MonsterType type)
        : Character(x, y, w, h, mass, DEFAULT_MONSTER_HEALTH, defaultDirection, DEFAULT_MONSTER_ATTACK_SPEED), type(type)
    {
        maxAttackFrame = attackSpeed / 100 * 43;
    }

    void handleInput();

    void handleState();

    bool attack() override;

    bool takeDamage(float damage);

    void jump() override;

    bool update(float dt) override;

    bool render() override;

    bool clean() override;

    MonsterType getType() const { return type; }

    bool findKnightInRange(const SDL_Rect& knightRect);

private:
    void setTextureBasedOnTypeAndState();

};