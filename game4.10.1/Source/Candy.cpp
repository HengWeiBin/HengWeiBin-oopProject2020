#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"

namespace game_framework
{
	Candy::Candy(int id, int x, int y): style(id), x(x), y(y), alive(1)
	{

	}
}