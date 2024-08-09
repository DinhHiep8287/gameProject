#include "Knight.h"

bool Knight::findMonsterInRange(const Vector2D& monsterPos) {
    float distance = this->getPosition().distance(monsterPos);
    return (distance < ATTACK_RANGE);
}

void Knight::handleInput() {
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
        this->attack();
    }
}

void Knight::handleState()
{
    if (state == ATTACKING) {
        this->setAnimation("KnightAttack", direction == LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE, 0, 60, 6, 0);
        this->getAnimation()->UpdateAnimation();
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
    if (state == ATTACKING || attackTimer > 0.0f) {
        return false;
    }

    state = ATTACKING;
    attackTimer = attackCooldown;
    return true;
}

bool Knight::takeDamage(float damage) {
    if (state == TAKING_DAMAGE) {
        return false; 
    }
    this->health -= damage;
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

    if (attackTimer > 0.0f) {
        attackTimer -= dt;
    }

    std::cout << attackTimer << std::endl;

    Vector2D oldPosition = *this->getBody()->getPosition();
    SDL_Rect oldRect = this->getBody()->getRectShape();
    SDL_Rect rect = this->getBody()->getRectShape();
    // Xử lý di chuyển
    handleInput();
    // Cập nhật cơ thể
    this->getBody()->update(dt);
    Vector2D newPosition = *this->getBody()->getPosition();
    SDL_Rect newRect = this->getBody()->getRectShape();
    // Xử lý va chạm
    handleColission(rect, oldRect, newRect, oldPosition, newPosition);
    // Set và cập nhật animation
    handleState();

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
