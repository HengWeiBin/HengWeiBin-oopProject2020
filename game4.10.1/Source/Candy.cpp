#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), x(x), y(y), dx(x), dy(y), alive(1)
	{

	}

	Candy::Candy() : style(0)
	{
		
	}

	Candy::~Candy()
	{

	}

	void Candy::LoadBitmap()
	{
		char BitmapDir[50];
		GetBitmapDirectory(style, BitmapDir);
		bmp.LoadBitmap(BitmapDir, RGB(255, 255, 255));
	}

	void Candy::OnMove()
	{
		if (x != dx)
			x > dx ? x-= 5 : x+= 5;
		if (y != dy)
			y > dy ? y-= 5 : y+= 5;
	}

	void Candy::OnShow()
	{
		if (IsAlive())
		{
			bmp.SetTopLeft(x, y);
			bmp.ShowBitmap();
		}
	}

	void Candy::SetDestination(int x, int y)
	{
		dx = x;
		dy = y;
	}

	bool Candy::IsAlive()
	{
		return alive;
	}

	void Candy::SetAlive(bool alive)
	{
		this->alive = alive;
	}

	int Candy::GetStyle()
	{
		return style;
	}

	void Candy::SetStyle(int style)
	{
		this->style = style;
	}

	void Candy::GetBitmapDirectory(int style, char* BitmapDir)
	{
		switch (style)
		{
		case 1:
			strcpy(BitmapDir, ".\\Bitmaps\\RedCandy.bmp");
			break;
		case 2:
			strcpy(BitmapDir, ".\\Bitmaps\\OrangeCandy.bmp");
			break;
		case 3:
			strcpy(BitmapDir, ".\\Bitmaps\\GreenCandy.bmp");
			break;
		case 4:
			strcpy(BitmapDir, ".\\Bitmaps\\BlueCandy.bmp");
			break;
		case 5:
			strcpy(BitmapDir, ".\\Bitmaps\\PurpleCandy.bmp");
			break;
		/////////////////////////////////////////////////////////
		//	Special Candy: Vertical
		/////////////////////////////////////////////////////////
		/*case 10:
			BitmapDir = ".\\Bitmaps\\VPowRedCandy.bmp";
			break;
		case 20:
			BitmapDir = ".\\Bitmaps\\VPowOrangeCandy.bmp";
			break;
		case 30:
			BitmapDir = ".\\Bitmaps\\VPowGreenCandy.bmp";
			break;
		case 40:
			BitmapDir = ".\\Bitmaps\\VPowBlueCandy.bmp";
			break;
		case 50:
			BitmapDir = ".\\Bitmaps\\VPowPurpleCandy.bmp";
			break;*/
		}
	}

	int Candy::GetTopLeftX()
	{
		return x;
	}

	int Candy::GetTopLeftY()
	{
		return y;
	}

	bool Candy::IsMoving()
	{
		if (style == 0) return 0;
		return !(x == dx && y == dy);
	}
}