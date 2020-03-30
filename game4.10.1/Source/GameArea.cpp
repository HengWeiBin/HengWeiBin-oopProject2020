#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <ddraw.h>
#include <algorithm>
#include <set>
#include "audio.h"
#include "gamelib.h"
#include "Candy.h"
#include "GameArea.h"

namespace game_framework
{
	GameArea::GameArea() :x(280), y(35), MAX_RAND_NUM(5), totalClicked(0)
	{
		score.SetInteger(0);
		LoadStage();
	}

	GameArea::~GameArea()
	{	}

	void GameArea::LoadBitmap()
	{
		Area.LoadBitmap(".\\Bitmaps\\container.bmp");

		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (candies[i][j].GetStyle())
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
					case '2': map[i][j] = 2; break;		//2 = candy spawning area
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
				if (map[i][j])
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
		DropCandy();							//drop if candy hvnt touch the ground/other candy
		PutCandy();								//put candy at apawning area if it's empty

		for (int i = 0; i < MaxHeight; i++)
			for (int j = 0; j < MaxWidth; j++)
				candies[i][j].OnMove();

		if (!IsDropping())
		{
			ClearCombo();
			Sleep(100);
		}
			
	}

	void GameArea::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (!IsDropping())
		{
			int column = (point.x - 280) / 50;
			int row = (point.y - 35) / 50;
			totalClicked += candies[row][column].Click();
		}
	}

	void GameArea::OnLButtonUp(UINT nFlags, CPoint point)
	{

	}

	void GameArea::OnMouseMove(UINT nFlags, CPoint point)
	{

	}

	void GameArea::InitCandy()
	{									//There are five basic type of candy
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

	void GameArea::DropCandy()
	{
		for (int i = MaxHeight - 1; i >= 0; i--)
			for (int j = 0; j < MaxWidth; j++)
				if (candies[i][j].GetStyle() != 0 && map[i + 1][j] != 0 && candies[i + 1][j].GetStyle() == 0)
				{
					candies[i][j].SetDestination(candies[i][j].GetTopLeftY() + 50);

					candies[i + 1][j] = candies[i][j];
					candies[i][j].SetStyle(0);
				}
	}

	void GameArea::ClearCombo()
	{
		set<Candy*> accumulateCandy;
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (!candies[i][j].GetStyle()) continue;
				accumulateCandy.insert(&candies[i][j]);						//put the first candy into set
				GetCandies(accumulateCandy, i, j, candies[i][j].GetStyle());//collect all similar candies that follow-up with first
				DeleteCombo(accumulateCandy);								//delete all combo
			}
		}
	}

	void GameArea::GetCandies(set<Candy*>& accumulateCandy, int i, int j, int checkStyle)
	{	//Recursive condition: there is(are) same candy(ies) nearby
		int currentStyle = candies[i][j].GetStyle();
		candies[i][j].SetStyle(0);
		if (j + 1 < MaxWidth && candies[i][j + 1].GetStyle() == checkStyle)
		{//check to the right
			accumulateCandy.insert(&candies[i][j + 1]);
			GetCandies(accumulateCandy, i, j + 1, checkStyle);
		}
		if (i + 1 < MaxHeight && candies[i + 1][j].GetStyle() == checkStyle)
		{//Check downward
			accumulateCandy.insert(&candies[i + 1][j]);
			GetCandies(accumulateCandy, i + 1, j, checkStyle);
		}
		if (j - 1 >= 0 && candies[i][j - 1].GetStyle() == checkStyle)
		{//Check to the left
			accumulateCandy.insert(&candies[i][j - 1]);
			GetCandies(accumulateCandy, i, j - 1, checkStyle);
		}
		if (i - 1 >= 0 && candies[i - 1][j].GetStyle() == checkStyle)
		{//Check upward
			accumulateCandy.insert(&candies[i - 1][j]);
			GetCandies(accumulateCandy, i - 1, j, checkStyle);
		}
		candies[i][j].SetStyle(currentStyle);
	}

	//Functions CompareX() and CompareY() are used by stable_sort
	bool CompareX(Candy* candy1, Candy* candy2)					//
	{															//
		return (candy1->GetTopLeftX() < candy2->GetTopLeftX());	//
	}															//
																//
	bool CompareY(Candy* candy1, Candy* candy2)					//
	{															//
		return candy1->GetTopLeftY() < candy2->GetTopLeftY();	//
	}															//
	//==========================================================//

	void GameArea::DeleteCombo(set<Candy*>&accumulateCandy)
	{
		if (accumulateCandy.size() < 3)
		{	//Pass
			accumulateCandy.clear();
			return;
		}

		vector<int> x, y;
		vector<Candy*> toDelete;
		for (auto i = accumulateCandy.begin(); i != accumulateCandy.end(); i++)
		{
			x.push_back((*i)->GetTopLeftX());
			y.push_back((*i)->GetTopLeftY());
		}
		for (auto i = accumulateCandy.begin(); i != accumulateCandy.end(); i++)
		{	/*delete if more than 3 candies on a vertical line*/
			if (count(x.begin(), x.end(), (*i)->GetTopLeftX()) >= 3)
				toDelete.push_back(*i);
		}
		RemoveContinuous(toDelete, 'y', &CompareY);
		for (auto i = accumulateCandy.begin(); i != accumulateCandy.end(); i++)
		{	/*delete if more than 3 candies on a horizontal line*/
			if (count(y.begin(), y.end(), (*i)->GetTopLeftY()) >= 3)
				toDelete.push_back(*i);
		}
		RemoveContinuous(toDelete, 'x', &CompareX);
		accumulateCandy.clear();
	}

	void GameArea::RemoveContinuous(vector<Candy*>& toDelete, char c, bool(*Compare)(Candy*, Candy*))
	{
		if (!toDelete.size()) return; //pass

		vector<Candy*> line;
		char check = c == 'x' ? 'y' : 'x';
		while(1)
		{	//collect candies on a same line
			int currentLine = toDelete[0]->GetTopLeft(check);
			for (auto i = toDelete.begin(); i != toDelete.end();)
			{
				if ((*i)->GetTopLeft(check) == currentLine)
				{
					line.push_back(*i);
					i = toDelete.erase(i);
				}
				else i++;
			}

			stable_sort(line.begin(), line.end(), Compare);	//When their x/y are same, sort according to y/x
			int count = 1;
			for (unsigned int i = 0; i < line.size() - 1; i++)
			{
				if (line[i]->GetTopLeft(c) + 50 == line[i + 1]->GetTopLeft(c)) count++;	//If next candy is follow-up with current, keep counting
				else if (count < 3) count = 1;											//else, if count >= 3 -> combo, or pass
				else
				{
					for (unsigned int j = i - count; j < i; j++)
					{
						line[j]->SetStyle(0);
						score.Add(600);
					}
					count = 1;
				}
			}
			if (count >= 3)
				for (unsigned int j = line.size() - count; j < line.size(); j++)
				{
					line[j]->SetStyle(0);
					score.Add(600);
				}
			line.clear();
			if (toDelete.size() < 3) break;	//break if there is not enough candies to form a combo
		}
		toDelete.clear();
	}

	void GameArea::PutCandy()
	{
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (map[i][j] == 2 && candies[i][j].GetStyle() == 0)
				{
					int id = rand() % MAX_RAND_NUM + 1;					//random type of Candy
					int offset = candies[i + 1][j].GetCurrentY();
					candies[i][j] = Candy(id, j * 50 + x, offset - 50);
					candies[i][j].LoadBitmap();
					candies[i][j].SetDestination(i * 50 + y);
				}
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

	void GameArea::ExchangeCandy()
	{
		if (totalClicked == 2)
		{
			Candy* firstCandy = NULL;
			for (int i = 0; i < MaxHeight; i++)
				for (int j = 0; j < MaxWidth; j++)
					if (candies[i][j].IsClicked() && firstCandy == NULL)
						firstCandy = &candies[i][j];
					else if (candies[i][j].IsClicked() && firstCandy != NULL && IsNeighbour(*firstCandy, candies[i][j]))
					{
						firstCandy->SetDestination(candies[i][j].GetTopLeftX(), candies[i][j].GetTopLeftY());
						candies[i][j].SetDestination(firstCandy->GetTopLeftX(), firstCandy->GetTopLeftY());
						totalClicked += candies[i][j].Click();
						totalClicked += firstCandy->Click();
						return;
					}
		}
	}

	bool GameArea::IsNeighbour(Candy &a, Candy &b)
	{
		return (fabs(a.GetTopLeftX() - b.GetTopLeftX()) == 50 || fabs(a.GetTopLeftY() - b.GetTopLeftY()) == 50);
	}
}