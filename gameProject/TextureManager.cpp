#include "TextureManager.h"
TextureManager* TextureManager::instance = nullptr;

bool TextureManager::load(std::string id, std::string fileName)
{
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == nullptr)
    {
        SDL_Log(" Fail to load Texture : ", fileName.c_str(), SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetInstance()->renderer, surface);
    if (texture == nullptr)
    {
        SDL_Log(" Fail to load Texture from surface : ", SDL_GetError());
    }
    _textureMap[id] = texture;
    return true;
}
void TextureManager::drop(std::string id)
{
    SDL_DestroyTexture(_textureMap[id]);
    _textureMap.erase(id);
}

void TextureManager::draw(std::string id, float x, float y, float width, float height, SDL_RendererFlip flip, float paralaxSpeed)
{
    SDL_Rect srcrect = { 0 , 0 , width , height };
    SDL_Rect dstrect = { x - Camera::getInstance()->position.getX() * paralaxSpeed , y - Camera::getInstance()->position.getY() * paralaxSpeed , width , height };
    //cout << " x : " << x - Camera::getInstance()->pos.x * paralaxSpeed << "  y : " << y - Camera::getInstance()->pos.y * paralaxSpeed << endl;
    SDL_RenderCopyEx(Game::GetInstance()->renderer, _textureMap[id], &srcrect, &dstrect, 0, NULL, flip);
}

void TextureManager::drawFrame(std::string id, float x, float y, float width, float height, int row, int frame, SDL_RendererFlip flip)
{
    // Tọa độ của 1 source frame sẽ được xác định bởi x = Chiều Dài 1 frame * thứ tự frame ; y = Chiều cao 1 frame * thứ tự cột
    SDL_Rect srcrect = { width * frame , height * row , width , height };
    SDL_Rect dstrect = { x - Camera::getInstance()->position.getX(), y - Camera::getInstance()->position.getY() , width , height};
    SDL_RenderCopyEx(Game::GetInstance()->renderer, _textureMap[id], &srcrect, &dstrect, 0, NULL, flip);
}

float TextureManager::textureWidth(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.w;
}

float TextureManager::textureHeight(std::string id)
{
    SDL_Texture* texture = _textureMap[id];
    SDL_Rect rect1;
    SDL_QueryTexture(texture, NULL, NULL, &rect1.w, &rect1.h);
    return rect1.h;
}

