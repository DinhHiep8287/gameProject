#pragma once
#include "Physic/Vector2D.h"
#include "SDL.h"
#include "Physic/constants.h"

class Camera
{
public:
    Camera();
    static Camera* instance;
    static Camera* getInstance()
    {
        return instance = (instance != nullptr) ? instance : new Camera();
    }
    Vector2D* pPosition;
    SDL_Rect viewBox;
    Vector2D position;
    SDL_Rect getViewBox();
    Vector2D* getPoint();

    bool isInViewBox(int objX, int objY, int objWidth, int objHeight) const;
    bool isInViewBox(const SDL_Rect& rect) const;
    void setPoint(Vector2D* _point);
    void update(float dt);
};

