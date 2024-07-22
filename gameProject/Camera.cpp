#include "camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera() {
    viewBox = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
}

SDL_Rect Camera::getViewBox() {
    return viewBox;
}

Vector2D* Camera::getPoint() {
    return pPosition;
}


void Camera::setPoint(Vector2D* _point) {
    pPosition = _point;
}

void Camera::update(float dt) {
    // đặt tọa độ của "box" điểm nhìn 
    viewBox.x = static_cast<int>(pPosition->getX()) - SCREEN_WIDTH / 2; // từ trung tâm trừ đi độ dài màn hình / 2
    viewBox.y = static_cast<int>(pPosition->getY()) - SCREEN_HEIGHT / 2; // từ trung tâm trừ đi độ cao màn hình / 2
    // Nếu nhỏ hơn 0 chứng tỏ đã đến giới hạn của map, không cuộn camera nữa
    if (viewBox.x < 0) {
        viewBox.x = 0;
    }
    if (viewBox.y < 0) {
        viewBox.y = 0;
    }
    // Tương tự, đã đến giới hạn map thì không cuộn camera nữa
    if (viewBox.x > (MAP_WIDTH - viewBox.w)) {
        viewBox.x = MAP_WIDTH - viewBox.w;
    }
    if (viewBox.y > (MAP_HEIGHT - viewBox.h)) {
        viewBox.y = (MAP_HEIGHT - viewBox.h);
    }

    // Đặt tọa độ pos điểm nhìn
    position = Vector2D(static_cast<float>(viewBox.x), static_cast<float>(viewBox.y));
}
