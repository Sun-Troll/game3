#pragma once


#include "Graphics.h"
#include "Vec2.h"

class Bullet
{
public:
	void Spawn(const Vec2& owner_pos, const Vec2& aim_point);
	void Move(float tick_time);
	void ClampScreen();
	bool EnemyHit(const Vec2& target_pos, const Vec2& target_rb);
	void Draw(Graphics& gfx) const;
	bool GetSpawned() const;
	int GetDamage() const;
private:
	bool spawned = false;
	static constexpr float maxTimeOnGround = 2.0f;
	static constexpr float drag = 0.6f;
	static constexpr float bounce = -0.9f;
	Color c{ 255, 255, 255 };
	static constexpr int width = 10;
	static constexpr int height = 10;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), float(Graphics::ScreenHeight - height - 2) };
	Vec2 vel{ 0.0f, 0.0f };
	float velSet = 100.0f;
	static constexpr int damage = 1000000;
};