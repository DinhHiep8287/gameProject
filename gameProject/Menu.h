#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include "AssetManager.h"
#include <vector>
#include <string>

enum MenuItemState {
    NORMAL,
    HOVERED,
    CLICKED
};

class MenuItem {
public:
    MenuItem(const std::string& text, int x, int y, int w, int h)
        : text(text), x(x), y(y), width(w), height(h) {}

    virtual void render(SDL_Renderer* renderer) = 0; // Lớp con phải cài đặt

    SDL_Rect getRect() const { return SDL_Rect{ x, y, width, height }; }

protected:
    std::string text;
    int x, y;
    int width, height;
};

class Button : public MenuItem {
public:
    Button(const std::string& text, const std::string& normalTextureId, const std::string& hoveredTextureId, int x, int y, int w, int h)
        : MenuItem(text, x, y, w, h), normalTextureId(normalTextureId), hoveredTextureId(hoveredTextureId), state(NORMAL) {}

    void render(SDL_Renderer* renderer) override {
        // Chọn texture dựa trên trạng thái của nút
        std::string textureId = (state == HOVERED) ? hoveredTextureId : normalTextureId;
        AssetManager::GetInstance()->renderTextureRect(renderer, textureId, x, y, width, height);

        // Thiết lập màu chữ
        SDL_Color textColor = (state == HOVERED) ? SDL_Color{ 255, 0, 0, 255 } : SDL_Color{ 255, 255, 255, 255 };

        // Render text ở giữa rect
        int textWidth, textHeight;
        TTF_SizeText(AssetManager::GetInstance()->getFont("fontGame"), text.c_str(), &textWidth, &textHeight);
        int centeredX = x + (width - textWidth) / 2;
        int centeredY = y + (height - textHeight) / 2;
        AssetManager::GetInstance()->renderText(renderer, text, "fontGame", textColor, centeredX, centeredY);
    }

    bool handleEvent(const SDL_Event& e) {
        if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.motion.x;
            int mouseY = e.motion.y;
            SDL_Point mousePoint{ mouseX, mouseY };
            SDL_Rect rect = getRect();
            if (SDL_PointInRect(&mousePoint, &rect)) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    AssetManager::GetInstance()->playSound("button");
                    state = CLICKED;
                    return true; // Button được nhấn
                }
                state = HOVERED;
            }
            else {
                state = NORMAL;
            }
        }
        return false; // Không có sự kiện nhấn
    }

private:
    std::string normalTextureId;
    std::string hoveredTextureId;
    MenuItemState state;
};

class Panel : public MenuItem {
public:
    Panel(const std::string& text, const std::string& textureId, int x, int y, int w, int h)
        : MenuItem(text, x, y, w, h), textureId(textureId) {}

    void render(SDL_Renderer* renderer) override {
        AssetManager::GetInstance()->renderTextureRect(renderer, textureId, x, y, width, height);

        // Render text ở giữa rect
        int textWidth, textHeight;
        TTF_SizeText(AssetManager::GetInstance()->getFont("fontGame"), text.c_str(), &textWidth, &textHeight);
        int centeredX = x + (width - textWidth) / 2;
        int centeredY = y + (height - textHeight) / 2;
        AssetManager::GetInstance()->renderText(renderer, text, "fontGame", { 255, 255, 255, 255 }, centeredX, centeredY);
    }
private:
    std::string textureId;
};

class Menu {
public:
    void addPanel(std::unique_ptr<Panel> panel) {
        panels.push_back(std::move(panel));
    }

    void addButton(std::unique_ptr<Button> button) {
        buttons.push_back(std::move(button));
    }

    void render(SDL_Renderer* renderer) {
        // Render các Panel trước
        for (const auto& panel : panels) {
            panel->render(renderer);
        }

        // Render các Button sau
        for (const auto& button : buttons) {
            button->render(renderer);
        }
    }

    int handleEvent(const SDL_Event& e) {
        // Kiểm tra các Button
        for (int i = 0; i < buttons.size(); ++i) {
            if (buttons[i]->handleEvent(e)) {
                return i; // Trả về index của Button được nhấn
            }
        }
        return -1; // Không có Button nào được nhấn
    }

private:
    std::vector<std::unique_ptr<Panel>> panels;
    std::vector<std::unique_ptr<Button>> buttons;
};
