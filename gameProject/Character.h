#pragma once
#include "Object.h"

enum CharacterState {
    IDLE,
    RUNNING,
    JUMPING,
    ATTACKING,
    FALLING
};

class Character : public Object {
protected:
    int health;
    dir direction;
    CharacterState state;

public:
    Character(float x, float y, float w, float h, float mass, int maxHealth, dir defaultDirection)
        : Object(x, y, w, h, mass), health(maxHealth), direction(defaultDirection), state(IDLE)
    {
    }

    int getHealth() const { return health; }
    void setHealth(int _health) { health = _health; }

    dir getDirection() const { return direction; }
    void setDirection(dir _direction) { direction = _direction; }

    CharacterState getState() const { return state; }
    void setState(CharacterState _state) { state = _state; }

    virtual bool attack() = 0;
    virtual void jump() = 0;
};
