#pragma once
#include <map>
#include <vector>

enum MonsterType {
    FLYING_EYE,
    GOBLIN,
    MUSHROOM,
    SKELETON
};

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
    //direction
    enum dir
    {
        LEFT, RIGHT
    };

const float deltaTime = 0.1f;
const float MASS = 1.0f;
const float GRAVITY = 10.0f;
const float JUMP_FORCE = 70.0f;
const float FRICTION = 0.9f;
const float MAX_VELOCITY_X = 40.0f; 
const float MAX_VELOCITY_Y = 60.0f; 
const dir defaultDirection = RIGHT;



// Map 
    enum LayerType {    
        TILE_LAYER,
        OBJECT_LAYER1,
        OBJECT_LAYER2,
        NUM_LAYERS
    };
    
    //Texture
    const std::map<std::string, std::string> MAP_TEXTURE_PATHS = {
        {"object_1", "Assets//Ob.png"},
        {"object_2", "Assets//Ob1.png"},
        {"tile_set", "Assets//Tileset.png"},
        {"heart", "Assets//heart.png"},
    };

    const std::map<std::string, std::string> MAP_DATA_PATHS = {
        {"tile_layer", "Map//MapData//LayerData1.txt"},
        {"object_1_layer", "Map//MapData//LayerData2.txt"},
        {"object_2_layer", "Map//MapData//LayerData3.txt"},

    };

    // Map Data
    const int NUM_TILE_SET_X = 10; const int NUM_TILE_SET_Y = 6; const int FIRST_ID_TILE_SET = 1;
    const int NUM_OBJECT_1_X = 12; const int NUM_OBJECT_1_Y = 11; const int FIRST_ID_OBJECT_1 = 61;
    const int NUM_OBJECT_2_X = 40; const int NUM_OBJECT_2_Y = 30; const int FIRST_ID_OBJECT_2 = 193;

    const std::string HIGHSCORE_PATH = "Map//GameData//highscore.txt";

    // Monster Info
const std::vector<std::tuple<int, int, int, MonsterType>> monstersInfo = {
    {400, 400, MASS, FLYING_EYE},
    {1250, 500, MASS, SKELETON},
    {2900, 700, MASS, SKELETON},
    {3450, 400, MASS, MUSHROOM},
    {3200, 0, MASS, GOBLIN},
    {3800, 700, MASS, SKELETON},
    {2500, 150, MASS, FLYING_EYE},
    {2000, 750, MASS, MUSHROOM},
    {2500, 550, MASS, MUSHROOM},
    {1400, 200 , MASS, FLYING_EYE},
    {3800, 300, MASS, GOBLIN}
    };
// Background Path
const std::map<std::string, std::string> BACKGROUND_PATHS = {
    {"background_1", "Assets//Background//Layers//1.png"},
    {"background_2", "Assets//Background//Layers//2.png"},
    {"background_3", "Assets//Background//Layers//3.png"},
    {"background_4", "Assets//Background//Layers//4.png"},
    {"background_5", "Assets//Background//Layers//5.png"}
};

const int backgroundWidth = 4028;
const int backgroundHeight = 800;

//Font Path
const std::map<std::string, std::pair<std::string, int>> FONTS_PATHS = {
    {"default", {"Assets//fonts//default.ttf", 20}},
    {"fontGame", {"Assets//fonts//fontGame.ttf", 20}},
    {"DungeonFont", {"Assets//fonts//DungeonFont.ttf", 100}}
};

//Music & Sound Path 
const std::map<std::string, std::string> MUSIC_PATHS = {
    {"gameMusic", "Assets//sound//music//GameMusic.wav"},
    {"menuMusic", "Assets//sound//music//MenuMusic.wav"}
};

const std::map<std::string, std::string> SOUND_PATHS = {
    {"button", "Assets//button//MI_SFX 01.wav"},
    {"knight_attack", "Assets//sound//sfx//knight_attack.wav"},
    {"knight_death", "Assets//sound//sfx//knight_death.wav"},
    {"knight_jump", "Assets//sound//sfx//knight_jump.wav"},
    {"knight_jump_land", "Assets//sound//sfx//knight_jump_land.wav"},
    {"knight_take_damage", "Assets//sound//sfx//knight_take_damage.wav"},
    {"knight_walk", "Assets//sound//sfx//knight_walk.wav"},
    {"monster_attack", "Assets//sound//sfx//monster_attack.wav"},
    {"monster_take_damage", "Assets//sound//sfx//monster_take_damage.wav"},
    {"monster_death", "Assets//sound//sfx//monster_death.wav"},
};

const int DEFAULT_FONT_SIZE = 20;

// Texture Path
    // Knight
    const std::map<std::string, std::string> KNIGHT_TEXTURE_PATHS = {
    {"KnightIdle", "Assets//Knight//idle.png"},
    {"KnightRun", "Assets//Knight//Run.png"},
    {"KnightAttack", "Assets//Knight//Attack.png"},
    {"KnightJump", "Assets//Knight//Jump.png"},
    {"KnightFall", "Assets//Knight//Fall.png"},
    {"KnightTakeHit", "Assets//Knight//Take Hit.png"},
    {"KnightDie", "Assets//Knight//Death.png"},
    {"KnightDead", "Assets//Knight//Dead.png"}
    };

    //Monster
    const std::map<std::string, std::string> FLYING_EYE_TEXTURE_PATHS = {
        {"FlyingEyeAttack", "Assets//Monster//Flying eye//Attack.png"},
        {"FlyingEyeAttack2", "Assets//Monster//Flying eye//Attack2.png"},
        {"FlyingEyeAttack3", "Assets//Monster//Flying eye//Attack3.png"},
        {"FlyingEyeDead", "Assets//Monster//Flying eye//Dead.png"},
        {"FlyingEyeDeath", "Assets//Monster//Flying eye//Death.png"},
        {"FlyingEyeFlight", "Assets//Monster//Flying eye//Flight.png"},
        {"FlyingEyeProjectileSprite", "Assets//Monster//Flying eye//projectile_sprite.png"},
        {"FlyingEyeTakeHit", "Assets//Monster//Flying eye//Take Hit.png"}
    };

    const std::map<std::string, std::string> GOBLIN_TEXTURE_PATHS = {
        {"GoblinAttack", "Assets//Monster//Goblin//Attack.png"},
        {"GoblinAttack2", "Assets//Monster//Goblin//Attack2.png"},
        {"GoblinAttack3", "Assets//Monster//Goblin//Attack3.png"},
        {"GoblinBombSprite", "Assets//Monster//Goblin//Bomb_sprite.png"},
        {"GoblinDead", "Assets//Monster//Goblin//Dead.png"},
        {"GoblinDeath", "Assets//Monster//Goblin//Death.png"},
        {"GoblinIdle", "Assets//Monster//Goblin//Idle.png"},
        {"GoblinRun", "Assets//Monster//Goblin//Run.png"},
        {"GoblinTakeHit", "Assets//Monster//Goblin//Take Hit.png"}
    };

    const std::map<std::string, std::string> MUSHROOM_TEXTURE_PATHS = {
        {"MushroomAttack", "Assets//Monster//Mushroom//Attack.png"},
        {"MushroomAttack2", "Assets//Monster//Mushroom//Attack2.png"},
        {"MushroomAttack3", "Assets//Monster//Mushroom//Attack3.png"},
        {"MushroomDead", "Assets//Monster//Mushroom//Dead.png"},
        {"MushroomDeath", "Assets//Monster//Mushroom//Death.png"},
        {"MushroomIdle", "Assets//Monster//Mushroom//Idle.png"},
        {"MushroomProjectileSprite", "Assets//Monster//Mushroom//Projectile_sprite.png"},
        {"MushroomRun", "Assets//Monster//Mushroom//Run.png"},
        {"MushroomTakeHit", "Assets//Monster//Mushroom//Take Hit.png"}
    };

    const std::map<std::string, std::string> SKELETON_TEXTURE_PATHS = {
        {"SkeletonAttack", "Assets//Monster//Skeleton//Attack.png"},
        {"SkeletonAttack2", "Assets//Monster//Skeleton//Attack2.png"},
        {"SkeletonAttack3", "Assets//Monster//Skeleton//Attack3.png"},
        {"SkeletonDead", "Assets//Monster//Skeleton//Dead.png"},
        {"SkeletonDeath", "Assets//Monster//Skeleton//Death.png"},
        {"SkeletonIdle", "Assets//Monster//Skeleton//Idle.png"},
        {"SkeletonShield", "Assets//Monster//Skeleton//Shield.png"},
        {"SkeletonSwordSprite", "Assets//Monster//Skeleton//Sword_sprite.png"},
        {"SkeletonTakeHit", "Assets//Monster//Skeleton//Take Hit.png"},
        {"SkeletonWalk", "Assets//Monster//Skeleton//Walk.png"}
    };

    const std::map<std::string, std::string> MENU_TEXTURE_PATHS = {
        {"panelTexture", "Assets//button//png@4x//Button-Back//Rect//Panel@4x.png"},

        {"buttonNormalTexture", "Assets//button//png@4x//Button-Back//Rect//Default@4x.png"},
        {"buttonHoveredTexture", "Assets//button//png@4x//Button-Back//Rect//Hover@4x.png"},

        {"muteNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOff//Default@4x.png"},
        {"muteHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOff//Hover@4x.png"},

        {"unmuteNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOn//Default@4x.png"},
        {"unmuteHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOn//Hover@4x.png"},

        {"leftNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//ArrowLeft-Bold//Default@4x.png"},
        {"leftHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//ArrowLeft-Bold//Hover@4x.png"},

        {"rightNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//ArrowRight-Bold//Default@4x.png"},
        {"rightHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//ArrowRight-Bold//Hover@4x.png"},

        {"pauseNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//Pause//Default@4x.png"},
        {"pauseHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//Pause//Hover@4x.png"},

        {"replayNormalButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOff//Default@4x.png"},
        {"replayHoveredButtonTexture", "Assets//button//png@4x//Buttons//Square//SoundOn//Hover@4x.png"},

    };

