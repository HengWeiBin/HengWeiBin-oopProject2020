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
	GameArea::GameArea() :x(280), y(35)
	{	}

	GameArea::~GameArea()
	{
		if (candies != NULL)
			delete[] candies;
	}

	void GameArea::LoadBitmap()
	{

	}

	void GameArea::LoadStage()
	{

	}

	void GameArea::OnShow()
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				candies[i][j].OnShow();		//Show all Candies
			}
		}

	}

	void GameArea::OnMove()
	{

	}

	void GameArea::OnLButtonDown(UINT nFlags, CPoint point)
	{

	}

	void GameArea::OnLButtonUp(UINT nFlags, CPoint point)
	{

	}

	void GameArea::OnMouseMove(UINT nFlags, CPoint point)
	{

	}

	void GameArea::InitCandy()
	{
		const int MAX_RAND_NUM = 5;		//There are five type of candy(temporary)
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				switch (map[i][j])
				{
				case 0: 
					candies[i][j] = Candy();
					break;
				case 1: 
					int id = rand() % MAX_RAND_NUM + 1;
					candies[i][j] = Candy(id, j * 50, i * 50);
				}
			}
		}
	}

	void GameArea::CheckCombo()
	{

	}

}