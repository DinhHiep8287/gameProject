//#include "Object.h"
//
//Object::Object(const std::string& textureID, float x, float y, float w, float h, float mass)
//    : id(textureID), width(w), height(h), body(Shape(RectangleShape(w, h)), x, y, mass), flip(SDL_FLIP_NONE)
//{
//    centerPoint = new Vector2D(x + w / 2, y + h / 2);
//}
//
//void Object::update(float dt)
//{
//    body.IntegrateForces(dt);
//    body.IntegrateVelocities(dt);
//    *centerPoint = Vector2D(body.position.getX() + width / 2, body.position.getY() + height / 2);
//}
//
//void Object::render(SDL_Renderer* renderer)
//{
//    TextureManager::GetInstance()->draw(id, body.position.getX(), body.position.getY(), width, height, flip, 1.0f);
//}
