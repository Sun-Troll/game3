#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Player
{
public:
	void Move(float tick_time, bool right, bool left, bool down, bool up, bool jump);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
	void DrawHp(Graphics& gfx) const;
	const Vec2& GetPos() const;
	const Vec2& GetVel() const;
	Vec2 GetMiddleX() const;
private:
	static constexpr int hpMax = 10000000;
	int hp = hpMax;
	static constexpr float acc = 14.0f;
	static constexpr float drag = 0.1f;
	static constexpr float bounce = -0.6f;
	float jumpVal = 0.0f;
	static constexpr float jumpCharge = 20.0f;
	static constexpr float jumpMax = 40.0f;
	static constexpr float gravity = 20.0f;
	Color c{ 255, 255, 255 };
	static constexpr int width = 40;
	static constexpr int height = 40;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
	bool fly = false;
};