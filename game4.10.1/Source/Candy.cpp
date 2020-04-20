#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	static int	redBmpId[12] = {
		IDB_RED_NOR, IDB_RED_NOR1, IDB_RED_NOR2, IDB_RED_NOR3, IDB_RED_NOR4,
		IDB_RED_NOR_C, IDB_RED_HOR, IDB_RED_HOR_C, IDB_RED_VER, IDB_RED_VER_C, IDB_RED_PAC, IDB_RED_PAC_C },
			orangeBmpId[12] = {
		IDB_ORG_NOR, IDB_ORG_NOR1, IDB_ORG_NOR2, IDB_ORG_NOR3, IDB_ORG_NOR4,
		IDB_ORG_NOR_C, IDB_ORG_HOR, IDB_ORG_HOR_C, IDB_ORG_VER, IDB_ORG_VER_C, IDB_ORG_PAC, IDB_ORG_PAC_C },
			yellowBmpId[12] = {
		IDB_YEL_NOR, IDB_YEL_NOR1, IDB_YEL_NOR2, IDB_YEL_NOR3, IDB_YEL_NOR4,
		IDB_YEL_NOR_C, IDB_YEL_HOR, IDB_YEL_HOR_C, IDB_YEL_VER, IDB_YEL_VER_C, IDB_YEL_PAC, IDB_YEL_PAC_C },
			greenBmpId[12] = {
		IDB_GRE_NOR, IDB_GRE_NOR1, IDB_GRE_NOR2, IDB_GRE_NOR3, IDB_GRE_NOR4,
		IDB_GRE_NOR_C, IDB_GRE_HOR, IDB_GRE_HOR_C, IDB_GRE_VER, IDB_GRE_VER_C, IDB_GRE_PAC, IDB_GRE_PAC_C },
			blueBmpId[12] = {
		IDB_BLU_NOR, IDB_BLU_NOR1, IDB_BLU_NOR2, IDB_BLU_NOR3, IDB_BLU_NOR4,
		IDB_BLU_NOR_C, IDB_BLU_HOR, IDB_BLU_HOR_C, IDB_BLU_VER, IDB_BLU_VER_C, IDB_BLU_PAC, IDB_BLU_PAC_C },
			purpleBmpId[12] = {
		IDB_PUR_NOR, IDB_PUR_NOR1, IDB_PUR_NOR2, IDB_PUR_NOR3, IDB_PUR_NOR4,
		IDB_PUR_NOR_C, IDB_PUR_HOR, IDB_PUR_HOR_C, IDB_PUR_VER, IDB_PUR_VER_C, IDB_PUR_PAC, IDB_PUR_PAC_C },
			audioID[4] = {
		AUDIO_CANDY_LAND1, AUDIO_CANDY_LAND2, AUDIO_CANDY_LAND3, AUDIO_CANDY_LAND4 };

	Candy::Candy(int id, int x, int y)
		: style(id), rawStyle(id), x(x), y(y), dx(x), dy(y), onClick(false), fallingSpeed(0), power(0),
		pushX(0), pushY(0), isBlast(false)
	{
		minify = CAnimation::CAnimation(5);
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
		minify.AddBitmap(bmpID[1], RGB(255, 255, 255));
		minify.AddBitmap(bmpID[2], RGB(255, 255, 255));
		minify.AddBitmap(bmpID[3], RGB(255, 255, 255));
		minify.AddBitmap(bmpID[4], RGB(255, 255, 255));

		normal.LoadBitmap(bmpID[0], RGB(255, 255, 255));
		normalClick.LoadBitmap(bmpID[5], RGB(255, 255, 255));

		horizon.LoadBitmap(bmpID[6], RGB(255, 255, 255));
		horizonClick.LoadBitmap(bmpID[7], RGB(255, 255, 255));

		vertical.LoadBitmap(bmpID[8], RGB(255, 255, 255));
		verticalClick.LoadBitmap(bmpID[9], RGB(255, 255, 255));

		pack.LoadBitmap(bmpID[10], RGB(255, 255, 255));
		packClick.LoadBitmap(bmpID[11], RGB(255, 255, 255));

		super.LoadBitmap(IDB_SUPER, RGB(255, 255, 255));
		superClick.LoadBitmap(IDB_SUPER_C, RGB(255, 255, 255));
	}

	void Candy::OnMove()
	{
		//if (isBlast)
		//{
		//	if (minify.IsFinalBitmap())
		//		SetStyle(0);
		//	else
		//		minify.OnMove();
		//}
		//else
		{
			if (pushX != 0 || pushY != 0)
			{
				int offsetX = pushX > 0 ? 1 : -1, offsetY = pushY > 0 ? 1 : -1;
				if (pushX != 0)
				{
					x += offsetX;
					pushX -= offsetX;
				}
				if (pushY != 0)
				{
					y += offsetY;
					pushY -= offsetY;
				}
				return;
			}

			int fixedSpeed = GAME_CYCLE_TIME * 5 / 16;
			if (y != dy && x != dx)
			{
				y < dy ? y += fixedSpeed : y -= fixedSpeed;
				x < dx ? x += fixedSpeed : x -= fixedSpeed;
			}
			else if (x != dx)
				x > dx ? x -= fixedSpeed : x += fixedSpeed;
			else if (y < dy)
			{
				y += fallingSpeed;
				fallingSpeed += GAME_CYCLE_TIME * 2 / 16;
				if (y > dy)
				{
					y = dy;
					fallingSpeed = 0;
					int sound = rand() % 4;
					CAudio::Instance()->Play(audioID[sound], false);
				}
			}

			y > dy ? y -= fixedSpeed * 2 : y;
		}
	}

	void Candy::OnShow()
	{
		CMovingBitmap *idle, *click;
		GetCurrentShow(&idle, &click);

		//if (!isBlast)
		//{
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
		//}
		//else
		//{
		//	minify.SetTopLeft(x, y);
		//	minify.OnShow();
		//}
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
		case 5:
			*bmpID = redBmpId; break;
		case 6:
			*bmpID = yellowBmpId; break;
		case 3:
			*bmpID = orangeBmpId; break;
		case 4:
			*bmpID = greenBmpId; break;
		case 1:
			*bmpID = blueBmpId; break;
		case 2:
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
		return !(x == dx && y == dy && !isBlast);
	}

	bool Candy::IsClicked()
	{
		return onClick;
	}

	void Candy::Kill()
	{
		isBlast = true;
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
		isBlast = false;
	}

	void Candy::InitClick()
	{
		onClick = false;
	}

	void Candy::Push(int x, int y)
	{
		this->x = x > 0 ? this->x + 20 : x < 0 ? this->x - 20 : this->x;
		this->y = y > 0 ? this->y + 20 : y < 0 ? this->y - 20 : this->y;
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