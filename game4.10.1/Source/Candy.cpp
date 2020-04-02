#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), x(x), y(y), dx(x), dy(y), onClick(false), fallingSpeed(1), power(0)
	{}

	Candy::Candy() : style(0)
	{}

	Candy::~Candy()
	{}

	void Candy::LoadBitmap()
	{
		string candyName;
		const string dir = ".\\Bitmaps\\", click = "Clicked";
		GetCandyName(candyName);
		normal.LoadBitmap(dir + candyName, RGB(255, 255, 255));
		normalClick.LoadBitmap(dir + click + candyName, RGB(255, 255, 255));

		horizon.LoadBitmap(dir + "P1" + candyName, RGB(255, 255, 255));
		horizonClick.LoadBitmap(dir + click + "P1" + candyName, RGB(255, 255, 255));

		vertical.LoadBitmap(dir + "P2" + candyName, RGB(255, 255, 255));
		verticalClick.LoadBitmap(dir + click + "P2" + candyName, RGB(255, 255, 255));

		pack.LoadBitmap(dir + "P3" + candyName, RGB(255, 255, 255));
		packClick.LoadBitmap(dir + click + "P3" + candyName, RGB(255, 255, 255));
	}

	void Candy::OnMove()
	{
		if (y != dy && x != dx)
		{
			y < dy ? y += 10 : y -= 10;
			x < dx ? x += 10 : x -= 10;
		}
		if (x != dx)
			x > dx ? x -= 10 : x += 10;
		if (y < dy)
		{
			y += fallingSpeed;
			fallingSpeed += 4;
			if (y > dy)
			{
				y = dy;
				fallingSpeed = 10;
			}
		}

		y > dy ? y -= 10 : y;
	}

	void Candy::OnShow()
	{
		CMovingBitmap *idle, *click;
		GetCurrentShow(&idle, &click);

		if (!onClick)
		{
			idle->SetTopLeft(x, y);
			idle->ShowBitmap();
		}
		else
		{
			click->SetTopLeft(x, y);
			click->ShowBitmap();
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
		case 6:
			BitmapDir = "SuperCandy.bmp";
			break;
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

	void Candy::GetCurrentShow(CMovingBitmap **idle, CMovingBitmap **click)
	{
		switch (power)
		{
		case 0:
			*idle = &normal;
			*click = &normalClick;
			break;
		case 1:
			*idle = &horizon;
			*click = &horizonClick;
			break;
		case 2:
			*idle = &vertical;
			*click = &verticalClick;
			break;
		case 3:
			*idle = &pack;
			*click = &packClick;
			break;
		}
	}
}