#pragma once
#include "Object.h"
#include "Map/MapData/Level.h"
#include "Physic/constants.h"
enum CharacterState {
    IDLE,
    RUNNING,
    JUMPING,
    ATTACKING,
    FALLING,
    TAKING_DAMAGE,
    DYING,
    DEAD
};


class Character : public Object {
protected:
    float attackSpeed;
    float attackFrame = 0;
    float maxAttackFrame;
    float health;
    dir direction;
    CharacterState state;
    bool isDamageFrame = false;

public:
    Character(float x, float y, float w, float h, float mass, int maxHealth, dir defaultDirection, int _attackSpeed)
        : Object(x, y, w, h, mass), health(maxHealth), direction(defaultDirection), state(IDLE), attackSpeed(_attackSpeed)
    {
    }

    void handleColission(SDL_Rect& rect, const SDL_Rect oldRect, const SDL_Rect newRect,
        const Vector2D oldPosition, const Vector2D newPosition) {
        
        // Khi nhân vật rơi xuống vực
        if (this->getBody()->getRectShape().y + this->getBody()->getRectShape().h > MAP_HEIGHT + 500) {
            health = 0;
            state = DEAD;
            return;
        }

        rect.x = newRect.x;
        if (Level::isCollidingMap(rect, 0)) {
            this->getBody()->setPosition(oldPosition.getX(), oldPosition.getY());
            this->getBody()->unsetVelocityX();
            rect.x = oldRect.x;
        }
        else {
            this->getBody()->setPosition(newPosition.getX(), oldPosition.getY());
        }

        rect.y = newRect.y;
        if (Level::isCollidingMap(rect, 0)) {
            this->getBody()->setPosition(this->getBody()->getPosition()->getX(), oldPosition.getY());
            this->getBody()->unsetVelocityY();
            if (newPosition.getY() > oldPosition.getY()) {
                this->getBody()->setIsGrounded(true);
            }
            rect.y = oldRect.y;
        }
        else {
            this->getBody()->setPosition(this->getBody()->getPosition()->getX(), newPosition.getY());
        }

    }

    bool checkEdgeOfPlatform(int levelIndex) {
        SDL_Rect rect = this->getBody()->getRectShape();
        int tileSize = TILE_SIZE;

        // Xác định vị trí của quái vật trên lưới ô
        int currentLeftTile = rect.x / tileSize;
        int currentRightTile = (rect.x + rect.w) / tileSize;
        int currentBottomTile = (rect.y + rect.h) / tileSize;

        // Lấy chiều rộng và chiều cao của bản đồ (số ô trên chiều ngang và chiều dọc)
        int mapWidth = Level::getMatrix()[levelIndex][0].size();
        int mapHeight = Level::getMatrix()[levelIndex].size();

        // Kiểm tra xem quái vật có ra ngoài bản đồ hay không
        if (currentLeftTile < 0 || currentRightTile >= mapWidth || currentBottomTile >= mapHeight) {
            return true; // Quái vật ra ngoài bản đồ
        }

        // Kiểm tra xem quái vật có ở rìa nền không
        bool isLeftEdgeSolid = false;
        if (currentLeftTile >= 0 && currentLeftTile < mapWidth) {
            if (currentBottomTile + 1 < mapHeight) {
                isLeftEdgeSolid = (Level::getMatrix()[levelIndex][currentBottomTile + 1][currentLeftTile] > 0);
            }
        }

        bool isRightEdgeSolid = false;
        if (currentRightTile >= 0 && currentRightTile < mapWidth) {
            if (currentBottomTile + 1 < mapHeight) {
                isRightEdgeSolid = (Level::getMatrix()[levelIndex][currentBottomTile + 1][currentRightTile] > 0);
            }
        }

        // Nếu một trong hai bên không có nền bên dưới, quái vật đang ở rìa và có khả năng sẽ rơi xuống
        if (!isLeftEdgeSolid || !isRightEdgeSolid) {
            return true; // Quái vật đang ở rìa
        }

        return false; // Quái vật vẫn ở trên nền
    }

    bool isAboutToHitWall(int levelIndex) {
        SDL_Rect rect = this->getBody()->getRectShape();
        int tileSize = TILE_SIZE;

        // Xác định vị trí của nhân vật trên lưới ô
        int currentLeftTile = rect.x / tileSize;
        int currentRightTile = (rect.x + rect.w) / tileSize;
        int currentBottomTile = (rect.y + rect.h) / tileSize;

        // Lấy chiều rộng và chiều cao của bản đồ (số ô trên chiều ngang và chiều dọc)
        int mapWidth = Level::getMatrix()[levelIndex][0].size();
        int mapHeight = Level::getMatrix()[levelIndex].size();

        // Xác định hướng di chuyển của nhân vật
        bool movingRight = this->getDirection() == RIGHT;
        bool movingLeft = this->getDirection() == LEFT;

        // Kiểm tra xem nhân vật có sắp đụng vào tường hay không dựa trên hướng di chuyển
        if (movingRight) {
            // Xác định ô phía trước bên phải
            int nextTileRight = (rect.x + rect.w + 1) / tileSize;
            int bottomTileBelowRight = (rect.y + rect.h) / tileSize;

            if (nextTileRight >= 0 && nextTileRight < mapWidth && bottomTileBelowRight < mapHeight) {
                return (Level::getMatrix()[levelIndex][bottomTileBelowRight][nextTileRight] > 0);
            }
        }
        else if (movingLeft) {
            // Xác định ô phía trước bên trái
            int nextTileLeft = (rect.x - 1) / tileSize;
            int bottomTileBelowLeft = (rect.y + rect.h) / tileSize;

            if (nextTileLeft >= 0 && nextTileLeft < mapWidth && bottomTileBelowLeft < mapHeight) {
                return (Level::getMatrix()[levelIndex][bottomTileBelowLeft][nextTileLeft] > 0);
            }
        }

        return false; // Nhân vật không sắp đụng vào tường
    }

    


    int getHealth() const { return health; }
    void setHealth(int _health) { health = _health; }

    dir getDirection() const { return direction; }
    void setDirection(dir _direction) { direction = _direction; }

    CharacterState getState() const { return state; }
    void setState(CharacterState _state) { state = _state; }

    bool getIsDamageFrame() const { return isDamageFrame; }
    void setIsDamageFrame(bool _isDamageFrame) { isDamageFrame = _isDamageFrame; }

    std::string toString(CharacterState state) const {
        switch (state) {
        case IDLE: return "IDLE";
        case RUNNING: return "RUNNING";
        case JUMPING: return "JUMPING";
        case ATTACKING: return "ATTACKING";
        case FALLING: return "FALLING";
        case TAKING_DAMAGE: return "TAKING_DAMAGE";
        case DYING: return "DYING";
        case DEAD: return "DEAD";
        default: return "UNKNOWN";
        }
    }


    void renderText(int startX, int startY) const {
        Object::renderText(startX, startY);
        SDL_Color color = { 255, 255, 255, 255 };
        std::string fontId = "default";

        std::string healthText = "Health: " + std::to_string(this->getHealth());
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, healthText, fontId, color, startX, startY + 240);

        std::string stateText = "State: " + toString(this->getState());
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, stateText, fontId, color, startX, startY + 260);

        std::string attackSpeedText = "Attack Speed: " + std::to_string(this->attackSpeed);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, attackSpeedText, fontId, color, startX, startY + 280);

        std::string attackFrameText = "Attack Frame: " + std::to_string(this->attackFrame);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, attackFrameText, fontId, color, startX, startY + 300);

        std::string maxAttackFrameText = "Max Attack Frame: " + std::to_string(this->maxAttackFrame);
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, maxAttackFrameText, fontId, color, startX, startY + 320);

        std::string directionText = "Direction: " + std::string(this->direction == LEFT ? "LEFT" : "RIGHT");
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, directionText, fontId, color, startX, startY + 340);

        std::string isDamageFrameText = "Is Damage Frame: " + std::string(this->isDamageFrame ? "Yes" : "No");
        AssetManager::GetInstance()->renderText(Game::GetInstance()->renderer, isDamageFrameText, fontId, color, startX, startY + 360);
    }

    virtual bool attack() = 0;
    virtual void jump() = 0;
};
