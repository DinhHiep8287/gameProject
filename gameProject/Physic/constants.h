#pragma once
#include <map>

const int SIZE = 32;

// Screen dimensions
const int NUM_SCREEN_X = 32;
const int NUM_SCREEN_Y = 19;
const int SCREEN_WIDTH = NUM_SCREEN_X * SIZE;
const int SCREEN_HEIGHT = NUM_SCREEN_Y * SIZE;

// Map dimensions
const int NUM_MAP_X = 128;
const int NUM_MAP_Y = 28;
const int MAP_WIDTH = NUM_MAP_X * SIZE;
const int MAP_HEIGHT = NUM_MAP_Y * SIZE;

// Physic
const float deltaTime = 0.1f;
const float MASS = 1.0f;
const float GRAVITY = 10.0f;
const float JUMP_FORCE = 50;
const float FRICTION = 0.9f;
const float MAX_VELOCITY_X = 40.0f; 
const float MAX_VELOCITY_Y = 40.0f; 


//direction
enum dir
{
	LEFT, RIGHT
};


// Background Path
const std::map<std::string, std::string> backgroundPaths = {
    {"background_1", "Assets//Background//Layers//1.png"},
    {"background_2", "Assets//Background//Layers//2.png"},
    {"background_3", "Assets//Background//Layers//3.png"},
    {"background_4", "Assets//Background//Layers//4.png"},
    {"background_5", "Assets//Background//Layers//5.png"}
};

const int backgroundWidth = 4028;
const int backgroundHeight = 800;

// Texture Path
    // Knight
    const std::map<std::string, std::string> knightTexturePaths = {
    {"KnightIdle", "Assets//Knight//idle.png"},
    {"KnightRun", "Assets//Knight//Run.png"},
    {"KnightAttack", "Assets//Knight//Attack.png"},
    {"KnightJump", "Assets//Knight//Jump.png"},
    {"KnightFall", "Assets//Knight//Fall.png"},
    {"KnightTakeHit", "Assets//Knight//Take Hit.png"},
    {"KnightDie", "Assets//Knight//Death.png"},
    {"KnightDead", "Assets//Knight//Dead.png"}
    };

