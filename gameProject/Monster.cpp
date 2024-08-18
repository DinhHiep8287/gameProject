#include "Monster.h"

void Monster::handleInput() {
    if (direction == RIGHT && state == RUNNING ) {
        this->getBody()->setVelocity(Vector2D(DEFAULT_MONSTER_SPEED, this->getBody()->getVelocity().getY()));
    }
    if (direction == LEFT && state == RUNNING) {
        this->getBody()->setVelocity(Vector2D(-DEFAULT_MONSTER_SPEED, this->getBody()->getVelocity().getY()));
    }
    // Kiểm tra nếu quái vật đến rìa platform
    if (checkEdgeOfPlatform(0) || isAboutToHitWall(0)) {
        // Đảo ngược hướng di chuyển khi đến rìa platform
        if (direction == RIGHT && state == RUNNING) {
            direction = LEFT;
            this->getBody()->setVelocity(Vector2D(-DEFAULT_MONSTER_SPEED, this->getBody()->getVelocity().getY()));
        }
        else {
            direction = RIGHT;
            this->getBody()->setVelocity(Vector2D(DEFAULT_MONSTER_SPEED, this->getBody()->getVelocity().getY()));
        }
    }
}

void Monster::setTextureBasedOnTypeAndState() {
        if (direction == LEFT) {
            this->getAnimation()->flip = SDL_FLIP_HORIZONTAL;
        }
        else {
            this->getAnimation()->flip = SDL_FLIP_NONE;
        }
    switch (type) {
    case FLYING_EYE:
        if (state == IDLE || state == RUNNING) {
            this->setAnimation("FlyingEyeFlight", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("FlyingEyeAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("FlyingEyeTakeHit", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("FlyingEyeDeath", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 200, 4, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("FlyingEyeDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case GOBLIN:
        if (state == IDLE) {
            this->setAnimation("GoblinIdle", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("GoblinRun", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("GoblinAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("GoblinTakeHit", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("GoblinDeath", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 200, 4, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("GoblinDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case MUSHROOM:
        if (state == IDLE) {
            this->setAnimation("MushroomIdle", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("MushroomRun", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 8, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("MushroomAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("MushroomTakeHit", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("MushroomDeath", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 200, 4, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("MushroomDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;

    case SKELETON:
        if (state == IDLE) {
            this->setAnimation("SkeletonIdle", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == RUNNING) {
            this->setAnimation("SkeletonWalk", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == ATTACKING) {
            this->setAnimation("SkeletonAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, attackSpeed, 8, 0);
        }
        else if (state == TAKING_DAMAGE) {
            this->setAnimation("SkeletonTakeHit", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        }
        else if (state == DYING) {
            this->setAnimation("SkeletonDeath", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 200, 4, 0);
        }
        else if (state == DEAD) {
            this->setAnimation("SkeletonDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 1, 0);
        }
        break;
    }
}

void Monster::handleState()
{
    if (state == DEAD) {
        getBody()->unsetVelocity();
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
            AssetManager::GetInstance()->playSound("monster_attack", 7);
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

    // Kiểm tra nếu vận tốc đủ lớn để chuyển sang trạng thái RUNNING
    if (abs(this->getBody()->getVelocity().getX()) > 0.8f) {
        state = RUNNING;
    }
    else {
        state = IDLE;
    }

    // Nếu nhân vật ngừng tấn công, reset attackFrame về 0
    attackFrame = 0;

    // Xử lý trạng thái và cập nhật animation tương ứng
    switch (state) {
    case IDLE:
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        break;
    case RUNNING:
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        break;
    case ATTACKING:
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        break;
    case DYING:
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        break;
    case DEAD:
        setTextureBasedOnTypeAndState();
        this->getAnimation()->UpdateAnimation();
        break;
    }
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
    _healthBar->update(health, DEFAULT_MONSTER_HEALTH);
    AssetManager::GetInstance()->playSound("monster_take_damage", 9);
    if (this->health <= 0) {
        this->health = 0;
        // Chuyển trực tiếp sang trạng thái DYING khi máu của quái vật bằng 0
        state = DYING;
        AssetManager::GetInstance()->playSound("monster_death", 8);
        return true;
    }

    // Nếu nhân vật đang ở trạng thái ATTACKING, reset attackFrame
    if (state == ATTACKING) {
        attackFrame = 0;
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

        // Chỉ kiểm tra tầm tấn công nếu quái vật không đang tấn công
        if (SDL_HasIntersection(&attackRect, &knightRect) != SDL_FALSE) {
            attack();
            return true;
        }
        else if (state != ATTACKING) {
            state = RUNNING;
        }
    }
    return false;
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

    _healthBar->update(health, DEFAULT_MONSTER_HEALTH);
    _healthBar->setPosition(this->getBody()->getRectShape().x - Camera::getInstance()->getViewBox().x, this->getBody()->getRectShape().y - 10 - Camera::getInstance()->getViewBox().y);

    return true;
}

bool Monster::render() {
    if (state != DEAD) {
        _healthBar->render(Game::GetInstance()->renderer);
    }
    this->getAnimation()->DrawAnimation(this->getAnimation()->id, this->getPosition().getX() - this->getTextureWidth() / 2, this->getPosition().getY() - this->getTextureHeight() / 2,
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

bool Monster::clean() {
    // Giải phóng tài nguyên hoặc xóa các đối tượng liên quan đến Monster nếu cần
    // Ví dụ: Xóa textures, sounds, hoặc bất kỳ thứ gì Monster đang sử dụng.
    // Đặt lại các biến của Monster về trạng thái ban đầu.
    if (getBody()) {
        delete getBody();
        setBody(nullptr);
    }
    return true;
}
