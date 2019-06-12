#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Missile
{
public:
	void Spawn(const Vec2& owner_pos, const Vec2& owner_vel);
	void Move(float tick_time, const Vec2& target_pos);
	void ClampScreen();
	bool PlayerHit(const Vec2& target_pos, const Vec2& target_rb);
	void Draw(Graphics& gfx) const;
	bool GetSpawned() const;
	int GetDamage() const;
private:
	bool spawned = false;
	float timeOnGround = 0.0f;
	static constexpr float acc = 16.0f;
	static constexpr float drag = 0.7f;
	static constexpr float bounce = -0.9f;
	static constexpr float gravity = 20.0f;
	Color c{ 0, 255, 0 };
	static constexpr int width = 30;
	static constexpr int height = 30;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
	static constexpr int damage = 2000000;
};