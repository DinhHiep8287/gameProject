#include "AssetManager.h"
AssetManager* AssetManager::instance = nullptr;

bool AssetManager::loadTexture(std::string id, std::string fileName)
{
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == nullptr)
    {
        std::cout << "load khong thanh cong: " << fileName << std::endl;
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        std::cout << "load khong thanh cong: " << fileName << std::endl;
    }
    _textureMap[id] = texture;
    std::cout << "load thanh cong: " << fileName << std::endl;
    return true;
}
bool AssetManager::loadFont(std::string id, std::string fileName, int fontSize)
{
    TTF_Font* font = TTF_OpenFont(fileName.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    else {
        std::cout << "Load thanh cong: " << fileName << std::endl;
    }

    _fontMap[id] = font;
    return true;
}
bool AssetManager::loadSound(std::string id, std::string fileName)
{
    Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
        return false;
    }
    else {
        std::cout << "Load thanh cong: " << fileName << std::endl;
    }

    _soundMap[id] = sound;
    return true;
}

bool AssetManager::loadMusic(std::string id, std::string fileName)
{
    Mix_Music* music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    else {
        std::cout << "Load thanh cong: " << fileName << std::endl;
    }
    _musicMap[id] = music;
    return true;
}

TTF_Font* AssetManager::getFont(const std::string& fontId)
{
    // Tìm kiếm font trong _fontMap theo id
    auto it = _fontMap.find(fontId);

    if (it != _fontMap.end()) {
        // Nếu tìm thấy, trả về font
        return it->second;
    }
    else {
        // Nếu không tìm thấy, in ra thông báo lỗi và trả về nullptr
        std::cerr << "Font not found: " << fontId << std::endl;
        return nullptr;
    }
}


void AssetManager::dropTexture(std::string id)
{
    SDL_DestroyTexture(_textureMap[id]);
    _textureMap.erase(id);
}

void AssetManager::dropFont(std::string id)
{
    TTF_CloseFont(_fontMap[id]);
    _fontMap.erase(id);
}

void AssetManager::dropSound(std::string id)
{
    Mix_FreeChunk(_soundMap[id]);
    _soundMap.erase(id);
}

void AssetManager::renderBackground(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed)
{
    SDL_Rect srcrect = { 0 , 0 , width , height };
    SDL_Rect dstrect = { x - Camera::getInstance()->position.getX() * paralaxSpeed , y - Camera::getInstance()->position.getY() * paralaxSpeed , width , height };
    SDL_RenderCopyEx(Game::GetInstance()->renderer, _textureMap[id], &srcrect, &dstrect, 0, NULL, flip);
}

void AssetManager::renderObject(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip)
{
    // Tọa độ của 1 source frame sẽ được xác định bởi x = Chiều Dài 1 frame * thứ tự frame ; y = Chiều cao 1 frame * thứ tự cột
    if (_textureMap.find(id) == _textureMap.end()) {
        std::cerr << "Error: Texture " << id << " not found!" << std::endl;
        return;
    }
    SDL_Rect srcrect = { width * frame , height * row , width , height };
    SDL_Rect dstrect = { x - Camera::getInstance()->position.getX(), y - Camera::getInstance()->position.getY() , width , height};
    SDL_RenderCopyEx(Game::GetInstance()->renderer, _textureMap[id], &srcrect, &dstrect, 0, NULL, flip);
}

void AssetManager::renderObject(std::string id, float textureX, float textureY, float width, float height, float mapX, float mapY)
{
    if (_textureMap.find(id) == _textureMap.end()) {
        std::cerr << "Error: Texture " << id << " not found!" << std::endl;
        return;
    }
    SDL_Rect srcrect = { textureX , textureY , width , height };
    SDL_Rect dstrect = { mapX - Camera::getInstance()->position.getX(), mapY - Camera::getInstance()->position.getY() , width , height };
    SDL_RenderCopy(Game::GetInstance()->renderer, _textureMap[id], &srcrect, &dstrect);
}

void AssetManager::renderTextureRect(SDL_Renderer* renderer, std::string textureId, int x, int y, int w, int h) {
    // Tìm kiếm texture trong _textureMap theo id
    auto it = _textureMap.find(textureId);

    if (it == _textureMap.end()) {
        // Nếu không tìm thấy, in ra thông báo lỗi và return
        std::cerr << "Texture not found: " << textureId << std::endl;
        return;
    }

    SDL_Texture* texture = it->second;

    SDL_Rect destRect = { x, y, w, h };

    // Render texture
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void AssetManager::renderRect(SDL_Rect rect)
{
    SDL_SetRenderDrawColor(Game::GetInstance()->renderer, 255, 255, 255, 255);
    SDL_Rect tempRect = { rect.x - Camera::getInstance()->position.getX(), rect.y - Camera::getInstance()->position.getY(),
                        rect.w, rect.h };

    if (SDL_RenderDrawRect(Game::GetInstance()->renderer, &tempRect) != 0) {
        std::cerr << "SDL_RenderDrawRect Error: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(Game::GetInstance()->renderer, 0, 0, 0, 255);
}

void AssetManager::renderRect(SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(Game::GetInstance()->renderer, color.r, color.g, color.b, color.a);
    SDL_Rect tempRect = { rect.x - Camera::getInstance()->position.getX(), rect.y - Camera::getInstance()->position.getY(),
                        rect.w, rect.h };

    if (SDL_RenderDrawRect(Game::GetInstance()->renderer, &tempRect) != 0) {
        std::cerr << "SDL_RenderDrawRect Error: " << SDL_GetError() << std::endl;
    }

    // Reset màu vẽ lại sau khi hoàn thành
    SDL_SetRenderDrawColor(Game::GetInstance()->renderer, 0, 0, 0, 255);
}

void AssetManager::playSound(std::string id)
{
    Mix_Chunk* sound = _soundMap[id];
    if (!sound) {
        std::cerr << "Sound not found: " << id << std::endl;
        return;
    }

    Mix_PlayChannel(-1, sound, 0);
}

void AssetManager::playMusic(std::string id, int loop)
{
    if (idMusicPlaying != id) 
    {
        std::cout << "music play";
        stopMusic();
        Mix_Music* music = _musicMap[id];
        if (!music) {
            std::cerr << "Music not found: " << id << std::endl;
            return;
        }

        if (Mix_PlayMusic(music, loop) == -1) {
            std::cerr << "Mix_PlayMusic: " << Mix_GetError() << std::endl;
        }
        idMusicPlaying = id;
    }
}

void AssetManager::stopMusic()
{
    Mix_HaltMusic();
}

void AssetManager::playSound(std::string id, int channel)
{
    Mix_Chunk* sound = _soundMap[id];
    if (!sound) {
        std::cerr << "Sound not found: " << id << std::endl;
        return;
    }

    if (Mix_PlayChannel(channel, sound, 0) == -1) {
        std::cerr << "Unable to play sound: " << Mix_GetError() << std::endl;
    }
}

void AssetManager::increaseMusicVolume() {
    currentMusicVolumePercent += 10;
    if (currentMusicVolumePercent > 100) {
        currentMusicVolumePercent = 100;
    }

    int newVolume = (currentMusicVolumePercent * MIX_MAX_VOLUME) / 100;
    Mix_VolumeMusic(newVolume);
}

void AssetManager::decreaseMusicVolume() {
    currentMusicVolumePercent -= 10;
    if (currentMusicVolumePercent < 0) {
        currentMusicVolumePercent = 0;
    }

    int newVolume = (currentMusicVolumePercent * MIX_MAX_VOLUME) / 100;
    Mix_VolumeMusic(newVolume);
}

void AssetManager::increaseSFXVolume() {
    currentSFXVolumePercent += 10;
    if (currentSFXVolumePercent > 100) {
        currentSFXVolumePercent = 100;
    }

    int newVolume = (currentSFXVolumePercent * MIX_MAX_VOLUME) / 100;
    Mix_Volume(-1, newVolume);
}

void AssetManager::decreaseSFXVolume() {
    currentSFXVolumePercent -= 10;
    if (currentSFXVolumePercent < 0) {
        currentSFXVolumePercent = 0;
    }

    int newVolume = (currentSFXVolumePercent * MIX_MAX_VOLUME) / 100;
    Mix_Volume(-1, newVolume);
}

int AssetManager::getMusicVolume() const {
    return currentMusicVolumePercent;
}

int AssetManager::getSFXVolume() const {
    return currentSFXVolumePercent;
}

void AssetManager::unmuteVolume() {
    int newMusicVolume = (currentMusicVolumePercent * MIX_MAX_VOLUME) / 100;
    int newSFXVolume = (currentSFXVolumePercent * MIX_MAX_VOLUME) / 100;
    Mix_VolumeMusic(newMusicVolume);
    Mix_Volume(-1, newSFXVolume); 
}

void AssetManager::muteVolume() {
    Mix_VolumeMusic(0); 
    Mix_Volume(-1, 0);  
}

bool AssetManager::isMuted() const {
    return Mix_VolumeMusic(-1) == 0 && Mix_Volume(-1, -1) == 0; // Kiểm tra nếu âm lượng là 0 thì đang mute
}


void AssetManager::renderText(SDL_Renderer* renderer, std::string message, std::string fontId, SDL_Color color, int x, int y)
{
    TTF_Font* font = _fontMap[fontId];
    if (!font) {
        std::cerr << "Font not found: " << fontId << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void AssetManager::renderText(SDL_Renderer* renderer, std::string message, std::string fontId, SDL_Color color, int x, int y, int w, int h)
{
    TTF_Font* font = _fontMap[fontId];
    if (!font) {
        std::cerr << "Font not found: " << fontId << std::endl;
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


float AssetManager::textureWidth(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    if (!texture) {
        std::cerr << "Texture not found: " << id << std::endl;
        return 0;
    }
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.w;
}

float AssetManager::textureHeight(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    if (!texture) {
        std::cerr << "Texture not found: " << id << std::endl;
        return 0;
    }
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.h;
}

