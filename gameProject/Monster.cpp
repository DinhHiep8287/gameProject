#include "Monster.h"

void Monster::handleInput() {
    // Implement quái vật xử lý di chuyển hoặc hành động khác nếu cần
}

void Monster::handleState()
{
    if(state == ATTACKING) {
        attackFrame++;
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        isDamageFrame = false;

        if (this->getAnimation()->IsAnimationDone()) {
            attackFrame = 0;
            state = IDLE;
        }

        if (maxAttackFrame != 0 && attackFrame == int(maxAttackFrame / 4 * 3)) {
            isDamageFrame = true;
        }
        return;
    }

    if (abs(this->getBody()->getVelocity().getX()) > 0.8f) {
        state = RUNNING;
    }
    else {
        state = IDLE;
    }

    switch (state) {
    case IDLE:
        this->setTextureBasedOnTypeAndState();
        break;
    case RUNNING:
        this->setTextureBasedOnTypeAndState();
        break;
    case ATTACKING:
        this->setTextureBasedOnTypeAndState();
        break;
    case DEAD:
        this->setTextureBasedOnTypeAndState();
        break;
    }

    this->getAnimation()->UpdateAnimation();
}

bool Monster::attack()
{
    state = ATTACKING;
    return true;
}

bool Monster::takeDamage(float damage) {
    if (state == TAKING_DAMAGE) {
        return false;
    }
    this->health -= damage;
    state = TAKING_DAMAGE;

    return false;
}

void Monster::jump()
{
}

bool Monster::findKnightInRange(const Vector2D& knightPos) {
    float distance = this->getPosition().distance(knightPos);
    if (distance < MONSTER_ATTACK_RANGE) {
        attack();
        return true;
    }
    return false;
}


void Monster::setTextureBasedOnTypeAndState() {
    switch (type) {
    case FLYING_EYE:
        if (state == IDLE) {
            this->setAnimation("FlyingEyeFlight", SDL_FLIP_NONE, 0, 100, 6, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("FlyingEyeFlight", SDL_FLIP_NONE, 0, 100, 6, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("FlyingEyeAttack", SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("FlyingEyeDead", SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case GOBLIN:
        if (state == IDLE) {
            this->setAnimation("GoblinIdle", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("GoblinRun", SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("GoblinAttack", SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("GoblinDead", SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case MUSHROOM:
        if (state == IDLE) {
            this->setAnimation("MushroomIdle", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("MushroomRun", SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("MushroomAttack", SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("MushroomDead", SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case SKELETON:
        if (state == IDLE) {
            this->setAnimation("SkeletonIdle", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("SkeletonWalk", SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("SkeletonAttack", SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("SkeletonDead", SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;
    }
}

bool Monster::update(float dt) {
    Vector2D oldPosition = *this->getBody()->getPosition();
    SDL_Rect oldRect = this->getBody()->getRectShape();
    SDL_Rect rect = this->getBody()->getRectShape();

    // Xử lý di chuyển
    handleInput();
    // Cập nhật cơ thể
    this->getBody()->update(dt);
    Vector2D newPosition = *this->getBody()->getPosition();
    SDL_Rect newRect = this->getBody()->getRectShape();
    this->handleColission(rect, oldRect, newRect, oldPosition, newPosition);
    handleState();
    return true;
}

bool Monster::render() {
    this->getAnimation()->DrawAnimation(this->getAnimation()->id, this->getPosition().getX() - this->getTextureWidth() / 2, this->getPosition().getY() - this->getTextureHeight() / 2,
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

bool Monster::clean() {
    // Clean up logic if needed
    return true;
}
