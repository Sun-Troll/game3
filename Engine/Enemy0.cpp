#include "Enemy0.h"
#include <algorithm>

void Enemy0::Move(float tick_time, bool right, bool left, bool down, bool up, bool jump)
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

void Enemy0::ClampScreen()
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

void Enemy0::ReciveDamage(int damage)
{
	hp -= damage;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Enemy0::ColorSet()
{
	c.SetG(hp / 39215);
}

void Enemy0::AI(const Vec2& target_pos, const Vec2& target_vel, bool& right, bool& left, bool& attack)
{
	if (pos.x + width / 2.0f < target_pos.x + target_vel.x * 6.0f - 2.0f)
	{
		right = true;
	}
	if (pos.x + width / 2.0f > target_pos.x + target_vel.x * 6.0f + 2.0f)
	{
		left = true;
	}
	if (pos.x + width / 2.0f > target_pos.x + target_vel.x * 6.0f - 20.0f &&
		pos.x + width / 2.0f < target_pos.x + target_vel.x * 6.0f + 20.0f)
	{
		attack = true;
	}
}

void Enemy0::Draw(Graphics& gfx) const
{
	gfx.DrawRectDim(int(pos.x), int(pos.y), width, height, c);
}

const Vec2 & Enemy0::GetPos() const
{
	return pos;
}

const Vec2 & Enemy0::GetVel() const
{
	return vel;
}

Vec2 Enemy0::GetMiddleX() const
{
	return Vec2(pos.x + width / 2.0f, pos.y);
}

Vec2 Enemy0::GetBottomRight() const
{
	return Vec2(pos.x + width, pos.y + height);
}

int Enemy0::GetHp() const
{
	return hp;
}
