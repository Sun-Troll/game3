#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Player
{
public:
	void Move(bool right, bool left, bool down, bool up);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
private:
	static constexpr float acc = 0.2f;
	static constexpr float drag = 0.95f;
	static constexpr float bounce = -0.5f;
	Color c{ 255, 255, 255 };
	static constexpr int width = 20;
	static constexpr int height = 20;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
	bool fly = false;
};