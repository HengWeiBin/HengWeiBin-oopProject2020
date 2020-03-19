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
		case 2:
			BitmapDir = ".\\Bitmaps\\OrangeCandy.bmp";
		case 3:
			BitmapDir = ".\\Bitmaps\\GreenCandy.bmp";
		case 4:
			BitmapDir = ".\\Bitmaps\\BlueCandy.bmp";
		case 5:
			BitmapDir = ".\\Bitmaps\\PurpleCandy.bmp";
		}
	}

	void Candy::OnMove()
	{

	}

	void Candy::OnShow()
	{

	}

	void Candy::SetXY(int, int)
	{

	}

	bool Candy::IsAlive()
	{

	}

	void Candy::SetAlive(bool)
	{

	}
}