#include "Knight.h"

bool Knight::findMonsterInRange(const SDL_Rect& monsterRect) {
    Vector2D knightPos = this->getPosition();
    float rangeWidth = KNIGHT_ATTACK_RANGE;
    float rangeHeight = this->getBody()->getRectShape().h;

    SDL_Rect attackRect{};

    if (direction == RIGHT) {
        attackRect.x = static_cast<int>(knightPos.getX());
        attackRect.y = static_cast<int>(knightPos.getY() - rangeHeight / 2);
        attackRect.w = static_cast<int>(rangeWidth);
        attackRect.h = static_cast<int>(rangeHeight);
    }
    else if (direction == LEFT) {
        attackRect.x = static_cast<int>(knightPos.getX() - rangeWidth);
        attackRect.y = static_cast<int>(knightPos.getY() - rangeHeight / 2);
        attackRect.w = static_cast<int>(rangeWidth);
        attackRect.h = static_cast<int>(rangeHeight);
    }

    // Kiểm tra va chạm giữa phạm vi tấn công và hitbox của quái vật
    return SDL_HasIntersection(&attackRect, &monsterRect) != SDL_FALSE;
}

void Knight::handleInput() {
    if (state != DEAD && state != DYING) {
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
            this->getBody()->setForceX(10);
            direction = RIGHT;
        }
        else if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
            this->getBody()->setForceX(-10);
            direction = LEFT;
        }
        else {
            this->getBody()->unsetForce();
        }
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
            this->jump();
        }
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_J)) {
            attack();
        }
    }
}

void Knight::handleState()
{
    if (state == DEAD) {
        this->getBody()->unsetVelocityX();
        this->setAnimation("KnightDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 80, 1, 0);
        this->getAnimation()->UpdateAnimation();
        return;
    }

    if (state == DYING) {
        this->setAnimation("KnightDie", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 9, 0);
        this->getAnimation()->UpdateAnimation();

        if (this->getAnimation()->IsAnimationDone()) {
            state = DEAD; 
        }
        return;
    }

    if (state == ATTACKING) {
        attackFrame++;
        this->setAnimation("KnightAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, attackSpeed, 6, 0);
        this->getAnimation()->UpdateAnimation();
        isDamageFrame = false;
        

        if (this->getAnimation()->IsAnimationDone()) {
            attackFrame = 0;
            state = IDLE; 
        }

        if (attackFrame == int(maxAttackFrame / 2) ) {
            isDamageFrame = true;
            AssetManager::GetInstance()->playSound("knight_attack", 1);
        }
        return;
    }

    if (state == TAKING_DAMAGE) {
        this->setAnimation("KnightTakeHit", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 4, 0);
        this->getAnimation()->UpdateAnimation();
        if (this->getAnimation()->IsAnimationDone()) {
            state = IDLE;
        }
        return;
    }

    if (state == RUNNING && this->getBody()->isGrounded()) {
        if (!Mix_Playing(2)) {
            AssetManager::GetInstance()->playSound("knight_walk", 2);
        }
    }
    
    // Nếu nhân vật ngừng tấn công, reset attackFrame về 0
    attackFrame = 0;


    if (!this->getBody()->isGrounded()) {
        if (this->getBody()->getVelocity().getY() < 0) {
            state = JUMPING;
        }
        else {
            state = FALLING;
        }
    }
    else {
        // Nếu vừa tiếp đất sau khi nhảy hoặc rơi
        if (state == FALLING) {
            // Phát âm thanh tiếp đất
            AssetManager::GetInstance()->playSound("knight_jump_land", 3);
        }

        if (abs(this->getBody()->getVelocity().getX()) > 0.8f) {
            state = RUNNING;
        }
        else {
            state = IDLE;
        }
    }
    
    switch (state) {
    case IDLE:
        this->setAnimation("KnightIdle", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 80, 11, 0);
        break;
    case RUNNING:
        this->setAnimation("KnightRun", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 100, 8, 0);
        break;
    case JUMPING:
        this->setAnimation("KnightJump", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 50, 4, 0);
        break;
    case FALLING:
        this->setAnimation("KnightFall", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 50, 4, 0);
        break;
    case ATTACKING:
        this->setAnimation("KnightAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 60, 6, 0);
        break;
    }

    this->getAnimation()->UpdateAnimation();
}

bool Knight::attack() {
    if (health <= 0) {
        state = DYING;
        return false;
    }

    state = ATTACKING;
    return true;
}

bool Knight::takeDamage(float damage) {
    if (state == DEAD || state == DYING) {
        return false;
    }

    this->health -= damage;
    this->getBody()->unsetVelocity();

    AssetManager::GetInstance()->playSound("knight_take_damage", 4);
    if (this->health <= 0) {
        this->health = 0; 
        state = DYING; 
        AssetManager::GetInstance()->playSound("knight_death", 5);
        return true;
    }

    if (state == ATTACKING) {
        attackFrame = 0;
    }

    state = TAKING_DAMAGE;
    return false;
}
void Knight::jump()
{
    if (this->getBody()->isGrounded()) {
        this->getBody()->getVelocity().setY(-JUMP_FORCE);
        this->getBody()->setIsGrounded(false);
        AssetManager::GetInstance()->playSound("knight_jump", 6);
    }
}

bool Knight::update(float dt)
{
    
    Vector2D oldPosition = *this->getBody()->getPosition();
    SDL_Rect oldRect = this->getBody()->getRectShape();
    SDL_Rect rect = this->getBody()->getRectShape();
    // Xử lý di chuyển
    handleInput();
    // Set và cập nhật animation
    handleState();    
    // Cập nhật cơ thể
    this->getBody()->update(dt);    
    Vector2D newPosition = *this->getBody()->getPosition();
    SDL_Rect newRect = this->getBody()->getRectShape();
    // Xử lý va chạm
    handleColission(rect, oldRect, newRect, oldPosition, newPosition);
    return true;
}

bool Knight::render()
{
    this->getAnimation()->DrawAnimation(this->getAnimation()->id, this->getPosition().getX() - this->getTextureWidth() / 2, this->getPosition().getY() - this->getTextureHeight() / 2,
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

bool Knight::clean()
{
    // Giải phóng tài nguyên hoặc xóa các đối tượng liên quan đến Knight nếu cần
    // Ví dụ: Xóa textures, sounds, hoặc bất kỳ thứ gì Knight đang sử dụng.
    // Đặt lại các biến của Knight về trạng thái ban đầu.
    if (getBody()) {
        delete getBody();
        setBody(nullptr);
    }
    return true;
}
