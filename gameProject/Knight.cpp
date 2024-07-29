#include "Knight.h"

bool Knight::attack()
{
    // Placeholder implementation
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
   Vector2D oldPosition = *(this->getBody()->getPosition());

   // Kiểm tra va chạm
   if (Level::isCollidingMap(this->getBody()->getRectShape(), 0)) {
       // Xử lý va chạm
       this->getBody()->setPosition(oldPosition.getX(), oldPosition.getY());
       this->getBody()->setIsGrounded(true);
       this->getBody()->getVelocity().setY(0); // Cân nhắc thêm để khôi phục vận tốc
   }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
        this->getBody()->setForceX(10);
    }
    else if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
        this->getBody()->setForceX(-10);
    }
    else {
        this->getBody()->unsetForce();
    }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
        this->jump();
    }

    //

    //Update Body
    this->getBody()->update(dt);

    // Set + Update Animation
    this->setAnimation("KnightIdle", SDL_FLIP_NONE, 0, 80, 11, 0);
    this->getAnimation()->UpdateAnimation();

    return true;
}

bool Knight::render()
{
    this->getAnimation()->DrawAnimation(this->getTextureID(), this->getPosition().getX() - this->getTextureWidth() / 2, this->getPosition().getY() - this->getTextureHeight() / 2,
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

bool Knight::clean()
{
    // Placeholder implementation
    return false;
}
