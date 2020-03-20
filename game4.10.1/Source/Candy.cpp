#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), x(x), y(y), alive(1)
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
		string BitmapDir;
		switch (style)
		{
		case 1:
			BitmapDir = ".\\Bitmaps\\RedCandy.bmp";
			break;
		case 2:
			BitmapDir = ".\\Bitmaps\\OrangeCandy.bmp";
			break;
		case 3:
			BitmapDir = ".\\Bitmaps\\GreenCandy.bmp";
			break;
		case 4:
			BitmapDir = ".\\Bitmaps\\BlueCandy.bmp";
			break;
		case 5:
			BitmapDir = ".\\Bitmaps\\PurpleCandy.bmp";
			break;
		/////////////////////////////////////////////////////////
		//	Special Candy: Vertical
		/////////////////////////////////////////////////////////
		case 10:
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
			break;
		}
	}

	void Candy::OnMove()
	{

	}

	void Candy::OnShow()
	{
		if (IsAlive())
		{
			bmp.SetTopLeft(x, y);
			bmp.ShowBitmap();
		}
	}

	void Candy::SetXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	inline bool Candy::IsAlive()
	{
		return alive;
	}

	void Candy::SetAlive(bool alive)
	{
		this->alive = alive;
	}
}