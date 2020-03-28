#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <ddraw.h>
#include <algorithm>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"
#include "GameArea.h"

namespace game_framework
{
	GameArea::GameArea() :x(280), y(35)
	{
		/*candies = new Candy*[MaxHeight];
		for (int i = 0; i < MaxHeight; i++)
		{
			candies[i] = new Candy[MaxWidth];
		}*/

		LoadStage();
	}

	GameArea::~GameArea()
	{
		/*for (int i = 0; i < MaxHeight; i++)
		{
			delete[] candies[i];
		}
		delete[] candies;*/
	}

	void GameArea::LoadBitmap()
	{
		Area.LoadBitmap(".\\Bitmaps\\container.bmp");

		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
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
			for (int i = 0; i < MaxHeight; i++) {
				getline(InputStage, firstline);
				for (int j = 0; j < MaxWidth; j++) {
					switch (firstline[j])
					{
					case '0': map[i][j] = 0; break;		//0 = none, !0 = gameArea
					case '1': map[i][j] = 1; break;		//1 = normalArea
					case '2': map[i][j] = 1; break;		//2 = candy spawning area
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
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (map[i][j] == 1)
					Area.SetTopLeft(j * 50 + x, i * 50 + y);
				Area.ShowBitmap();
			}
		}

		///////////////////////////////////////////
		// Show all candy						///
		///////////////////////////////////////////
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (candies[i][j].GetStyle() != 0)
					candies[i][j].OnShow();
			}
		}

	}

	void GameArea::OnMove()
	{
		for (int i = MaxHeight - 1; i >= 0; i--)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (candies[i][j].GetStyle() != 0 && map[i + 1][j] != 0 && candies[i + 1][j].GetStyle() == 0)
				{
					candies[i][j].SetDestination(candies[i][j].GetTopLeftY() + 50);

					candies[i + 1][j] = candies[i][j];
					candies[i][j].SetStyle(0);
				}
			}
		}

		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				candies[i][j].OnMove();
			}
		}
		if (!IsDropping())
		{
			Sleep(100);
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
		const int MAX_RAND_NUM = 5;										//There are five basic type of candy
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				switch (map[i][j])
				{
				case 1 || 2:
				{
					int id = rand() % MAX_RAND_NUM + 1;					//random type of Candy
					candies[i][j] = Candy(id, j * 50 + x, i * 50 + y);	//Set candy
					break;
				}
				default:
					candies[i][j] = Candy();							
					break;
				}
			}
		}
	}

	void GameArea::ClearCombo()
	{
		vector<Candy*> accumulateCandy;
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (!candies[i][j].GetStyle()) continue;
				accumulateCandy.push_back(&candies[i][j]);
				GetCombo(accumulateCandy, i, j, candies[i][j].GetStyle());
				clearCandies(accumulateCandy);
			}
		}
	}

	void GameArea::GetCombo(vector<Candy*>& accumulateCandy, int i, int j, int checkStyle)
	{
		int currentStyle = candies[i][j].GetStyle();
		candies[i][j].SetStyle(0);
		if (j + 1 < MaxWidth && candies[i][j + 1].GetStyle() == checkStyle)
		{//check to the right
			accumulateCandy.push_back(&candies[i][j + 1]);
			GetCombo(accumulateCandy, i, j + 1, checkStyle);
		}
		if (i + 1 < MaxHeight && candies[i + 1][j].GetStyle() == checkStyle)
		{//Check downward
			accumulateCandy.push_back(&candies[i + 1][j]);
			GetCombo(accumulateCandy, i + 1, j, checkStyle);
		}
		if (j - 1 >= 0 && candies[i][j - 1].GetStyle() == checkStyle)
		{//Check to the left
			accumulateCandy.push_back(&candies[i][j - 1]);
			GetCombo(accumulateCandy, i, j - 1, checkStyle);
		}
		if (i - 1 >= 0 && candies[i - 1][j].GetStyle() == checkStyle)
		{//Check upward
			accumulateCandy.push_back(&candies[i - 1][j]);
			GetCombo(accumulateCandy, i - 1, j, checkStyle);
		}
		candies[i][j].SetStyle(currentStyle);
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
			/*delete if more than 3 candies on a vertical line*/
			if (count(x.begin(), x.end(), accumulateCandy[i]->GetTopLeftX()) >= 3)
				toDelete.push_back(accumulateCandy[i]);
			/*delete if more than 3 candies on a horizontal line*/
			if (count(y.begin(), y.end(), accumulateCandy[i]->GetTopLeftY()) >= 3)
				toDelete.push_back(accumulateCandy[i]);
		}
		for (unsigned int i = 0; i < toDelete.size(); i++)
		{
			//toDelete[i]->SetAlive(false);
			toDelete[i]->SetStyle(0);
		}
		accumulateCandy.clear();
	}

	void GameArea::RemoveNonCont(vector<int>& integers)
	{
		/*sort(integers.begin(), integers.end());
		vector<int> result;
		int count = 1;
		for (unsigned int i = 0; i < integers.size() - 1; i++)
		{
			if (integers[i] + 1 == integers[i + 1]) count++;
			else
			{
				if (count < 3) count = 1;
				else
				{
					for (int j = i - count; j < i; j++)
						result.push_back(integers[j]);
					count = 1;
				}
			}
		}*/
	}

	void GameArea::PutCandy()
	{
		for (int i = 0; i < 16; i++)
		{
			if (!candies[3][i].GetStyle())
			{
				int id = rand() % 5 + 1;
				candies[3][i] = Candy(id, i * 50 + x, 100 + y);
				candies[3][i].LoadBitmap();
			}
		}
	}

	bool GameArea::IsDropping()
	{
		for (int i = 0; i < MaxHeight; i++)
			for (int j = 0; j < MaxWidth; j++)
				if (candies[i][j].IsMoving()) 
					return true;
		return false;
	}
}