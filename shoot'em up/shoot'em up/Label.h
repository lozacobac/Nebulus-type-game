#pragma once
#include <SDL3/SDL.h>
#include <string>
class Label
{
public:
	Label(float x, float y, const std::string& text, float scale = 1.0f);

	void render(SDL_Renderer* renderer);

	void setPosition(float x, float y);
	void setText(const std::string& newText);
	void setScale(float scale);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

	std::string getText()const;
	float getX() const;
	float getY() const;

private:
	float m_x;
	float m_y;
	std::string m_text;
	float m_scale;
	Uint8 m_r, m_g, m_b, m_a;
};

