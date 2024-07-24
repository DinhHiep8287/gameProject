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

    _soundMap[id] = sound;
    return true;
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
    //cout << " x : " << x - Camera::getInstance()->pos.x * paralaxSpeed << "  y : " << y - Camera::getInstance()->pos.y * paralaxSpeed << endl;
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

void AssetManager::playSound(std::string id)
{
    Mix_Chunk* sound = _soundMap[id];
    if (!sound) {
        std::cerr << "Sound not found: " << id << std::endl;
        return;
    }

    Mix_PlayChannel(-1, sound, 0);
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


float AssetManager::textureWidth(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.w;
    
}

float AssetManager::textureHeight(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.h;
}

