#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	static int	redBmpId[8] = {
		IDB_RED_NOR, IDB_RED_NOR_C, IDB_RED_HOR, IDB_RED_HOR_C, IDB_RED_VER, IDB_RED_VER_C, IDB_RED_PAC, IDB_RED_PAC_C },
				orangeBmpId[8] = {
		IDB_ORG_NOR, IDB_ORG_NOR_C, IDB_ORG_HOR, IDB_ORG_HOR_C, IDB_ORG_VER, IDB_ORG_VER_C, IDB_ORG_PAC, IDB_ORG_PAC_C },
				greenBmpId[8] = {
		IDB_GRE_NOR, IDB_GRE_NOR_C, IDB_GRE_HOR, IDB_GRE_HOR_C, IDB_GRE_VER, IDB_GRE_VER_C, IDB_GRE_PAC, IDB_GRE_PAC_C },
				blueBmpId[8] = {
		IDB_BLU_NOR, IDB_BLU_NOR_C, IDB_BLU_HOR, IDB_BLU_HOR_C, IDB_BLU_VER, IDB_BLU_VER_C, IDB_BLU_PAC, IDB_BLU_PAC_C },
				purpleBmpId[8] = {
		IDB_PUR_NOR, IDB_PUR_NOR_C, IDB_PUR_HOR, IDB_PUR_HOR_C, IDB_PUR_VER, IDB_PUR_VER_C, IDB_PUR_PAC, IDB_PUR_PAC_C };

	Candy::Candy(int id, int x, int y)
		: style(id), rawStyle(id), x(x), y(y), dx(x), dy(y), onClick(false), fallingSpeed(10), power(0)
	{
	}

	Candy::Candy(int x, int y) 
		: style(-1), x(x), y(y), dx(x), dy(y)
	{	}

	Candy::Candy()
		: style(-1)
	{	}

	Candy::~Candy()
	{
	}

	void Candy::LoadBitmap()
	{
		int *bmpID;
		GetBmpId(&bmpID);
		normal.LoadBitmap(bmpID[0], RGB(255, 255, 255));
		normalClick.LoadBitmap(bmpID[1], RGB(255, 255, 255));

		horizon.LoadBitmap(bmpID[2], RGB(255, 255, 255));
		horizonClick.LoadBitmap(bmpID[3], RGB(255, 255, 255));

		vertical.LoadBitmap(bmpID[4], RGB(255, 255, 255));
		verticalClick.LoadBitmap(bmpID[5], RGB(255, 255, 255));

		pack.LoadBitmap(bmpID[6], RGB(255, 255, 255));
		packClick.LoadBitmap(bmpID[7], RGB(255, 255, 255));

		super.LoadBitmap(IDB_SUPER, RGB(255, 255, 255));
		superClick.LoadBitmap(IDB_SUPER_C, RGB(255, 255, 255));
	}

	void Candy::OnMove()
	{
		if (y != dy && x != dx)
		{
			y < dy ? y += 5 : y -= 5;
			x < dx ? x += 5 : x -= 5;
		}
		else if (x != dx)
			x > dx ? x -= 5 : x += 5;
		else if (y < dy)
		{
			y += fallingSpeed;
			fallingSpeed += 1;
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

	void Candy::GetBmpId(int** bmpID)
	{
		switch (style)
		{
		case 1:
			*bmpID = redBmpId; break;
		case 2:
			*bmpID = orangeBmpId; break;
		case 3:
			*bmpID = greenBmpId; break;
		case 4:
			*bmpID = blueBmpId; break;
		case 5:
			*bmpID = purpleBmpId; break;
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
		if (style <= 0) return 0;
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

	void Candy::InitClick()
	{
		onClick = false;
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
		case 4:
			*idle = &super;
			*click = &superClick;
			break;
		}
	}
}