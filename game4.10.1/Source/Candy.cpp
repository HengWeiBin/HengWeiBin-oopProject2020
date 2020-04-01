#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), x(x), y(y), dx(x), dy(y), onClick(false)
	{}

	Candy::Candy() : style(0)
	{}

	Candy::~Candy()
	{}

	void Candy::LoadBitmap()
	{
		string candyName;
		GetCandyName(candyName);
		bmp.LoadBitmap(".\\Bitmaps\\" + candyName, RGB(255, 255, 255));
		bmpClick.LoadBitmap(".\\Bitmaps\\Clicked" + candyName, RGB(255, 255, 255));
	}

	void Candy::OnMove()
	{
		if (y != dy)
			y > dy ? y -= 10 : y += 10;
		if (x != dx)
			x > dx ? x -= 10 : x += 10;
	}

	void Candy::OnShow()
	{
		if (!onClick)
		{
			bmp.SetTopLeft(x, y);
			bmp.ShowBitmap();
		}
		else
		{
			bmpClick.SetTopLeft(x, y);
			bmpClick.ShowBitmap();
		}
	}

	void Candy::SetDestination(int x, int y)
	{
		dx = x;
		dy = y;
	}

	void Candy::SetDestination(int y)
	{
		dy = y;
	}

	int Candy::GetStyle()
	{
		return style;
	}

	void Candy::SetStyle(int style)
	{
		this->style = style;
	}

	void Candy::GetCandyName(string& BitmapDir)
	{
		switch (style)
		{
		case 1:
			BitmapDir = "RedCandy.bmp";
			break;
		case 2:
			BitmapDir = "OrangeCandy.bmp";
			break;
		case 3:
			BitmapDir = "GreenCandy.bmp";
			break;
		case 4:
			BitmapDir = "BlueCandy.bmp";
			break;
		case 5:
			BitmapDir = "PurpleCandy.bmp";
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
		return dx;
	}

	int Candy::GetTopLeftY()
	{
		return dy;
	}

	int Candy::GetTopLeft(char c)
	{
		switch (c)
		{
		case 'x': return GetTopLeftX();
		case 'y': return GetTopLeftY();
		default: return 0;
		}
	}

	int Candy::GetCurrentX()
	{
		return x;
	}

	int Candy::GetCurrentY()
	{
		return y;
	}

	bool Candy::IsMoving()
	{
		if (style == 0) return 0;
		return !(x == dx && y == dy);
	}

	bool Candy::IsClicked()
	{
		return onClick;
	}

	Candy* Candy::Click()
	{
		onClick = onClick == true ? false : true;
		return this;
	}
}