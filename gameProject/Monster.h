#pragma once
#include "Character.h"

enum MonsterType {
    FLYING_EYE,
    GOBLIN,
    MUSHROOM,
    SKELETON
};

const float defaultMonsterMaxHealth = 100.0f;
const float MONSTER_ATTACK_RANGE = 50.0f;
const float MONSTER_ATTACK_DAMAGE = 10.0f;

class Monster : public Character
{
private:
    MonsterType type;

public:
    Monster(float x, float y, float w, float h, float mass, MonsterType type)
        : Character(x, y, w, h, mass, defaultMonsterMaxHealth, defaultDirection), type(type)
    {
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

    bool findKnightInRange(const Vector2D& knightPos);

private:
    void setTextureBasedOnTypeAndState();

};