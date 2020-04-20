#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Blast.h"

namespace game_framework
{
	Blast::Blast()
	{

	}

	NormalBlast::NormalBlast() :delay(5), zoom(0.5)
	{

	}

	void NormalBlast::LoadBitmap()
	{
		bmp.LoadBitmap("Bitmaps\\NormalExplode5.bmp");
	}

	void NormalBlast::OnMove()
	{
		zoom += 0.1;
	}

	void NormalBlast::OnShow()
	{
		if(zoom < 1.1)
			bmp.ShowBitmap(zoom);
	}

	void NormalBlast::SetTopLeft(int x, int y)
	{
		bmp.SetTopLeft(x, y);
	}
}