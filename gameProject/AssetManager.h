#pragma once
#include "Game.h"
#include "Camera.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
class AssetManager
{
public:
    static AssetManager* instance;
    static AssetManager* GetInstance() {
        return instance = (instance != nullptr) ? instance : new AssetManager;
    }
    
    std::map<std::string, SDL_Texture*> _textureMap;
    std::map<std::string, TTF_Font*> _fontMap;
    std::map<std::string, Mix_Chunk*> _soundMap;
    std::map<std::string, Mix_Music*> _musicMap;
    std::string idMusicPlaying = "";
    int currentMusicVolumePercent = 100;
    int currentSFXVolumePercent = 100;

    bool loadTexture(std::string id, std::string fileName);
    bool loadFont(std::string id, std::string fileName, int fontSize);
    bool loadSound(std::string id, std::string fileName);
    bool loadMusic(std::string id, std::string fileName);

    TTF_Font* getFont(const std::string& fontId);

    void dropTexture(std::string id);
    void dropFont(std::string id);
    void dropSound(std::string id);

    void renderBackground(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed);

    void renderObject(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip);

    void renderObject(std::string id, float textureX, float textureY, float width, float height, float mapX, float mapY);

    void renderTextureRect(SDL_Renderer* renderer, std::string textureId, int x, int y, int w, int h);

    void renderRect(SDL_Rect rect);

    void renderRect(SDL_Rect rect, SDL_Color color);

    void playSound(std::string id);

    void playSound(std::string id, int channel);

    void playMusic(std::string id, int loop);

    void stopMusic();

    void increaseMusicVolume();

    void decreaseMusicVolume();

    void increaseSFXVolume();

    void decreaseSFXVolume();

    void muteVolume();

    void unmuteVolume();

    int getMusicVolume() const;

    int getSFXVolume() const;

    bool isMuted() const;

    void renderText(SDL_Renderer* renderer, std::string message, std::string fontId, SDL_Color color, int x, int y);

    void renderText(SDL_Renderer* renderer, std::string message, std::string fontId, SDL_Color color, int x, int y, int w, int h);

    float textureWidth(std::string id);
    
    float textureHeight(std::string id);

};

