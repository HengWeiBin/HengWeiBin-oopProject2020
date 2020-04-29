#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework
{
	static int	redBmp[29] = {
		IDB_RED_NOR1, IDB_RED_NOR2, IDB_RED_NOR3, IDB_RED_NOR4,
		IDB_RED_EXPL1, IDB_RED_EXPL2, IDB_RED_EXPL3, IDB_RED_EXPL4, IDB_RED_EXPL5,
		IDB_RED_EXPL6, IDB_RED_EXPL7, IDB_RED_EXPL8, IDB_RED_EXPL9, IDB_RED_EXPL10,
		IDB_RED_SHAT1, IDB_RED_SHAT2, IDB_RED_SHAT3, IDB_RED_SHAT4, IDB_RED_SHAT5,
		IDB_RED_SHAT6, IDB_RED_SHAT7, IDB_RED_SHAT8, IDB_RED_SHAT9, IDB_RED_SHAT10,
		IDB_RED_SHAT11, IDB_RED_SHAT12, IDB_RED_SHAT13, IDB_RED_SHAT14, IDB_RED_SHAT15 },

			orangeBmp[29] = {
		IDB_ORG_NOR1, IDB_ORG_NOR2, IDB_ORG_NOR3, IDB_ORG_NOR4,
		IDB_ORG_EXPL1, IDB_ORG_EXPL2, IDB_ORG_EXPL3, IDB_ORG_EXPL4, IDB_ORG_EXPL5,
		IDB_ORG_EXPL6, IDB_ORG_EXPL7, IDB_ORG_EXPL8, IDB_ORG_EXPL9, IDB_ORG_EXPL10,
		IDB_ORG_SHAT1, IDB_ORG_SHAT2, IDB_ORG_SHAT3, IDB_ORG_SHAT4, IDB_ORG_SHAT5,
		IDB_ORG_SHAT6, IDB_ORG_SHAT7, IDB_ORG_SHAT8, IDB_ORG_SHAT9, IDB_ORG_SHAT10,
		IDB_ORG_SHAT11, IDB_ORG_SHAT12, IDB_ORG_SHAT13, IDB_ORG_SHAT14, IDB_ORG_SHAT15 },

			yellowBmp[29] = {
		IDB_YEL_NOR1, IDB_YEL_NOR2, IDB_YEL_NOR3, IDB_YEL_NOR4,
		IDB_YEL_EXPL1, IDB_YEL_EXPL2, IDB_YEL_EXPL3, IDB_YEL_EXPL4, IDB_YEL_EXPL5,
		IDB_YEL_EXPL6, IDB_YEL_EXPL7, IDB_YEL_EXPL8, IDB_YEL_EXPL9, IDB_YEL_EXPL10,
		IDB_YEL_SHAT1, IDB_YEL_SHAT2, IDB_YEL_SHAT3, IDB_YEL_SHAT4, IDB_YEL_SHAT5,
		IDB_YEL_SHAT6, IDB_YEL_SHAT7, IDB_YEL_SHAT8, IDB_YEL_SHAT9, IDB_YEL_SHAT10,
		IDB_YEL_SHAT11, IDB_YEL_SHAT12, IDB_YEL_SHAT13, IDB_YEL_SHAT14, IDB_YEL_SHAT15 },

			greenBmp[29] = {
		IDB_GRE_NOR1, IDB_GRE_NOR2, IDB_GRE_NOR3, IDB_GRE_NOR4,
		IDB_GRE_EXPL1, IDB_GRE_EXPL2, IDB_GRE_EXPL3, IDB_GRE_EXPL4, IDB_GRE_EXPL5,
		IDB_GRE_EXPL6, IDB_GRE_EXPL7, IDB_GRE_EXPL8, IDB_GRE_EXPL9, IDB_GRE_EXPL10,
		IDB_GRE_SHAT1, IDB_GRE_SHAT2, IDB_GRE_SHAT3, IDB_GRE_SHAT4, IDB_GRE_SHAT5,
		IDB_GRE_SHAT6, IDB_GRE_SHAT7, IDB_GRE_SHAT8, IDB_GRE_SHAT9, IDB_GRE_SHAT10,
		IDB_GRE_SHAT11, IDB_GRE_SHAT12, IDB_GRE_SHAT13, IDB_GRE_SHAT14, IDB_GRE_SHAT15 },

			blueBmp[29] = {
		IDB_BLU_NOR1, IDB_BLU_NOR2, IDB_BLU_NOR3, IDB_BLU_NOR4,
		IDB_BLU_EXPL1, IDB_BLU_EXPL2, IDB_BLU_EXPL3, IDB_BLU_EXPL4, IDB_BLU_EXPL5,
		IDB_BLU_EXPL6, IDB_BLU_EXPL7, IDB_BLU_EXPL8, IDB_BLU_EXPL9, IDB_BLU_EXPL10,
		IDB_BLU_SHAT1, IDB_BLU_SHAT2, IDB_BLU_SHAT3, IDB_BLU_SHAT4, IDB_BLU_SHAT5,
		IDB_BLU_SHAT6, IDB_BLU_SHAT7, IDB_BLU_SHAT8, IDB_BLU_SHAT9, IDB_BLU_SHAT10,
		IDB_BLU_SHAT11, IDB_BLU_SHAT12, IDB_BLU_SHAT13, IDB_BLU_SHAT14, IDB_BLU_SHAT15 },

			purpleBmp[29] = {
		IDB_PUR_NOR1, IDB_PUR_NOR2, IDB_PUR_NOR3, IDB_PUR_NOR4,
		IDB_PUR_EXPL1, IDB_PUR_EXPL2, IDB_PUR_EXPL3, IDB_PUR_EXPL4, IDB_PUR_EXPL5,
		IDB_PUR_EXPL6, IDB_PUR_EXPL7, IDB_PUR_EXPL8, IDB_PUR_EXPL9, IDB_PUR_EXPL10,
		IDB_PUR_SHAT1, IDB_PUR_SHAT2, IDB_PUR_SHAT3, IDB_PUR_SHAT4, IDB_PUR_SHAT5,
		IDB_PUR_SHAT6, IDB_PUR_SHAT7, IDB_PUR_SHAT8, IDB_PUR_SHAT9, IDB_PUR_SHAT10,
		IDB_PUR_SHAT11, IDB_PUR_SHAT12, IDB_PUR_SHAT13, IDB_PUR_SHAT14, IDB_PUR_SHAT15 };

	NormalBlast::NormalBlast() :curShow(0)
	{
	}

	NormalBlast::NormalBlast(int style, int x, int y) :curShow(0), size(2.0)
	{
		LoadBitmap(style);
		SetTopLeft(x, y);

		int direction[] = { -2, 0, 2 };
		for (int i = 0; i < 3; i++)
		{
			shatPosition[i][0] = x;
			shatPosition[i][1] = y;
			shatShow[i] = rand() % 15;
			shift[i][0] = direction[rand() % 3];
			shift[i][1] = direction[rand() % 3];
		}
	}

	void NormalBlast::LoadBitmap(int style)
	{
		int *bmpID;
		GetBmpId(bmpID, style);

		for (int i = 0; i < 4; i++)
			candy[i].LoadBitmap(bmpID[i], RGB(255, 255, 255));

		for (int i = 0; i < 10; i++)
			normalBlast[i].LoadBitmap(bmpID[i + 4], RGB(254, 191, 200));

		for (int i = 0; i < 15; i++)
			shatter[i].LoadBitmap(bmpID[i + 14], RGB(0, 0, 0));
	}

	void NormalBlast::OnMove()
	{
		curShow++;
		size -= 0.1;

		for (int i = 0; i < 3; i++)
		{
			shatPosition[i][0] += shift[i][0];
			shatPosition[i][1] += shift[i][1];
			if (curShow % 2) shatShow[i] = (shatShow[i] + 1) % 15;
		}
	}

	void NormalBlast::OnShow()
	{
		if (curShow < 10)
		{
			normalBlast[curShow].SetTopLeft(x - (normalBlast[curShow].Width() / 2) + 25, y - (normalBlast[curShow].Height() / 2) + 25);
			normalBlast[curShow].ShowBitmap();
		}

		if (curShow < 4)
		{
			candy[curShow].SetTopLeft(x, y);
			candy[curShow].ShowBitmap();
		}

		if (curShow >= 4)
		{
			for (int i = 0; i < 3; i++)
			{
				shatter[shatShow[i]].SetTopLeft(shatPosition[i][0], shatPosition[i][1]);
				shatter[shatShow[i]].ShowBitmap(size);
			}
		}
	}

	void NormalBlast::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool NormalBlast::IsLast()
	{
		return (curShow == 14);
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