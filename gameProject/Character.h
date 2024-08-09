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
    float attackSpeed;
    float attackFrame = 0;
    float maxAttackFrame;
    float health;
    dir direction;
    CharacterState state;
    bool isDamageFrame = false;

public:
    Character(float x, float y, float w, float h, float mass, int maxHealth, dir defaultDirection, int _attackSpeed)
        : Object(x, y, w, h, mass), health(maxHealth), direction(defaultDirection), state(IDLE), attackSpeed(_attackSpeed)
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
            this->getBody()->setPosition(this->getBody()->getPosition()->getX(), oldPosition.getY());
            this->getBody()->unsetVelocityY();
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

    bool getIsDamageFrame() const { return isDamageFrame; }
    void setIsDamageFrame(bool _isDamageFrame) { isDamageFrame = _isDamageFrame; }

    void renderText(int startX, int startY) const {
        Object::renderText(0, 0);
        SDL_Color color = { 255, 255, 255, 255 };
        std::string fontId = "default";

        std::string healthText = "Health: " + std::to_string(this->getHealth());
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, healthText, fontId, color, startX, startY + 240);

        std::string stateText = "State: " + std::to_string(this->getState());
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, stateText, fontId, color, startX, startY + 260);

        std::string attackSpeedText = "Attack Speed: " + std::to_string(this->attackSpeed);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, attackSpeedText, fontId, color, startX, startY + 280);

        std::string attackFrameText = "Attack Frame: " + std::to_string(this->attackFrame);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, attackFrameText, fontId, color, startX, startY + 300);

        std::string maxAttackFrameText = "Max Attack Frame: " + std::to_string(this->maxAttackFrame);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, maxAttackFrameText, fontId, color, startX, startY + 320);
        std::string directionText;
        if (this->direction == LEFT) {
            directionText = "Direction: LEFT";
        }
        else {
            directionText = "Direction: RIGHT";
        }
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, directionText, fontId, color, startX, startY + 340);

        std::string isDamageFrameText = "Is Damage Frame: " + std::string(this->isDamageFrame ? "Yes" : "No");
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, isDamageFrameText, fontId, color, startX, startY + 360);
    }

    virtual bool attack() = 0;
    virtual void jump() = 0;
};
