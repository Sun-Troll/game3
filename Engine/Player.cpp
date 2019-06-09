#include "Player.h"
#include <algorithm>

void Player::Move(float tick_time, bool right, bool left, bool down, bool up, bool jump)
{
	Vec2 vAcc(0.0f, 0.0f);
	if (right)
	{
		++vAcc.x;
	}
	if (left)
	{
		--vAcc.x;
	}
	if (fly)
	{
		if (down)
		{
			++vAcc.y;
		}
		if (up)
		{
			--vAcc.y;
		}
	}
	vAcc.Normalize() *= acc * tick_time;
	if (!fly)
	{
		if (jump && pos.y >= float(Graphics::ScreenHeight - height - 2))
		{
			jumpVal = std::max(-jumpMax, jumpVal - jumpCharge * tick_time);
		}
		else
		{
			vAcc.y += jumpVal;
			jumpVal = 0.0f;
		}
		vAcc.y += gravity * tick_time;
	}
	vel += vAcc;
	vel *= pow(drag, tick_time);
	
	pos += vel * tick_time * 60.0f;
}

void Player::ClampScreen()
{
	if (pos.x < 2.0f)
	{
		pos.x = 2.0f;
		vel.x *= bounce;
	}
	if (pos.x > float(Graphics::ScreenWidth - width - 2))
	{
		pos.x = float(Graphics::ScreenWidth - width - 2);
		vel.x *= bounce;
	}
	if (pos.y < 102.0f)
	{
		pos.y = 102.0f;
		vel.y *= bounce;
	}
	if (pos.y > float(Graphics::ScreenHeight - height - 2))
	{
		pos.y = float(Graphics::ScreenHeight - height - 2);
		vel.y *= bounce;
	}
}

void Player::Draw(Graphics& gfx) const
{
	gfx.DrawRectDim(int(pos.x), int(pos.y), width, height, c);
}

void Player::DrawHp(Graphics& gfx) const
{
	gfx.DrawRectDim(50, 40, hpMax / 50000, 11, Colors::Blue);
	gfx.DrawRectDim(50, 43, hp / 50000, 5, Colors::Green);
}

const Vec2& Player::GetPos() const
{
	return pos;
}

const Vec2 & Player::GetVel() const
{
	return vel;
}

Vec2 Player::GetMiddleX() const
{
	const Vec2 middleX(pos.x + width / 2.0f, pos.y);
	return middleX;
}
