#include "Bullet.h"

void Bullet::Spawn(const Vec2 & owner_pos, const Vec2& aim_point)
{
	pos = owner_pos;
	pos.x -= width / 2.0f;
	vel = (aim_point - owner_pos).Normalize() * velSet;
	spawned = true;
}

void Bullet::Move(float tick_time)
{
	vel *= pow(drag, tick_time);

	pos += vel * tick_time * 60.0f;
}

void Bullet::ClampScreen()
{
	if (pos.x < 2.0f || pos.x > float(Graphics::ScreenWidth - width - 2) ||
		pos.y < 102.0f || pos.y > float(Graphics::ScreenHeight - height - 2))
	{
		spawned = false;
	}
}

bool Bullet::EnemyHit(const Vec2 & target_pos, const Vec2 & target_rb, int enemy_hp)
{
	if (pos.x < target_rb.x && pos.x + width > target_pos.x &&
		pos.y < target_rb.y && pos.y + height > target_pos.y && enemy_hp > 0)
	{
		spawned = false;
		return true;
	}
	return false;
}

void Bullet::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim(int(pos.x), int(pos.y), width, height, c);
}

bool Bullet::GetSpawned() const
{
	return spawned;
}

int Bullet::GetDamage() const
{
	return damage;
}

int Bullet::GetMpDrain() const
{
	return mpDrain;
}
