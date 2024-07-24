#include "Knight.h"

bool Knight::attack()
{
    return false;
}

bool Knight::update(float dt)
{
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
        this->getBody()->jump();
    }

    this->setAnimation("KnightIdle", SDL_FLIP_NONE, 0, 80, 11, 0);

    this->setBody(100, 100);
    this->getBody()->update(dt);

    this->getAnimation()->UpdateAnimation();

    return false;
}

bool Knight::render()
{
    this->getAnimation()->DrawAnimation(this->getTextureID(), this->getPosition().getX(), this->getPosition().getY(),
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

bool Knight::clean()
{
    return false;
}
