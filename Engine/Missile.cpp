#include "Missile.h"

void Missile::Spawn(const Vec2 & owner_pos, const Vec2 & owner_vel)
{
	pos = owner_pos;
	pos.x -= width / 2.0f;
	vel = owner_vel;
	spawned = true;
}

void Missile::Move(float tick_time, const Vec2 & target_pos)
{
	vel += (target_pos - pos).Normalize() * acc * tick_time;
	vel *= pow(drag, tick_time);

	pos += vel * tick_time * 60.0f;
}

void Missile::ClampScreen()
{
	if (pos.x < 2.0f || pos.x > float(Graphics::ScreenWidth - width - 2) ||
		pos.y < 102.0f || pos.y > float(Graphics::ScreenHeight - height - 2))
	{
		spawned = false;
	}
}

bool Missile::PlayerHit(const Vec2 & target_pos, const Vec2 & target_rb)
{
	if (pos.x < target_rb.x && pos.x + width > target_pos.x &&
		pos.y < target_rb.y && pos.y + height > target_pos.y)
	{
		spawned = false;
		return true;
	}
	return false;
}

void Missile::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim(int(pos.x), int(pos.y), width, height, c);
}

bool Missile::GetSpawned() const
{
	return spawned;
}

int Missile::GetDamage() const
{
	return damage;
}
