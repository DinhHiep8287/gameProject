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
    MenuItem(const std::string& id, const std::string& text, int x, int y, int w, int h)
        :id(id), text(text), x(x), y(y), width(w), height(h) {}

    virtual void render(SDL_Renderer* renderer) = 0; // Lớp con phải cài đặt

    SDL_Rect getRect() const { return SDL_Rect{ x, y, width, height }; }

    const std::string& getId() const {
        return id;
    }

protected:
    std::string id;
    std::string text;
    int x, y;
    int width, height;
};

class Button : public MenuItem {
public:
    Button(const std::string& id, const std::string& text, const std::string& normalTextureId, const std::string& hoveredTextureId, int x, int y, int w, int h)
        : MenuItem(id, text, x, y, w, h), normalTextureId(normalTextureId), hoveredTextureId(hoveredTextureId), state(NORMAL) {}

    void render(SDL_Renderer* renderer) override {
        // Chọn texture dựa trên trạng thái của nút
        std::string textureId = (state == HOVERED) ? hoveredTextureId : normalTextureId;
        AssetManager::GetInstance()->renderTextureRect(renderer, textureId, x, y, width, height);

        // Thiết lập màu chữ
        SDL_Color textColor = (state == HOVERED) ? SDL_Color{ 255, 0, 0, 255 } : SDL_Color{ 255, 255, 255, 255 };

        // Render text ở giữa rect
        if (!text.empty()) {
            int textWidth, textHeight;
            TTF_SizeText(AssetManager::GetInstance()->getFont("fontGame"), text.c_str(), &textWidth, &textHeight);
            int centeredX = x + (width - textWidth) / 2;
            int centeredY = y + (height - textHeight) / 2;
            AssetManager::GetInstance()->renderText(renderer, text, "fontGame", textColor, centeredX, centeredY);
        }

    }

    const std::string& getText() const {
        return text;
    }

    void setNormalTextureId(const std::string& newNormalTextureId) {
        normalTextureId = newNormalTextureId;
    }
    void setHoveredTextureId(const std::string& newHoveredTextureId) {
        hoveredTextureId = newHoveredTextureId;
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
        else if (e.type == SDL_MOUSEBUTTONUP && state == CLICKED) {
            // Sau khi xử lý sự kiện CLICKED, kiểm tra lại trạng thái HOVERED
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            SDL_Point mousePoint{ mouseX, mouseY };
            SDL_Rect rect = getRect();
            if (SDL_PointInRect(&mousePoint, &rect)) {
                state = HOVERED;
            }
            else {
                state = NORMAL;
            }
        }
        return false; // Không có sự kiện nhấn
    }

public:
    std::string normalTextureId;
    std::string hoveredTextureId;
    MenuItemState state;
};

class Panel : public MenuItem {
public:
    Panel(const std::string& id, const std::string& text, const std::string& textureId, int x, int y, int w, int h)
        : MenuItem(id, text, x, y, w, h), textureId(textureId) {}

    void render(SDL_Renderer* renderer) override {
        AssetManager::GetInstance()->renderTextureRect(renderer, textureId, x, y, width, height);

        // Render text ở giữa rect
        if (!text.empty())
        {
            int textWidth, textHeight;
            TTF_SizeText(AssetManager::GetInstance()->getFont("fontGame"), text.c_str(), &textWidth, &textHeight);
            int centeredX = x + (width - textWidth) / 2;
            int centeredY = y + (height - textHeight) / 2;
            AssetManager::GetInstance()->renderText(renderer, text, "fontGame", { 255, 255, 255, 255 }, centeredX, centeredY);
        }
    }
private:
    std::string textureId;
};

class Label : public MenuItem {
public:
    Label(const std::string& id, const std::string& text, const std::string& fontId, SDL_Color color, int x, int y, int w, int h)
        : MenuItem(id, text, x, y, w, h), fontId(fontId), color(color){}

    void render(SDL_Renderer* renderer) override {
        // Render text ở giữa rect
        int textWidth, textHeight;
        TTF_SizeText(AssetManager::GetInstance()->getFont(fontId), text.c_str(), &textWidth, &textHeight);
        int centeredX = x + (width - textWidth) / 2;
        int centeredY = y + (height - textHeight) / 2;
        AssetManager::GetInstance()->renderText(renderer, text, fontId, color, centeredX, centeredY);
    }

    void setText(const std::string& newText) {
        text = newText;
    }

    void setColor(SDL_Color newColor) {
        color = newColor;
    }

private:
    std::string fontId;
    SDL_Color color;
};

class Menu {
public:
    void addPanel(std::unique_ptr<Panel> panel) {
        panels.push_back(std::move(panel));
    }

    void addButton(std::unique_ptr<Button> button) {
        buttons.push_back(std::move(button));
    }

    void addLabel(std::unique_ptr<Label> label) {
        labels.push_back(std::move(label));
    }

    void updateLabel(const std::string& id, const std::string& newText) {
        for (auto& label : labels) {
            if (label && label->getId() == id) {
                label->setText(newText);
                break;
            }
        }
    }

    void updateButtonTexture(const std::string& text, const std::string& newNormalTextureId, const std::string& newHoveredTextureId) {
        for (auto& button : buttons) {
            if (button && button->getId() == text) {
                button->setNormalTextureId(newNormalTextureId);
                button->setHoveredTextureId(newHoveredTextureId);
                break;
            }
        }
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
        
        for (const auto& label : labels) {
            label->render(renderer);
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
    std::vector<std::unique_ptr<Label>> labels;
};

class Setting : public Menu {
public:
    Setting(int x, int y, int w, int h) {
        int panelWidth = SIZE * 15;
        int panelHeight = SIZE * 10; // Tăng chiều cao panel để phù hợp với thiết kế mới
        int panelX = (NUM_SCREEN_X * SIZE - panelWidth) / 2;
        int panelY = (NUM_SCREEN_Y * SIZE - panelHeight) / 2;

        // Thêm Panel vào SettingMenu
        addPanel(std::make_unique<Panel>("SettingPanel", "", "panelTexture", panelX, panelY, panelWidth, panelHeight));

        // Tính toán vị trí của các thành phần
        int labelWidth = SIZE * 3;
        int labelHeight = SIZE * 1.5;
        int buttonSize = SIZE * 1.5; // Nút tăng giảm âm lượng hình vuông
        int volumeLabelWidth = SIZE * 3;

        // Vị trí hàng đầu tiên
        int firstRowY = panelY + SIZE * 2;
        int labelX = panelX + SIZE * 1;
        int decreaseButtonX = labelX + labelWidth + SIZE * 0.5;
        int increaseButtonX = decreaseButtonX + buttonSize + SIZE * 0.5;
        int volumeLabelX = increaseButtonX + buttonSize + SIZE * 0.5;

        // Thêm các thành phần hàng đầu tiên vào SettingMenu
        addLabel(std::make_unique<Label>("MusicLabel", "Music:", "fontGame", SDL_Color{ 255, 255, 255, 255 }, labelX, firstRowY, labelWidth, labelHeight));
        addButton(std::make_unique<Button>("IncreaseVolume", "", "rightNormalButtonTexture", "rightHoveredButtonTexture", increaseButtonX, firstRowY, buttonSize, buttonSize));
        addButton(std::make_unique<Button>("DecreaseVolume", "", "leftNormalButtonTexture", "leftHoveredButtonTexture", decreaseButtonX, firstRowY, buttonSize, buttonSize));
        addLabel(std::make_unique<Label>("Volume", std::to_string(AssetManager::GetInstance()->getVolume()), "fontGame", SDL_Color{ 255, 255, 255, 255 }, volumeLabelX, firstRowY, volumeLabelWidth, labelHeight));

        // Vị trí hàng thứ hai (Label "Mute:" và Button "Mute/Unmute")
        int secondRowY = firstRowY + labelHeight + SIZE * 1.5;
        int muteLabelX = labelX;
        int muteButtonX = muteLabelX + labelWidth + SIZE * 0.5;

        // Thêm Label "Mute:" và Button "Mute/Unmute" vào hàng thứ hai
        addLabel(std::make_unique<Label>("MuteLabel", "Mute:", "fontGame", SDL_Color{ 255, 255, 255, 255 }, muteLabelX, secondRowY, labelWidth, labelHeight));
        addButton(std::make_unique<Button>("Mute", "", "unmuteNormalButtonTexture", "unmuteHoveredButtonTexture", muteButtonX, secondRowY, buttonSize, buttonSize));

        // Vị trí hàng thứ ba (nút "Back")
        int thirdRowY = secondRowY + labelHeight + SIZE * 1.5;
        int buttonWidth = SIZE * 6;
        int buttonHeight = SIZE * 1.5;
        int backButtonX = panelX + (panelWidth - buttonWidth) / 2;

        // Thêm nút "Back" vào hàng thứ ba
        addButton(std::make_unique<Button>("Back", "Back", "buttonNormalTexture", "buttonHoveredTexture", backButtonX, thirdRowY, buttonWidth, buttonHeight));
    }
};
