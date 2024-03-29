/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Player.h"
#include "Enemy0.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Missile.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	bool gameOver = false;
	bool gameStarted = false;
	FrameTimer ft;
	Player player0;
	static constexpr int enemy0NumMax = 100;
	int enemy0Num = 1;
	Enemy0 enemy0[enemy0NumMax];
	static constexpr int  bombNumMax = 1000;
	int bombCurrent = 0;
	Bomb bomb[bombNumMax];
	static constexpr int bulletNumMax = 1000;
	int bulletCurrent = 0;
	Bullet bullet[bulletNumMax];
	static constexpr int missileNumMax = 4;
	int missileCurrent = 0;
	Missile missile[missileNumMax];
	/********************************/
};