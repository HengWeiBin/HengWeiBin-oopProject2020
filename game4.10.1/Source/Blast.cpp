﻿#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework
{
	static int	redBmp[] = {
	IDB_RED_EXPL1, IDB_RED_EXPL2, IDB_RED_EXPL3, IDB_RED_EXPL4, IDB_RED_EXPL5,
	IDB_RED_EXPL6, IDB_RED_EXPL7, IDB_RED_EXPL8, IDB_RED_EXPL9, IDB_RED_EXPL10,
	IDB_RED_SHAT1, IDB_RED_SHAT2, IDB_RED_SHAT3, IDB_RED_SHAT4, IDB_RED_SHAT5,
	IDB_RED_SHAT6, IDB_RED_SHAT7, IDB_RED_SHAT8, IDB_RED_SHAT9, IDB_RED_SHAT10,
	IDB_RED_SHAT11, IDB_RED_SHAT12, IDB_RED_SHAT13, IDB_RED_SHAT14, IDB_RED_SHAT15,
	IDB_RED_VEXPL1, IDB_RED_VEXPL2, IDB_RED_VEXPL3, IDB_RED_VEXPL4, IDB_RED_VEXPL5,
	IDB_RED_VEXPL6, IDB_RED_VEXPL7, IDB_RED_VEXPL8, IDB_RED_VEXPL9, IDB_RED_VEXPL10,
	IDB_RED_VEXPL11, IDB_RED_VEXPL12, IDB_RED_VEXPL13, IDB_RED_VEXPL14, IDB_RED_VEXPL15,
	IDB_RED_HEXPL1, IDB_RED_HEXPL2, IDB_RED_HEXPL3, IDB_RED_HEXPL4, IDB_RED_HEXPL5,
	IDB_RED_HEXPL6, IDB_RED_HEXPL7, IDB_RED_HEXPL8, IDB_RED_HEXPL9, IDB_RED_HEXPL10,
	IDB_RED_HEXPL11, IDB_RED_HEXPL12, IDB_RED_HEXPL13, IDB_RED_HEXPL14, IDB_RED_HEXPL15 },

		orangeBmp[] = {
	IDB_ORG_EXPL1, IDB_ORG_EXPL2, IDB_ORG_EXPL3, IDB_ORG_EXPL4, IDB_ORG_EXPL5,
	IDB_ORG_EXPL6, IDB_ORG_EXPL7, IDB_ORG_EXPL8, IDB_ORG_EXPL9, IDB_ORG_EXPL10,
	IDB_ORG_SHAT1, IDB_ORG_SHAT2, IDB_ORG_SHAT3, IDB_ORG_SHAT4, IDB_ORG_SHAT5,
	IDB_ORG_SHAT6, IDB_ORG_SHAT7, IDB_ORG_SHAT8, IDB_ORG_SHAT9, IDB_ORG_SHAT10,
	IDB_ORG_SHAT11, IDB_ORG_SHAT12, IDB_ORG_SHAT13, IDB_ORG_SHAT14, IDB_ORG_SHAT15,
	IDB_ORG_VEXPL1, IDB_ORG_VEXPL2, IDB_ORG_VEXPL3, IDB_ORG_VEXPL4, IDB_ORG_VEXPL5,
	IDB_ORG_VEXPL6, IDB_ORG_VEXPL7, IDB_ORG_VEXPL8, IDB_ORG_VEXPL9, IDB_ORG_VEXPL10,
	IDB_ORG_VEXPL11, IDB_ORG_VEXPL12, IDB_ORG_VEXPL13, IDB_ORG_VEXPL14, IDB_ORG_VEXPL15,
	IDB_ORG_HEXPL1, IDB_ORG_HEXPL2, IDB_ORG_HEXPL3, IDB_ORG_HEXPL4, IDB_ORG_HEXPL5,
	IDB_ORG_HEXPL6, IDB_ORG_HEXPL7, IDB_ORG_HEXPL8, IDB_ORG_HEXPL9, IDB_ORG_HEXPL10,
	IDB_ORG_HEXPL11, IDB_ORG_HEXPL12, IDB_ORG_HEXPL13, IDB_ORG_HEXPL14, IDB_ORG_HEXPL15 },

		yellowBmp[] = {
	IDB_YEL_EXPL1, IDB_YEL_EXPL2, IDB_YEL_EXPL3, IDB_YEL_EXPL4, IDB_YEL_EXPL5,
	IDB_YEL_EXPL6, IDB_YEL_EXPL7, IDB_YEL_EXPL8, IDB_YEL_EXPL9, IDB_YEL_EXPL10,
	IDB_YEL_SHAT1, IDB_YEL_SHAT2, IDB_YEL_SHAT3, IDB_YEL_SHAT4, IDB_YEL_SHAT5,
	IDB_YEL_SHAT6, IDB_YEL_SHAT7, IDB_YEL_SHAT8, IDB_YEL_SHAT9, IDB_YEL_SHAT10,
	IDB_YEL_SHAT11, IDB_YEL_SHAT12, IDB_YEL_SHAT13, IDB_YEL_SHAT14, IDB_YEL_SHAT15,
	IDB_YEL_VEXPL1, IDB_YEL_VEXPL2, IDB_YEL_VEXPL3, IDB_YEL_VEXPL4, IDB_YEL_VEXPL5,
	IDB_YEL_VEXPL6, IDB_YEL_VEXPL7, IDB_YEL_VEXPL8, IDB_YEL_VEXPL9, IDB_YEL_VEXPL10,
	IDB_YEL_VEXPL11, IDB_YEL_VEXPL12, IDB_YEL_VEXPL13, IDB_YEL_VEXPL14, IDB_YEL_VEXPL15,
	IDB_YEL_HEXPL1, IDB_YEL_HEXPL2, IDB_YEL_HEXPL3, IDB_YEL_HEXPL4, IDB_YEL_HEXPL5,
	IDB_YEL_HEXPL6, IDB_YEL_HEXPL7, IDB_YEL_HEXPL8, IDB_YEL_HEXPL9, IDB_YEL_HEXPL10,
	IDB_YEL_HEXPL11, IDB_YEL_HEXPL12, IDB_YEL_HEXPL13, IDB_YEL_HEXPL14, IDB_YEL_HEXPL15 },

		greenBmp[] = {
	IDB_GRE_EXPL1, IDB_GRE_EXPL2, IDB_GRE_EXPL3, IDB_GRE_EXPL4, IDB_GRE_EXPL5,
	IDB_GRE_EXPL6, IDB_GRE_EXPL7, IDB_GRE_EXPL8, IDB_GRE_EXPL9, IDB_GRE_EXPL10,
	IDB_GRE_SHAT1, IDB_GRE_SHAT2, IDB_GRE_SHAT3, IDB_GRE_SHAT4, IDB_GRE_SHAT5,
	IDB_GRE_SHAT6, IDB_GRE_SHAT7, IDB_GRE_SHAT8, IDB_GRE_SHAT9, IDB_GRE_SHAT10,
	IDB_GRE_SHAT11, IDB_GRE_SHAT12, IDB_GRE_SHAT13, IDB_GRE_SHAT14, IDB_GRE_SHAT15,
	IDB_GRE_VEXPL1, IDB_GRE_VEXPL2, IDB_GRE_VEXPL3, IDB_GRE_VEXPL4, IDB_GRE_VEXPL5,
	IDB_GRE_VEXPL6, IDB_GRE_VEXPL7, IDB_GRE_VEXPL8, IDB_GRE_VEXPL9, IDB_GRE_VEXPL10,
	IDB_GRE_VEXPL11, IDB_GRE_VEXPL12, IDB_GRE_VEXPL13, IDB_GRE_VEXPL14, IDB_GRE_VEXPL15,
	IDB_GRE_HEXPL1, IDB_GRE_HEXPL2, IDB_GRE_HEXPL3, IDB_GRE_HEXPL4, IDB_GRE_HEXPL5,
	IDB_GRE_HEXPL6, IDB_GRE_HEXPL7, IDB_GRE_HEXPL8, IDB_GRE_HEXPL9, IDB_GRE_HEXPL10,
	IDB_GRE_HEXPL11, IDB_GRE_HEXPL12, IDB_GRE_HEXPL13, IDB_GRE_HEXPL14, IDB_GRE_HEXPL15 },

		blueBmp[] = {
	IDB_BLU_EXPL1, IDB_BLU_EXPL2, IDB_BLU_EXPL3, IDB_BLU_EXPL4, IDB_BLU_EXPL5,
	IDB_BLU_EXPL6, IDB_BLU_EXPL7, IDB_BLU_EXPL8, IDB_BLU_EXPL9, IDB_BLU_EXPL10,
	IDB_BLU_SHAT1, IDB_BLU_SHAT2, IDB_BLU_SHAT3, IDB_BLU_SHAT4, IDB_BLU_SHAT5,
	IDB_BLU_SHAT6, IDB_BLU_SHAT7, IDB_BLU_SHAT8, IDB_BLU_SHAT9, IDB_BLU_SHAT10,
	IDB_BLU_SHAT11, IDB_BLU_SHAT12, IDB_BLU_SHAT13, IDB_BLU_SHAT14, IDB_BLU_SHAT15,
	IDB_BLU_VEXPL1, IDB_BLU_VEXPL2, IDB_BLU_VEXPL3, IDB_BLU_VEXPL4, IDB_BLU_VEXPL5,
	IDB_BLU_VEXPL6, IDB_BLU_VEXPL7, IDB_BLU_VEXPL8, IDB_BLU_VEXPL9, IDB_BLU_VEXPL10,
	IDB_BLU_VEXPL11, IDB_BLU_VEXPL12, IDB_BLU_VEXPL13, IDB_BLU_VEXPL14, IDB_BLU_VEXPL15,
	IDB_BLU_HEXPL1, IDB_BLU_HEXPL2, IDB_BLU_HEXPL3, IDB_BLU_HEXPL4, IDB_BLU_HEXPL5,
	IDB_BLU_HEXPL6, IDB_BLU_HEXPL7, IDB_BLU_HEXPL8, IDB_BLU_HEXPL9, IDB_BLU_HEXPL10,
	IDB_BLU_HEXPL11, IDB_BLU_HEXPL12, IDB_BLU_HEXPL13, IDB_BLU_HEXPL14, IDB_BLU_HEXPL15 },

		purpleBmp[] = {
	IDB_PUR_EXPL1, IDB_PUR_EXPL2, IDB_PUR_EXPL3, IDB_PUR_EXPL4, IDB_PUR_EXPL5,
	IDB_PUR_EXPL6, IDB_PUR_EXPL7, IDB_PUR_EXPL8, IDB_PUR_EXPL9, IDB_PUR_EXPL10,
	IDB_PUR_SHAT1, IDB_PUR_SHAT2, IDB_PUR_SHAT3, IDB_PUR_SHAT4, IDB_PUR_SHAT5,
	IDB_PUR_SHAT6, IDB_PUR_SHAT7, IDB_PUR_SHAT8, IDB_PUR_SHAT9, IDB_PUR_SHAT10,
	IDB_PUR_SHAT11, IDB_PUR_SHAT12, IDB_PUR_SHAT13, IDB_PUR_SHAT14, IDB_PUR_SHAT15,
	IDB_PUR_VEXPL1, IDB_PUR_VEXPL2, IDB_PUR_VEXPL3, IDB_PUR_VEXPL4, IDB_PUR_VEXPL5,
	IDB_PUR_VEXPL6, IDB_PUR_VEXPL7, IDB_PUR_VEXPL8, IDB_PUR_VEXPL9, IDB_PUR_VEXPL10,
	IDB_PUR_VEXPL11, IDB_PUR_VEXPL12, IDB_PUR_VEXPL13, IDB_PUR_VEXPL14, IDB_PUR_VEXPL15,
	IDB_PUR_HEXPL1, IDB_PUR_HEXPL2, IDB_PUR_HEXPL3, IDB_PUR_HEXPL4, IDB_PUR_HEXPL5,
	IDB_PUR_HEXPL6, IDB_PUR_HEXPL7, IDB_PUR_HEXPL8, IDB_PUR_HEXPL9, IDB_PUR_HEXPL10,
	IDB_PUR_HEXPL11, IDB_PUR_HEXPL12, IDB_PUR_HEXPL13, IDB_PUR_HEXPL14, IDB_PUR_HEXPL15 };

	void Blast::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void Blast::GetBmpId(int*& bmpID, int style)
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

	NormalBlast::NormalBlast() :curShow(0), totalShow(0)
	{
	}

	NormalBlast::NormalBlast(int style, int x, int y) :curShow(0), size(1.8), totalShow(rand() % 2 + 2)
	{
		LoadBitmap(style);
		SetTopLeft(x, y);

		int direction[] = { -2, -1, 0, 2, 1 };	//direction & speed for shatter
		for (int i = 0; i < totalShow; i++)
		{
			//init shatters' position at center
			shatPosition[i][0] = x;
			shatPosition[i][1] = y;

			shatShow[i] = rand() % 15;				//set shatter start frame
			shift[i][0] = direction[rand() % 5];	//random direction x
			shift[i][1] = direction[rand() % 2 + 3];//random dirention y
			shift[i][2] = rand() % 2;				//set shatter rotation { 1 = clockwise, 0 = counter-clockwise}
		}
	}

	void NormalBlast::LoadBitmap(int style)
	{
		int *bmpID;
		GetBmpId(bmpID, style);

		for (int i = 0; i < 10; i++)
			normalBlast[i].LoadBitmap(bmpID[i], RGB(254, 191, 200));

		for (int i = 0; i < 15; i++)
			shatter[i].LoadBitmap(bmpID[i + 10], RGB(254, 191, 200));
	}

	void NormalBlast::OnMove()
	{
		curShow++;
		if(curShow % 2) size -= 0.1;	//zoom-out shatter

		for (int i = 0; i < totalShow; i++)
		{	//move shatters
			shatPosition[i][0] += shift[i][0];
			shatPosition[i][1] += shift[i][1];

			//rotate shatters
			if (!(curShow % 3))
			{
				if(shift[i][2]) shatShow[i] = (shatShow[i] - 1) < 0 ? (shatShow[i] - 1) + 15 : (shatShow[i] - 1);	//counter-clockwise
				else shatShow[i] = (shatShow[i] + 1) % 15;	//clockwise
			}
		}
	}

	void NormalBlast::OnShow()
	{
		if (curShow < 10)
		{	//show blast circle
			normalBlast[curShow].SetTopLeft(x - (normalBlast[curShow].Width() / 2) + 25, y - (normalBlast[curShow].Height() / 2) + 25);
			normalBlast[curShow].ShowBitmap();
		}

		if (curShow >= 4)
		{	//show shatters
			for (int i = 0; i < totalShow; i++)
			{
				shatter[shatShow[i]].SetTopLeft(shatPosition[i][0], shatPosition[i][1]);
				shatter[shatShow[i]].ShowBitmap(size);
			}
		}
	}

	bool NormalBlast::IsLast()
	{
		return (curShow == 25);
	}

	LineBlast::LineBlast(int style, int x, int y, int power) :powStyle(power), curShow(0)
	{
		LoadBitmap(style);
		SetTopLeft(x, y);
	}

	void LineBlast::LoadBitmap(int style)
	{
		int *bmpID;
		GetBmpId(bmpID, style);

		switch (powStyle)
		{
		case 1:
			for (int i = 0; i < 15; i++)
				horizontal[i].LoadBitmap(bmpID[i + 40], RGB(254, 191, 200));
			break;
		case 2:
			for (int i = 0; i < 15; i++)
				vertical[i].LoadBitmap(bmpID[i + 25], RGB(254, 191, 200));
			break;
		default:
			GAME_ASSERT(0, "Invalid power style");
		}
	}

	void LineBlast::OnMove()
	{
		curShow ++;
	}

	void LineBlast::OnShow()
	{
		if (curShow == 1) CAudio::Instance()->Play(AUDIO_LINE_BLAST, false);
		switch (powStyle)
		{
		case 1:
			horizontal[curShow].SetTopLeft(x - (horizontal[curShow].Width() / 2 - 25), y);
			horizontal[curShow].ShowBitmap();
			break;
		case 2:
			vertical[curShow].SetTopLeft(x, y - (vertical[curShow].Height() / 2 - 25));
			vertical[curShow].ShowBitmap();
			break;
		default:
			GAME_ASSERT(0, "Invalid power style");
		}
	}

	bool LineBlast::IsLast()
	{
		return curShow >= 14;
	}
}