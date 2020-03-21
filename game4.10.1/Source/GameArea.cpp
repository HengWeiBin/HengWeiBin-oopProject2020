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
	{
		candies = new Candy*[13];
		for (int i = 0; i < 13; i++)
		{
			candies[i] = new Candy[20];
		}

		////////////////////////////////////////////////////////////
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i == 0 || i == 12 || j == 0 || j == 19)		//for temporary use
					map[i][j] = 0;
				else
					map[i][j] = 1;
			}
		}
		////////////////////////////////////////////////////////////
	}

	GameArea::~GameArea()
	{
		for (int i = 0; i < 13; i++)
		{
			delete[] candies[i];
		}
		delete[] candies;
	}

	void GameArea::LoadBitmap()
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (candies[i][j].GetStyle() != 0)
					candies[i][j].LoadBitmap();
			}
		}
	}

	void GameArea::LoadStage()
	{

	}

	void GameArea::OnShow()
	{
		///////////////////////////////////////////
		// Show gamearea						///
		///////////////////////////////////////////
		/*
		
		
		
		
		
		
		
		
		
		*/
		///////////////////////////////////////////
		// Show all candy						///
		///////////////////////////////////////////
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (candies[i][j].GetStyle() != 0)
					candies[i][j].OnShow();
			}
		}

	}

	void GameArea::OnMove()
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (candies[i][j].GetStyle() != 0)
					candies[i][j].OnMove();
			}
		}
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
		const int MAX_RAND_NUM = 5;		//There are five basic type of candy
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
					candies[i][j] = Candy(id, j * 50 + x, i * 50 + y);
				}
			}
		}
	}


	void GameArea::CheckCombo()
	{
		int accumulateStyle = 0;
		vector<Candy*> accumulateCandy;
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				KillCombo(accumulateStyle, accumulateCandy, i, j);
			}
		}
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				KillCombo(accumulateStyle, accumulateCandy, j, i);
			}
		}
	}

	void GameArea::KillCombo(int& accumulateStyle, vector<Candy*>& accumulateCandy, int i, int j)
	{
		int currentStyle = candies[i][j].GetStyle();
		if (currentStyle == 0)
		{
			KillCandy(accumulateCandy);
			return;
		}
		if (currentStyle == accumulateStyle)
		{
			accumulateCandy.push_back(&candies[i][j]);
		}
		else
		{
			KillCandy(accumulateCandy);
			accumulateStyle = currentStyle;
		}
	}

	void GameArea::KillCandy(vector<Candy*>& candies)
	{
		if (candies.size() >= 3)
		{
			//for (int i = 0; i < candies.size(); i++)
			//	candies[i]->SetAlive(0);
		}
		candies.clear();
	}
}