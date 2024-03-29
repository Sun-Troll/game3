/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver && gameStarted)
	{
		float tickTime = ft.TimePassed();
		bool right = false;
		bool left = false;
		bool down = false;
		bool up = false;
		bool jump = false;
		bool attack = false;
		if (wnd.kbd.KeyIsPressed('D'))
		{
			right = true;
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			left = true;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			down = true;
		}
		if (wnd.kbd.KeyIsPressed('W'))
		{
			up = true;
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			jump = true;
		}
		if (wnd.mouse.LeftIsPressed())
		{
			attack = true;
		}
		player0.Move(tickTime, right, left, down, up, jump);
		player0.ClampScreen();
		player0.MpRegen(tickTime);
		player0.AttackTimeAdd(tickTime);
		if (attack && player0.GetMp() > 0 && player0.GetCurAttTime() >= player0.GetMaxAttTime())
		{
			player0.AttackTimeReset();
			player0.MpDrain(bullet[bulletCurrent].GetMpDrain());
			Vec2 mousePos(float(wnd.mouse.GetPosX()), float(wnd.mouse.GetPosY()));
			bullet[bulletCurrent].Spawn(player0.GetMiddleX(), Vec2(float(wnd.mouse.GetPosX()), float(wnd.mouse.GetPosY())));
			if (bulletCurrent < bulletNumMax)
			{
				++bulletCurrent;
			}
			else
			{
				bulletCurrent = 0;
			}
		}
		for (int i = 0; i < enemy0Num; ++i)
		{
			if (enemy0[i].GetHp() > 0)
			{
				right = false;
				left = false;
				down = false;
				up = false;
				jump = false;
				attack = false;
				enemy0[i].AI(player0.GetMiddleX(), player0.GetVel(), right, left, attack);
				enemy0[i].Move(tickTime, right, left, down, up, jump);
				enemy0[i].ClampScreen();
				enemy0[i].ColorSet();
				enemy0[i].AttackTimeAdd(tickTime);
				if (attack && enemy0[i].GetCurAttTime() >= enemy0[i].GetMaxAttTime() * 100 && enemy0[i].GetStage() == 1)
				{
					enemy0[i].AttackTimeReset();
					missile[missileCurrent].Spawn(enemy0[i].GetMiddleX(), enemy0[i].GetVel());
					if (missileCurrent < missileNumMax)
					{
						++missileCurrent;
					}
					else
					{
						missileCurrent = 0;
					}
				}
				else if (attack && enemy0[i].GetCurAttTime() >= enemy0[i].GetMaxAttTime())
				{
					enemy0[i].AttackTimeReset();
					bomb[bombCurrent].Spawn(enemy0[i].GetMiddleX(), enemy0[i].GetVel());
					if (bombCurrent < bombNumMax)
					{
						++bombCurrent;
					}
					else
					{
						bombCurrent = 0;
					}
				}
			}
			else
			{
				enemy0[i].NextStage();
			}
		}
		for (int i = 0; i < bulletNumMax; ++i)
		{
			if (bullet[i].GetSpawned())
			{
				bullet[i].Move(tickTime);
				bullet[i].ClampScreen();
				for (int ie = 0; ie < enemy0Num; ++ie)
				{
					if (bullet[i].EnemyHit(enemy0[ie].GetPos(), enemy0[ie].GetBottomRight(), enemy0[ie].GetHp()))
					{
						enemy0[ie].ReciveDamage(bullet[i].GetDamage());
					}
				}
			}
			
		}
		for (int i = 0; i < bombNumMax; ++i)
		{
			if (bomb[i].GetSpawned())
			{
				bomb[i].Move(tickTime);
				bomb[i].ClampScreen();
				if (bomb[i].PlayerHit(player0.GetPos(), player0.GetBottomRight()))
				{
					player0.ReciveDamage(bomb[i].GetDamage());
				}
			}
		}
		for (int i = 0; i < missileNumMax; ++i)
		{
			if (missile[i].GetSpawned())
			{
				missile[i].Move(tickTime, player0.GetMiddleX());
				missile[i].ClampScreen();
				if (missile[i].PlayerHit(player0.GetPos(), player0.GetBottomRight()))
				{
					player0.ReciveDamage(missile[i].GetDamage());
				}
				missile[i].Despawn(tickTime);
			}
		}
		if (player0.GetHp() <= 0)
		{
			gameOver = true;
		}
	}
	if (!gameStarted && wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameStarted = true;
	}
}

void Game::ComposeFrame()
{
	gfx.DrawRect(0, Graphics::ScreenHeight - 2, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
	gfx.DrawRect(0, 100, Graphics::ScreenWidth, 102, Colors::Red);
	gfx.DrawRect(0, 102, 2, Graphics::ScreenHeight - 2, Colors::Red);
	gfx.DrawRect(Graphics::ScreenWidth - 2, 102, Graphics::ScreenWidth, Graphics::ScreenHeight - 2, Colors::Red);
	player0.DrawHp(gfx);
	player0.DrawMp(gfx);
	for (int i = 0; i < enemy0Num; ++i)
	{
		enemy0[i].Draw(gfx);
	}
	for (int i = 0; i < bombNumMax; ++i)
	{
		if (bomb[i].GetSpawned())
		{
			bomb[i].Draw(gfx);
		}
	}
	for (int i = 0; i < missileNumMax; ++i)
	{
		if (missile[i].GetSpawned())
		{
			missile[i].Draw(gfx);
		}
	}
	for (int i = 0; i < bulletNumMax; ++i)
	{
		if (bullet[i].GetSpawned())
		{
			bullet[i].Draw(gfx);
		}
	}
	player0.Draw(gfx);
}
