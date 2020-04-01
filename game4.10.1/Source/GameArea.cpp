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
	GameArea::GameArea() :x(280), y(35), MAX_RAND_NUM(2)
	{
		score.SetInteger(0);
		LoadStage();
	}

	GameArea::~GameArea()
	{	}

	void GameArea::LoadBitmap()
	{
		Area.LoadBitmap(".\\Bitmaps\\container.bmp");
		score_board.LoadBitmap("Bitmaps\\score_board.bmp", RGB(0, 0, 0));

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
		// Show score    						///
		///////////////////////////////////////////
		score_board.SetTopLeft((SIZE_X - 1211) / 2, ((SIZE_Y - 420) / 2));
		score_board.ShowBitmap();
		score.SetTopLeft((((score_board.Left() + 140) - score.Size()) / 2), score_board.Top() + 120);
		score.ShowBitmap();

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
			int amountCleared = ClearCombo();
			if (amountCleared && clickedCandies.size() == 2)
				clickedCandies.clear();
			else if (!amountCleared && clickedCandies.size() == 2)
			{
				SwapCandy();
				clickedCandies.clear();
			}
			Sleep(100);
		}
			
	}

	void GameArea::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (!IsDropping())
		{
			int column = (point.x - 280) / 50;
			int row = (point.y - 35) / 50;
			Candy* clickedCandy = candies[row][column].Click();
			auto getCandyItr = find(clickedCandies.begin(), clickedCandies.end(), clickedCandy);

			if (getCandyItr == clickedCandies.end())
				clickedCandies.push_back(clickedCandy);
			else clickedCandies.erase(getCandyItr);

			if (clickedCandies.size() == 2)
			{
				if (IsNeighbour(*clickedCandies[0], *clickedCandies[1]))
					SwapCandy();
				else clickedCandies.clear();
			}
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
				case 1:
				{
					int id = rand() % MAX_RAND_NUM + 1;					//random type of Candy
					candies[i][j] = Candy(id, j * 50 + x, i * 50 + y);	//Set candy
					break;
				}
				case 2:
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
		for (int i = 0; i < MaxHeight; i++)
			for (int j = 0; j < MaxWidth; j++)
				if (map[i + 1][j] != 0 && candies[i][j].GetStyle())
				{
					if (!candies[i + 1][j].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
					/*else if (map[i + 1][j - 1] && !candies[i][j - 1].GetStyle() && !candies[i + 1][j - 1].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftX() - 50, candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j - 1] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
					else if (map[i + 1][j + 1]&& !candies[i][j + 1].GetStyle() && !candies[i + 1][j + 1].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftX() + 50, candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j + 1] = candies[i][j];
						candies[i][j].SetStyle(0);
					}*/
				}
	}

	int GameArea::ClearCombo()
	{
		set<Candy*> accumulateCandy;
		int conboDeleted = 0;
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (!candies[i][j].GetStyle()) continue;
				accumulateCandy.insert(&candies[i][j]);						//put the first candy into set
				GetCandies(accumulateCandy, i, j, candies[i][j].GetStyle());//collect all similar candies that follow-up with first
				conboDeleted += DeleteCombo(accumulateCandy);				//delete all combo
			}
		}
		return conboDeleted;
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

	int GameArea::DeleteCombo(set<Candy*>&accumulateCandy)
	{
		if (accumulateCandy.size() < 3)
		{	//Pass
			accumulateCandy.clear();
			return 0;
		}

		vector<int> x, y;
		vector<Candy*> toDelete;
		int conboDeleted = 0;
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
		conboDeleted += RemoveContinuous(toDelete, 'y', &CompareY);
		for (auto i = accumulateCandy.begin(); i != accumulateCandy.end(); i++)
		{	/*delete if more than 3 candies on a horizontal line*/
			if (count(y.begin(), y.end(), (*i)->GetTopLeftY()) >= 3)
				toDelete.push_back(*i);
		}
		conboDeleted += RemoveContinuous(toDelete, 'x', &CompareX);
		accumulateCandy.clear();
		return conboDeleted;
	}

	int GameArea::RemoveContinuous(vector<Candy*>& toDelete, char c, bool(*Compare)(Candy*, Candy*))
	{
		if (!toDelete.size()) return 0; //pass

		vector<Candy*> line;
		char check = c == 'x' ? 'y' : 'x';
		int conboDeleted = 0;
		while(1)
		{	
			GetLine(line, toDelete, check);					//collect candies on a same line
			stable_sort(line.begin(), line.end(), Compare);	//When their x/y are same, sort according to y/x

			int count = 1;
			for (unsigned int i = 0; i < line.size() - 1; i++)
			{
				if (line[i]->GetTopLeft(c) + 50 == line[i + 1]->GetTopLeft(c)) count++;	//If next candy is follow-up with current, keep counting
				else if (count < 3) count = 1;											//else, if count >= 3 -> combo, or pass
				else
				{
					RemoveContinuous(line, i - count, i);
					count = 1;
					conboDeleted++;
				}
			}
			if (count >= 3)
			{
				RemoveContinuous(line, line.size() - count, line.size());
				conboDeleted++;
			}
			line.clear();
			if (toDelete.size() < 3) break;	//break if there is not enough candies to form a combo
		}
		toDelete.clear();
		return conboDeleted;
	}

	void GameArea::RemoveContinuous(vector<Candy*>& line, unsigned offset, unsigned lineSize)
	{
		for (unsigned int j = offset; j < lineSize; j++)
		{
			line[j]->SetStyle(0);
			score.Add(60);
		}
	}

	void GameArea::GetLine(vector<Candy*>& line, vector<Candy*>& toDelete, char check)
	{
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
	}

	void GameArea::PutCandy()
	{
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (map[i][j] == 2 && !candies[i][j].GetStyle())
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

	void GameArea::SwapCandy()
	{
		clickedCandies[0]->SetDestination(clickedCandies[1]->GetCurrentX(), clickedCandies[1]->GetCurrentY());
		clickedCandies[1]->SetDestination(clickedCandies[0]->GetCurrentX(), clickedCandies[0]->GetCurrentY());

		Candy temp = *clickedCandies[0];
		*clickedCandies[0] = *clickedCandies[1];
		*clickedCandies[1] = temp;
	}

	bool GameArea::IsNeighbour(Candy &a, Candy &b)
	{
		bool vertiNeighbour = fabs(a.GetTopLeftX() - b.GetTopLeftX()) == 50 && a.GetTopLeftY() == b.GetTopLeftY();
		bool horztNeighbour = fabs(a.GetTopLeftY() - b.GetTopLeftY()) == 50 && a.GetTopLeftX() == b.GetTopLeftX();
		return vertiNeighbour || horztNeighbour;
	}
}