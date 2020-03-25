#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <fstream>
#include <string>
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

		LoadStage();
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
		Area.LoadBitmap(".\\Bitmaps\\container.bmp");

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
		fstream InputStage;
		InputStage.open(".\\Stages\\cnt_stage1.txt");
		if (InputStage) {
			string firstline;
			for (int i = 0; i < 13; i++) {
				getline(InputStage, firstline);
				for (int j = 0; j < 20; j++) {
					switch (firstline[j])
					{
					case '0': map[i][j] = 0; break;
					case '1': map[i][j] = 1; break;
					}
				}
			}
		}
		InputStage.close();
	}

	void GameArea::OnShow()
	{
		///////////////////////////////////////////
		// Show gamearea						///
		///////////////////////////////////////////
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
					Area.SetTopLeft(j * 50 + x, i * 50 + y);
				Area.ShowBitmap();
			}
		}

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
				if (candies[i][j].GetStyle())
					if (i + 1 < 13 && map[i + 1][j] && !candies[i + 1][j].IsAlive())
					{
						int currentX = candies[i][j].GetTopLeftX();
						int currentY = candies[i][j].GetTopLeftY();
						candies[i][j].SetDestination(currentX, candies[i + 1][j].GetTopLeftY());

						candies[i + 1][j] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
				candies[i][j].OnMove();
			}
		}
		if (!IsDropping())
		{
			ClearCombo();
			//PutCandy();
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
					int id = rand() % MAX_RAND_NUM + 1;					//random type of Candy
					candies[i][j] = Candy(id, j * 50 + x, i * 50 + y);	//Set candy
				}
			}
		}
	}

	void GameArea::ClearCombo()
	{
		vector<Candy*> accumulateCandy;
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				accumulateCandy.push_back(&candies[i][j]);
				GetCombo(accumulateCandy, i, j);
				clearCandies(accumulateCandy);
			}
		}
	}

	void GameArea::GetCombo(vector<Candy*>& accumulateCandy, int i, int j)
	{
		candies[i][j].SetAlive(0);
		int currentStyle = accumulateCandy[0]->GetStyle();
		if (j + 1 < 20 && candies[i][j + 1].IsAlive() && candies[i][j + 1].GetStyle() == currentStyle)		//Check to the right	
		{
			accumulateCandy.push_back(&candies[i][j + 1]);
			return GetCombo(accumulateCandy, i, j + 1);
		}
		if (i + 1 < 13 && candies[i + 1][j].IsAlive() && candies[i + 1][j].GetStyle() == currentStyle)		//Check downward
		{
			accumulateCandy.push_back(&candies[i + 1][j]);
			return GetCombo(accumulateCandy, i + 1, j);
		}
		if (j - 1 >= 0 && candies[i][j - 1].IsAlive() && candies[i][j - 1].GetStyle() == currentStyle)		//Check to the left
		{
			accumulateCandy.push_back(&candies[i][j - 1]);
			return GetCombo(accumulateCandy, i, j - 1);
		}
		if (i - 1 >= 0 && candies[i - 1][j].IsAlive() && candies[i - 1][j].GetStyle() == currentStyle)		//Check upward
		{
			accumulateCandy.push_back(&candies[i - 1][j]);
			return GetCombo(accumulateCandy, i - 1, j);
		}
		candies[i][j].SetAlive(1);
	}

	void GameArea::clearCandies(vector<Candy*>&accumulateCandy)
	{
		vector<int> x, y;
		vector<Candy*> toDelete;
		for (unsigned int i = 0; i < accumulateCandy.size(); i++)
		{
			x.push_back(accumulateCandy[i]->GetTopLeftX());
			y.push_back(accumulateCandy[i]->GetTopLeftY());
		}
		for (unsigned int i = 0; i < accumulateCandy.size(); i++)
		{
			if (count(x.begin(), x.end(), accumulateCandy[i]->GetTopLeftX()) >= 3)
				toDelete.push_back(accumulateCandy[i]);
			if (count(y.begin(), y.end(), accumulateCandy[i]->GetTopLeftY()) >= 3)
				toDelete.push_back(accumulateCandy[i]);
		}
		for (unsigned int i = 0; i < toDelete.size(); i++)
			toDelete[i]->SetAlive(0);
		accumulateCandy.clear();
	}

/*	void GameArea::KillCombo(int& accumulateStyle, vector<Candy*>& accumulateCandy, int i, int j)
	{
		int currentStyle = candies[i][j].GetStyle();
		if (currentStyle == 0)
		{
			KillCandy(accumulateCandy, i, j);
		}
		else if (currentStyle == accumulateStyle)
		{
			accumulateCandy.push_back(&candies[i][j]);
		}
		else
		{
			KillCandy(accumulateCandy,i ,j);
			accumulateStyle = currentStyle;
		}
	}

	void GameArea::KillCandy(vector<Candy*>& candies, int i, int j)
	{
		if (candies.size() >= 3)
		{
			for (unsigned int i = 0; i < candies.size(); i++)
				candies[i]->SetAlive(false);
		}
		candies.clear();
		candies.push_back(&(this->candies[i][j]));
	}*/

	void GameArea::PutCandy()
	{
		for (int i = 0; i < 20; i++)
		{
			if (!candies[0][i].IsAlive())
			{
				int id = rand() % 5 + 1;
				candies[0][i] = Candy(id, i * 50 + x, 50 + y);
				candies[0][i].LoadBitmap();
			}
		}
	}

	bool GameArea::IsDropping()
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 20; j++)
				if (candies[i][j].IsMoving()) 
					return true;
		return false;
	}
}