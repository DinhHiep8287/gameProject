#include "Knight.h"

bool Knight::findMonsterInRange(const Vector2D& monsterPos) {
    float distance = this->getPosition().distance(monsterPos);
    return (distance < ATTACK_RANGE);
}

void Knight::handleInput() {
    if (state != DEAD)
    {
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
        this->setAnimation("KnightDead", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 80, 1, 0);
        this->getAnimation()->UpdateAnimation();
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

        if (maxAttackFrame != 0 && attackFrame == int(maxAttackFrame / 2) ) {
            isDamageFrame = true;
        }
        return;
    }
    
    if (!this->getBody()->isGrounded()) {
        if (this->getBody()->getVelocity().getY() < 0) {
            state = JUMPING;
        }
        else {
            state = FALLING;
        }
    }
    else if (abs(this->getBody()->getVelocity().getX()) > 0.8f) {
        state = RUNNING;
    }
    else {
        state = IDLE;
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
    state = ATTACKING;
    return true;
}

bool Knight::takeDamage(float damage) {
    if (state == DEAD) {
        return false;
    }

    this->health -= damage;
    if (this->health <= 0) {
        this->health = 0; // Đảm bảo máu không âm
        state = DEAD;
        return true;
    }

    state = TAKING_DAMAGE;
    return false;
}
void Knight::jump()
{
    if (this->getBody()->isGrounded()) {
        this->getBody()->getVelocity().setY(-JUMP_FORCE);
        this->getBody()->setIsGrounded(false);
    }
}

bool Knight::update(float dt)
{
    
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
    // Xử lý va chạm
    handleColission(rect, oldRect, newRect, oldPosition, newPosition);
    // Set và cập nhật animation
    

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
    // Placeholder implementation
    return false;
}
