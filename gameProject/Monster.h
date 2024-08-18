#pragma once
#include "Character.h"

const float DEFAULT_MONSTER_HEALTH = 100.0f;
const float MONSTER_ATTACK_RANGE = 100.0f;
const float MONSTER_ATTACK_DAMAGE = 10.0f;
const float DEFAULT_MONSTER_ATTACK_SPEED = 200.0f;
const float DEFAULT_MONSTER_SPEED = 10.0f;

const float FLYING_EYE_WIDTH = 40.0f;
const float GOBLIN_WIDTH = 40.0f;
const float MUSHROOM_WIDTH = 40.0f;
const float SKELETON_WIDTH = 40.0f;
const float DEFAULT_MONSTER_WIDTH = 40.0f;


const float FLYING_EYE_HEIGHT = 80.0f;
const float GOBLIN_HEIGHT = 90.0f;
const float MUSHROOM_HEIGHT = 90.0f;
const float SKELETON_HEIGHT = 90.0f;
const float DEFAULT_MONSTER_HEIGHT = 80.0f;


class Monster : public Character
{
private:
    MonsterType type;
    HealthBar* _healthBar;

public:
    Monster(float x, float y, float mass, MonsterType type)
        : Character(x, y, GetWidthBasedOnType(type), GetHeightBasedOnType(type), mass, DEFAULT_MONSTER_HEALTH, defaultDirection, DEFAULT_MONSTER_ATTACK_SPEED), type(type)
    {
        maxAttackFrame = attackSpeed / 100 * 43;
        _healthBar = new HealthBar(this->getBody()->getRectShape().x, this->getBody()->getRectShape().y - 10, GetWidthBasedOnType(type), 5);
    }

    static float GetWidthBasedOnType(MonsterType type) {
        switch (type) {
        case FLYING_EYE: return FLYING_EYE_WIDTH;
        case GOBLIN: return GOBLIN_WIDTH;
        case MUSHROOM: return MUSHROOM_WIDTH;
        case SKELETON: return SKELETON_WIDTH;
        default: return DEFAULT_MONSTER_WIDTH;
        }
    }

    // Hàm trả về chiều cao dựa trên loại quái vật
    static float GetHeightBasedOnType(MonsterType type) {
        switch (type) {
        case FLYING_EYE: return FLYING_EYE_HEIGHT;
        case GOBLIN: return GOBLIN_HEIGHT;
        case MUSHROOM: return MUSHROOM_HEIGHT;
        case SKELETON: return SKELETON_HEIGHT;
        default: return DEFAULT_MONSTER_HEIGHT;
        }
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