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
	float tickTime = ft.TimePassed();
	bool right = false;
	bool left = false;
	bool down = false;
	bool up = false;
	bool jump = false;
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
	player0.Move(tickTime, right, left, down, up, jump);
	player0.ClampScreen();
}

void Game::ComposeFrame()
{
	gfx.DrawRect(0, Graphics::ScreenHeight - 2, Graphics::ScreenWidth, Graphics::ScreenHeight, Colors::Red);
	gfx.DrawRect(0, 100, Graphics::ScreenWidth, 102, Colors::Red);
	gfx.DrawRect(0, 102, 2, Graphics::ScreenHeight - 2, Colors::Red);
	gfx.DrawRect(Graphics::ScreenWidth - 2, 102, Graphics::ScreenWidth, Graphics::ScreenHeight - 2, Colors::Red);
	player0.Draw(gfx);
}
