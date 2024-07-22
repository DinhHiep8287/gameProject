#pragma once


// Screen dimensions
const int SIZE = 32;
const int SCREEN_WIDTH = 32 * SIZE;
const int SCREEN_HEIGHT = 19 * SIZE;

// Physic
const float deltaTime = 0.1f;
const float MASS = 1.0f;
const float GRAVITY = 10.0f;
const float JUMP_FORCE = 50;
const float FRICTION = 0.9f;
const float MAX_VELOCITY_X = 40.0f; // Vận tốc tối đa theo phương x
const float MAX_VELOCITY_Y = 40.0f; // Vận tốc tối đa theo phương y

// Map dimensions
const int MAP_WIDTH = 32 * 128;
const int MAP_HEIGHT = 2 * SCREEN_HEIGHT;

//direction

enum dir
{
	LEFT, RIGHT
};

// Character

const float knightMaxHeath = 100;

// Background 
const std::string backgroundPath1 = "Assets//Background//Layers//1.png";
const std::string backgroundPath2 = "Assets//Background//Layers//2.png";
const std::string backgroundPath3 = "Assets//Background//Layers//3.png";
const std::string backgroundPath4 = "Assets//Background//Layers//4.png";
const std::string backgroundPath5 = "Assets//Background//Layers//5.png";
const int backgroundWidth = 4028;
const int backgroundHeight = 800;

