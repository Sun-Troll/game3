#include "bomb.h"

void Bomb::Spawn(const Vec2& owner_pos, const Vec2& owner_vel)
{
	pos = owner_pos;
	pos.x -= width / 2.0f;
	vel = owner_vel;
	spawned = true;
}

void Bomb::Move(float tick_time)
{
	vel.y += gravity * tick_time;;
	vel *= pow(drag, tick_time);

	pos += vel * tick_time * 60.0f;
	
	if (pos.y >= float(Graphics::ScreenHeight - height - 2))
	{
		timeOnGround += tick_time;
	}
	if (timeOnGround > maxTimeOnGround)
	{
		spawned = false;
	}
}

void Bomb::ClampScreen()
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

bool Bomb::PlayerHit(const Vec2 & target_pos, const Vec2 & target_rb)
{
	if (pos.x < target_rb.x && pos.x + width > target_pos.x &&
		pos.y < target_rb.y && pos.y + height > target_pos.y)
	{
		spawned = false;
		return true;
	}
	return false;
}

void Bomb::Draw(Graphics& gfx) const
{
	gfx.DrawRectDim(int(pos.x), int(pos.y), width, height, c);
}

bool Bomb::GetSpawned() const
{
	return spawned;
}

int Bomb::GetDamage() const
{
	return damage;
}

