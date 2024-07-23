#include "Knight.h"

bool Knight::attack()
{
    return false;
}

bool Knight::update(float dt)
{
    std::cout << "Updating Knight" << std::endl;

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_D)) {
        std::cout << "Moving right" << std::endl;
        this->getBody().setForceX(10);
    }
    else if (Input::getInstance()->getKeyDown(SDL_SCANCODE_A)) {
        std::cout << "Moving left" << std::endl;
        this->getBody().setForceX(-10);
    }
    else {
        this->getBody().unsetForce();
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {
        std::cout << "Jumping" << std::endl;
        this->getBody().jump();
    }

    std::cout << "Setting animation" << std::endl;
    this->getAnimation().SetAnimation("KnightIdle", SDL_FLIP_NONE, 0, 80, 11, 0);

    std::cout << "Updating body" << std::endl;
    this->getBody().update(dt);
    std::cout << "Updating animation" << std::endl;
    this->getAnimation().UpdateAnimation();
    std::cout << "Knight update completed" << std::endl;

    return false;
}

bool Knight::render()
{
    this->getAnimation().DrawAnimation(this->getTextureID(), this->getPosition().getX(), this->getPosition().getY(),
                                        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation().flip);
    return true;
}

bool Knight::clean()
{
    return false;
}
