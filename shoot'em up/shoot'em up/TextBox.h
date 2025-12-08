#pragma once
#include <SDL3/SDL.h>
#include <string>

class TextBox {
public:
    TextBox(float x, float y, float width, float height, size_t maxLength = 32);
    ~TextBox();

    void handleEvent(const SDL_Event& e);
    void update();
    void render(SDL_Renderer* renderer);

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setText(const std::string& newText);
    std::string getText() const;
    void clear();

    void setFocused(bool focus);
    bool isFocused() const;

private:
    SDL_FRect m_box;
    std::string m_text;
    size_t m_maxLength;
    bool m_focused;
    bool m_cursorVisible;
    Uint32 m_lastBlink;

    SDL_Cursor* m_cursorIBeam;
    SDL_Cursor* m_cursorArrow;

    bool isPointInside(float x, float y) const;
    void updateCursor(SDL_Renderer* renderer);
};

