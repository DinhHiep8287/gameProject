#include "Monster.h"

inline bool Monster::update(float dt) {
    // Update logic for the monster
    this->getBody()->update(dt);
    this->getAnimation()->UpdateAnimation();
    return true;
}

inline bool Monster::render() {
    this->getAnimation()->DrawAnimation(this->getAnimation()->id,
        this->getPosition().getX() - this->getTextureWidth() / 2,
        this->getPosition().getY() - this->getTextureHeight() / 2,
        this->getTextureWidth(), this->getTextureHeight(), this->getAnimation()->flip);
    return true;
}

inline bool Monster::clean() {
    // Clean up logic if needed
    return true;
}
