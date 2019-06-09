#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Bomb
{
public:
	void Spawn(const Vec2 owner_pos, const Vec2 owner_vel);
	void Move(float tick_time);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
	bool GetSpawned() const;
private:
	bool spawned = false;
	static constexpr float drag = 0.1f;
	static constexpr float bounce = -0.6f;
	static constexpr float gravity = 20.0f;
	Color c{ 255, 255, 255 };
	static constexpr int width = 20;
	static constexpr int height = 30;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
};