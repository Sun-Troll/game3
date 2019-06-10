#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Enemy0
{
public:
	void Move(float tick_time, bool right, bool left, bool down, bool up, bool jump);
	void ClampScreen();
	void ReciveDamage(int damage);
	void ColorSet();
	void AI(const Vec2& target_pos, const Vec2& target_vel, bool& right, bool& left, bool& attack);
	void Draw(Graphics& gfx) const;
	const Vec2& GetPos() const;
	const Vec2& GetVel() const;
	Vec2 GetMiddleX() const;
	Vec2 GetBottomRight() const;
	int GetHp() const;
private:
	static constexpr int hpMax = 10000000;
	int hp = hpMax;
	static constexpr float acc = 8.0f;
	static constexpr float drag = 0.1f;
	static constexpr float bounce = -0.6f;
	float jumpVal = 0.0f;
	static constexpr float jumpCharge = 20.0f;
	static constexpr float jumpMax = 40.0f;
	static constexpr float gravity = 20.0f;
	Color c{ 255, 255, 0 };
	static constexpr int width = 50;
	static constexpr int height = 30;
	Vec2 pos{ float((Graphics::ScreenWidth - width) / 2), 102.0f };
	Vec2 vel{ 0.0f, 0.0f };
	bool fly = true;
};