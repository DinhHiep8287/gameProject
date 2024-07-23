#pragma once


const int SIZE = 32;

// Screen dimensions
const int NUM_SCREEN_X = 30;
const int NUM_SCREEN_Y = 30;
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


// Background 
const std::string backgroundPath1 = "Assets//Background//Layers//1.png";
const std::string backgroundPath2 = "Assets//Background//Layers//2.png";
const std::string backgroundPath3 = "Assets//Background//Layers//3.png";
const std::string backgroundPath4 = "Assets//Background//Layers//4.png";
const std::string backgroundPath5 = "Assets//Background//Layers//5.png";
const int backgroundWidth = 4028;
const int backgroundHeight = 800;

//