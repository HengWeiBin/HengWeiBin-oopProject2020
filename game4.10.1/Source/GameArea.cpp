#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"
#include "GameArea.h"

namespace game_framework
{
	GameArea::GameArea() :x(280), y(35), candies(NULL)
	{	}

	GameArea::~GameArea()
	{
		if (candies != NULL)
			delete[] candies;
	}
}