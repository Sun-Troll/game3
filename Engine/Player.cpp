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

void Player::MpRegen()
{
	mp += mpRegen;
}

void Player::ReciveDamage(int damage)
{
	hp -= damage;
}

void Player::MpDrain(int mp_drain)
{
	mp -= mp_drain;
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

void Player::DrawMp(Graphics & gfx) const
{
	gfx.DrawRectDim(450, 40, mpMax / 50000, 11, Colors::Red);
	gfx.DrawRectDim(450, 43, mp / 50000, 5, Colors::Yellow);
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
	return Vec2(pos.x + width / 2.0f, pos.y);
}

Vec2 Player::GetBottomRight() const
{
	return Vec2(pos.x + width, pos.y + height);
}

int Player::GetHp() const
{
	return hp;
}

int Player::GetMp() const
{
	return mp;
}
