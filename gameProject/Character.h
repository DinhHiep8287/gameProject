#pragma once
#include "Object.h"
#include "Map/MapData/Level.h"

enum CharacterState {
    IDLE,
    RUNNING,
    JUMPING,
    ATTACKING,
    FALLING,
    TAKING_DAMAGE,
    DEAD
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

    void handleColission(SDL_Rect& rect, const SDL_Rect oldRect, const SDL_Rect newRect,
        const Vector2D oldPosition, const Vector2D newPosition) {
        rect.x = newRect.x;
        if (Level::isCollidingMap(rect, 0)) {
            this->getBody()->setPosition(oldPosition.getX(), oldPosition.getY());
            this->getBody()->unsetVelocityX();
            rect.x = oldRect.x;
        }
        else {
            this->getBody()->setPosition(newPosition.getX(), oldPosition.getY());
        }

        rect.y = newRect.y;
        if (Level::isCollidingMap(rect, 0)) {
            this->getBody()->unsetVelocityY();
            this->getBody()->setPosition(this->getBody()->getPosition()->getX(), oldPosition.getY());

            if (newPosition.getY() > oldPosition.getY()) {
                this->getBody()->setIsGrounded(true);
            }
            rect.y = oldRect.y;
        }
        else {
            this->getBody()->setPosition(this->getBody()->getPosition()->getX(), newPosition.getY());
        }

    }

    int getHealth() const { return health; }
    void setHealth(int _health) { health = _health; }

    dir getDirection() const { return direction; }
    void setDirection(dir _direction) { direction = _direction; }

    CharacterState getState() const { return state; }
    void setState(CharacterState _state) { state = _state; }

    void renderText(int startX, int startY) const {
        Object::renderText(0, 0);
        SDL_Color color = { 255, 255, 255, 255 }; // White color
        std::string fontId = "default";

        std::string heathText = "Health: " + std::to_string(this->getHealth());
        std::string stateText = "State: " + std::to_string(this->getState());
        
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, heathText, fontId, color, startX, startY + 240);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, stateText, fontId, color, startX, startY + 260);

    }

    virtual bool attack() = 0;
    virtual void jump() = 0;
};
