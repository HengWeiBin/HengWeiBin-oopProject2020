#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework
{
	static int	redBmp[4] = {
		IDB_RED_NOR1, IDB_RED_NOR2, IDB_RED_NOR3, IDB_RED_NOR4 },
			orangeBmp[4] = {
		IDB_ORG_NOR1, IDB_ORG_NOR2, IDB_ORG_NOR3, IDB_ORG_NOR4 },
			yellowBmp[4] = {
		IDB_YEL_NOR1, IDB_YEL_NOR2, IDB_YEL_NOR3, IDB_YEL_NOR4 },
			greenBmp[4] = {
		IDB_GRE_NOR1, IDB_GRE_NOR2, IDB_GRE_NOR3, IDB_GRE_NOR4 },
			blueBmp[4] = {
		IDB_BLU_NOR1, IDB_BLU_NOR2, IDB_BLU_NOR3, IDB_BLU_NOR4 },
			purpleBmp[4] = {
		IDB_PUR_NOR1, IDB_PUR_NOR2, IDB_PUR_NOR3, IDB_PUR_NOR4 };

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

		candy[0].LoadBitmap(bmpID[0], RGB(255, 255, 255));
		candy[1].LoadBitmap(bmpID[1], RGB(255, 255, 255));
		candy[2].LoadBitmap(bmpID[2], RGB(255, 255, 255));
		candy[3].LoadBitmap(bmpID[3], RGB(255, 255, 255));

		normalBlast[0].LoadBitmap("Bitmaps\\NormalExplode1.bmp");
		normalBlast[1].LoadBitmap("Bitmaps\\NormalExplode2.bmp");
		normalBlast[2].LoadBitmap("Bitmaps\\NormalExplode3.bmp");
		normalBlast[3].LoadBitmap("Bitmaps\\NormalExplode4.bmp");
	}

	void NormalBlast::OnMove()
	{
		curShow++;
	}

	void NormalBlast::OnShow()
	{
		normalBlast[curShow].SetTopLeft(x, y);
		normalBlast[curShow].ShowBitmap();
		candy[curShow].SetTopLeft(x, y);
		candy[curShow].ShowBitmap();
	}

	void NormalBlast::SetTopLeft(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool NormalBlast::IsLast()
	{
		return (curShow == 3);
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