#include "Player.h"

void Player::Move(bool right, bool left, bool down, bool up)
{
	Vec2 vAcc(0, 0);
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
	vel += vAcc.GetNormalized() * acc;
	vel *= drag;
	
	pos += vel;
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
