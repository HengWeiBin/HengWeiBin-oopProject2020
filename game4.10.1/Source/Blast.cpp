#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework
{
	static int	redBmp[14] = {
		IDB_RED_NOR1, IDB_RED_NOR2, IDB_RED_NOR3, IDB_RED_NOR4,
		IDB_RED_EXPL1, IDB_RED_EXPL2, IDB_RED_EXPL3, IDB_RED_EXPL4, IDB_RED_EXPL5,
		IDB_RED_EXPL6, IDB_RED_EXPL7, IDB_RED_EXPL8, IDB_RED_EXPL9, IDB_RED_EXPL10 },
			orangeBmp[14] = {
		IDB_ORG_NOR1, IDB_ORG_NOR2, IDB_ORG_NOR3, IDB_ORG_NOR4,
		IDB_ORG_EXPL1, IDB_ORG_EXPL2, IDB_ORG_EXPL3, IDB_ORG_EXPL4, IDB_ORG_EXPL5,
		IDB_ORG_EXPL6, IDB_ORG_EXPL7, IDB_ORG_EXPL8, IDB_ORG_EXPL9, IDB_ORG_EXPL10 },
			yellowBmp[14] = {
		IDB_YEL_NOR1, IDB_YEL_NOR2, IDB_YEL_NOR3, IDB_YEL_NOR4,
		IDB_YEL_EXPL1, IDB_YEL_EXPL2, IDB_YEL_EXPL3, IDB_YEL_EXPL4, IDB_YEL_EXPL5,
		IDB_YEL_EXPL6, IDB_YEL_EXPL7, IDB_YEL_EXPL8, IDB_YEL_EXPL9, IDB_YEL_EXPL10 },
			greenBmp[14] = {
		IDB_GRE_NOR1, IDB_GRE_NOR2, IDB_GRE_NOR3, IDB_GRE_NOR4,
		IDB_GRE_EXPL1, IDB_GRE_EXPL2, IDB_GRE_EXPL3, IDB_GRE_EXPL4, IDB_GRE_EXPL5,
		IDB_GRE_EXPL6, IDB_GRE_EXPL7, IDB_GRE_EXPL8, IDB_GRE_EXPL9, IDB_GRE_EXPL10 },
			blueBmp[14] = {
		IDB_BLU_NOR1, IDB_BLU_NOR2, IDB_BLU_NOR3, IDB_BLU_NOR4,
		IDB_BLU_EXPL1, IDB_BLU_EXPL2, IDB_BLU_EXPL3, IDB_BLU_EXPL4, IDB_BLU_EXPL5,
		IDB_BLU_EXPL6, IDB_BLU_EXPL7, IDB_BLU_EXPL8, IDB_BLU_EXPL9, IDB_BLU_EXPL10 },
			purpleBmp[14] = {
		IDB_PUR_NOR1, IDB_PUR_NOR2, IDB_PUR_NOR3, IDB_PUR_NOR4,
		IDB_PUR_EXPL1, IDB_PUR_EXPL2, IDB_PUR_EXPL3, IDB_PUR_EXPL4, IDB_PUR_EXPL5,
		IDB_PUR_EXPL6, IDB_PUR_EXPL7, IDB_PUR_EXPL8, IDB_PUR_EXPL9, IDB_PUR_EXPL10 },
			normalExplode[10] = {
		IDB_NOR_EXPL1, IDB_NOR_EXPL2, IDB_NOR_EXPL3, IDB_NOR_EXPL4, IDB_NOR_EXPL5,  
		IDB_NOR_EXPL6, IDB_NOR_EXPL7, IDB_NOR_EXPL8, IDB_NOR_EXPL9, IDB_NOR_EXPL10 };

	NormalBlast::NormalBlast() :curShow(0)
	{
	}

	NormalBlast::NormalBlast(int style, int x, int y) :curShow(0)
	{
		LoadBitmap(style);
		SetTopLeft(x, y);
	}

	void NormalBlast::LoadBitmap(int style)
	{
		int *bmpID;
		GetBmpId(bmpID, style);

		for (int i = 0; i < 4; i++)
		{
			candy[i].LoadBitmap(bmpID[i], RGB(255, 255, 255));
		}

		for (int i = 0; i < 10; i++)
		{
			normalBlast[i].LoadBitmap(bmpID[i + 4], RGB(254, 191, 200));
		}
	}

	void NormalBlast::OnMove()
	{
		curShow++;
	}

	void NormalBlast::OnShow()
	{
		normalBlast[curShow].SetTopLeft(x - (normalBlast[curShow].Width() / 2) + 25, y - (normalBlast[curShow].Height() / 2) + 25);
		normalBlast[curShow].ShowBitmap();
		if (curShow < 4)
		{
			candy[curShow].SetTopLeft(x, y);
			candy[curShow].ShowBitmap();
		}
	}

	void NormalBlast::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool NormalBlast::IsLast()
	{
		return (curShow == 9);
	}

	void NormalBlast::GetBmpId(int*& bmpID, int style)
	{
		switch (style)
		{
		case REDCANDY:
			bmpID = redBmp; break;
		case ORANGECANDY:
			bmpID = orangeBmp; break;
		case YELLOWCANDY:
			bmpID = yellowBmp; break;
		case GREENCANDY:
			bmpID = greenBmp; break;
		case BLUECANDY:
			bmpID = blueBmp; break;
		case PURPLECANDY:
			bmpID = purpleBmp; break;
		default:
			GAME_ASSERT(0, "NULL STYLE!");
		}
	}
}