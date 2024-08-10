#include "Monster.h"

void Monster::handleInput() {
    // Implement logic xử lý di chuyển hoặc hành động khác nếu cần
}

void Monster::handleState()
{
    if (state == DEAD) {
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        return;
    }

    if (state == DYING) {
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();

        if (this->getAnimation()->IsAnimationDone()) {
            state = DEAD; // Chuyển sang trạng thái DEAD khi animation DYING kết thúc
        }
        return;
    }

    if (state == TAKING_DAMAGE) {
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();

        if (this->getAnimation()->IsAnimationDone()) {
            state = IDLE;  
        }
        return;
    }

    if (state == ATTACKING) {
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
    case RUNNING:
    case ATTACKING:
    case DYING:
    case DEAD:
        this->setTextureBasedOnTypeAndState();
        break;
    }

    this->getAnimation()->UpdateAnimation();
}

bool Monster::attack()
{
    if (health <= 0) {
        state = DYING;
        return false;
    }

    state = ATTACKING;
    return true;
}

bool Monster::takeDamage(float damage) {
    if (state == DEAD || state == DYING) {
        return false;
    }

    this->health -= damage;
    if (this->health <= 0) {
        this->health = 0;
        state = DYING;
        return true;
    }

    state = TAKING_DAMAGE;
    return false;
}

void Monster::jump() {
    // Implement logic jump nếu cần
}

bool Monster::findKnightInRange(const SDL_Rect& knightRect) {
    if (state != DEAD && state != DYING && state != TAKING_DAMAGE) {
        Vector2D monsterPos = this->getPosition();
        float rangeWidth = MONSTER_ATTACK_RANGE;
        float rangeHeight = this->getBody()->getRectShape().h;

        SDL_Rect attackRect{};

        if (direction == RIGHT) {
            attackRect.x = static_cast<int>(monsterPos.getX());
            attackRect.y = static_cast<int>(monsterPos.getY() - rangeHeight / 2);
            attackRect.w = static_cast<int>(rangeWidth);
            attackRect.h = static_cast<int>(rangeHeight);
        }
        else if (direction == LEFT) {
            attackRect.x = static_cast<int>(monsterPos.getX() - rangeWidth);
            attackRect.y = static_cast<int>(monsterPos.getY() - rangeHeight / 2);
            attackRect.w = static_cast<int>(rangeWidth);
            attackRect.h = static_cast<int>(rangeHeight);
        }

        if (SDL_HasIntersection(&attackRect, &knightRect) != SDL_FALSE) {
            attack();
            return true;
        }
    }
    return false;
}


void Monster::setTextureBasedOnTypeAndState() {
    switch (type) {
    case FLYING_EYE:
        if (state == IDLE) {
            this->setAnimation("FlyingEyeFlight", SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("FlyingEyeFlight", SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("FlyingEyeAttack", SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("FlyingEyeTakeHit", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("FlyingEyeDeath", SDL_FLIP_NONE, 0, 100, 4, 0);
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
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("GoblinTakeHit", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("GoblinDeath", SDL_FLIP_NONE, 0, 100, 4, 0);
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
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("MushroomTakeHit", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("MushroomDeath", SDL_FLIP_NONE, 0, 100, 4, 0);
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
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("SkeletonTakeHit", SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("SkeletonDeath", SDL_FLIP_NONE, 0, 100, 4, 0);
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
    handleState();
    // Cập nhật cơ thể
    this->getBody()->update(dt);
    Vector2D newPosition = *this->getBody()->getPosition();
    SDL_Rect newRect = this->getBody()->getRectShape();
    this->handleColission(rect, oldRect, newRect, oldPosition, newPosition);
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
