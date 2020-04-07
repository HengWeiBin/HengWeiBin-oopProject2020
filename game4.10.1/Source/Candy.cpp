#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), rawStyle(id), x(x), y(y), dx(x), dy(y), onClick(false), fallingSpeed(1), power(0)
	{}

	Candy::Candy() : style(0), rawStyle(0)
	{}

	Candy::~Candy()
	{}

	void Candy::LoadBitmap()
	{
		int redBmpId[8] = {IDB_RED_NOR, IDB_RED_NOR_C, IDB_RED_HOR, IDB_RED_HOR_C, IDB_RED_VER, IDB_RED_VER_C, IDB_RED_PAC, IDB_RED_PAC_C };
		int orangeBmpId[8] = { IDB_ORG_NOR, IDB_ORG_NOR_C, IDB_ORG_HOR, IDB_ORG_HOR_C, IDB_ORG_VER, IDB_ORG_VER_C, IDB_ORG_PAC, IDB_ORG_PAC_C };
		int greenBmpId[8] = { IDB_GRE_NOR, IDB_GRE_NOR_C, IDB_GRE_HOR, IDB_GRE_HOR_C, IDB_GRE_VER, IDB_GRE_VER_C, IDB_GRE_PAC, IDB_GRE_PAC_C };
		int blueBmpId[8] = { IDB_BLU_NOR, IDB_BLU_NOR_C, IDB_BLU_HOR, IDB_BLU_HOR_C, IDB_BLU_VER, IDB_BLU_VER_C, IDB_BLU_PAC, IDB_BLU_PAC_C };
		int purpleBmpId[8] = { IDB_PUR_NOR, IDB_PUR_NOR_C, IDB_PUR_HOR, IDB_PUR_HOR_C, IDB_PUR_VER, IDB_PUR_VER_C, IDB_PUR_PAC, IDB_PUR_PAC_C };

		for (int i = 0; i < 8; i++)
		{
			red[i].LoadBitmap(redBmpId[i], RGB(255, 255, 255));
			orange[i].LoadBitmap(orangeBmpId[i], RGB(255, 255, 255));
			green[i].LoadBitmap(greenBmpId[i], RGB(255, 255, 255));
			blue[i].LoadBitmap(blueBmpId[i], RGB(255, 255, 255));
			purple[i].LoadBitmap(purpleBmpId[i], RGB(255, 255, 255));
		}
		super.LoadBitmap(".\\Bitmaps\\SuperCandy.bmp", RGB(255, 255, 255));
		superClick.LoadBitmap(".\\Bitmaps\\ClickedSuperCandy.bmp", RGB(255, 255, 255));
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

	void Candy::SetPower(int power)
	{
		this->power = power;
	}

	int Candy::GetPower()
	{
		return power;
	}

	void Candy::Relive()
	{
		style = rawStyle;
	}

	void Candy::GetCurrentShow(CMovingBitmap **idle, CMovingBitmap **click)
	{
		CMovingBitmap *curStyle;
		switch (style)
		{
		case 1:
			curStyle = red;
			break;
		case 2:
			curStyle = orange;
			break;
		case 3:
			curStyle = green;
			break;
		case 4:
			curStyle = blue;
			break;
		case 5:
			curStyle = purple;
			break;
		}

		switch (power)
		{
		case 0:
			*idle = &curStyle[0];
			*click = &curStyle[1];
			break;
		case 1:
			*idle = &curStyle[2];
			*click = &curStyle[3];
			break;
		case 2:
			*idle = &curStyle[4];
			*click = &curStyle[5];
			break;
		case 3:
			*idle = &curStyle[6];
			*click = &curStyle[7];
			break;
		case 4:
			*idle = &super;
			*click = &superClick;
			break;
		}
	}
}