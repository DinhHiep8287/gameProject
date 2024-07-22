#pragma once
#include "Object.h"
#include "Physic/constants.h"
class Knight : public Object
{
public:     
        Knight();
        int health = knightMaxHeath;
        dir direction;

        bool attackEnermy();
        void drawObject();
        void updateObject(float dt);
        void cleanObject(SDL_Texture* texture);

};