#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Player
{
public:
	void Move(float tick_time, bool right, bool left, bool down, bool up, bool jump);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
private:
	static constexpr float acc = 12.0f;
	static constexpr float drag = 2.0f;
	static constexpr float bounce = -0.5f;
	float jumpVal = 0.0f;
	static constexpr float jumpCharge = 25.0f;
	static constexpr float jumpMax = 50.0f;
	static constexpr float gravity = 10.0f;
	Color c{ 255, 255, 255 };
	static constexpr int width = 40;
	static constexpr int height = 40;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
	bool fly = false;
};