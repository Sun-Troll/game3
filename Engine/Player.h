#pragma once

#include "Graphics.h"
#include "Vec2.h"

class Player
{
public:
	void Move(float tick_time, bool right, bool left, bool down, bool up, bool jump);
	void ClampScreen();
	void MpRegen(float tick_time);
	void ReciveDamage(int damage);
	void MpDrain(int mp_drain);
	void AttackTimeAdd(float tick_time);
	void AttackTimeReset();
	void Draw(Graphics& gfx) const;
	void DrawHp(Graphics& gfx) const;
	void DrawMp(Graphics& gfx) const;
	const Vec2& GetPos() const;
	const Vec2& GetVel() const;
	Vec2 GetMiddleX() const;
	Vec2 GetBottomRight() const;
	int GetHp() const;
	int GetMp() const;
	float GetMaxAttTime() const;
	float GetCurAttTime() const;
private:
	static constexpr float maxAttackTime = 0.1f;
	float currentAttackTime = maxAttackTime;
	static constexpr int hpMax = 10000000;
	int hp = hpMax;
	static constexpr int mpMax = 10000000;
	int mp = mpMax;
	static constexpr float mpRegen = 1000000.0f;
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