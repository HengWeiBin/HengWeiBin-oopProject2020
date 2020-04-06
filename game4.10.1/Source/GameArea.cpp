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
		score = new CInteger(1);
		score->SetInteger(0);
		LoadStage();
	}

	GameArea::~GameArea()
	{
		delete score;
	}

	void GameArea::LoadBitmap()
	{
		Area.LoadBitmap(".\\Bitmaps\\container.bmp");
		score->LoadBitmap();
		score_board.LoadBitmap("Bitmaps\\score_board.bmp", RGB(0, 0, 0));

		for (int i = 0; i < 129; i++) {
			loading[i].LoadBitmap("Bitmaps\\Bitmap.bmp");
		}
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

	void GameArea::ShowScore() {
		int CurrentScore = score->GetInteger();
		int size = 1;
		while (CurrentScore > 9) {
			CurrentScore /= 10;
			size++;
			}
		//delete score;
		//score = new CInteger(size);
		if (size <=7){
		score->SetDigit(size);
		score->SetTopLeft((score_board.Left() + 135 - (18*size) ), score_board.Top() + 125);
		}

	}
	void GameArea::ShowStarBar() {
		//bar_width = 45;
		//bar_height = 254;
		// 127=100%  88=70%  108=85%
		//bottom left point 152,339px
		int X_point = (score_board.Left() + 150), Y_point = (score_board.Top() + 339); //loading bar set point
		double currentLevel = (score->GetInteger() / 40000.0) * 129;
		currentLevel = currentLevel > 129 ? 129 : currentLevel;
		for (int i = 0; i < currentLevel; i++) {
			loading[i].SetTopLeft(X_point, Y_point);
			Y_point -= 2;
		}
	}

	void GameArea::Find(Candy *candy, unsigned &row, unsigned &column)
	{
		for (unsigned i = 0; i < MaxHeight; i++)
			for (unsigned j = 0; j < MaxWidth; j++)
				if (&candies[i][j] == candy)
				{
					row = i;
					column = j;
					return;
				}
	}

	void GameArea::ReleasePower(Candy *candy, unsigned row, unsigned column)
	{
		if(candy != NULL) Find(candy, row, column); //if candy != NULL, get its' position in array
		else candy = &candies[row][column];			//else, row & column is candy's position

		if (!map[row][column]) return;

		int power = candy->GetPower();
		candy->SetStyle(0);
		candy->SetPower(0);

		switch (power)
		{
		case 0:
			break;
		case 1:
			RemoveRow(row);
			break;
		case 2:
			RemoveColumn(column);
			break;
		case 3:
			RemoveSquare(row, column, 1);
			break;
		case 4:
			RemoveStyle();
			break;
		}
		CAudio::Instance()->Play(AUDIO_DING, false);
	}

	void GameArea::ReleaseSwap()
	{
		int firstPow = clickedCandies[0]->GetPower(), secondPow = clickedCandies[1]->GetPower();
		if (firstPow == 4 && secondPow == 4)
		{
			unsigned row, column;
			Find(clickedCandies[0], row, column);
			RemoveSquare(row, column, 3);
		}
		else if (firstPow == 4 && secondPow)
		{
			PowerAll(clickedCandies[1]->GetStyle(), secondPow);
			clickedCandies[0]->SetStyle(0);
			clickedCandies[0]->SetPower(0);
		}
		else if (secondPow == 4 && firstPow)
		{
			PowerAll(clickedCandies[0]->GetStyle(), firstPow);
			clickedCandies[1]->SetStyle(0);
			clickedCandies[1]->SetPower(0);
		}
		else if (firstPow == 4 && !secondPow)
		{
			RemoveStyle(clickedCandies[1]->GetStyle());
			clickedCandies[0]->SetStyle(0);
			clickedCandies[0]->SetPower(0);
		}
		else if (secondPow == 4 && !firstPow)
		{
			RemoveStyle(clickedCandies[0]->GetStyle());
			clickedCandies[1]->SetStyle(0);
			clickedCandies[1]->SetPower(0);
		}
		else if (firstPow > 0 && firstPow < 3 && secondPow > 0 && secondPow < 3)
		{
			unsigned row, column;
			Find(clickedCandies[0], row, column);
			RemoveRow(row);
			RemoveColumn(column);
		}
		else if (firstPow == 3 && secondPow == 3)
		{
			unsigned row, column;
			Find(clickedCandies[0], row, column);
			RemoveSquare(row, column, 2);
		}
		else if (firstPow == 3 && secondPow > 0 && secondPow < 3)
		{
			unsigned row, column;
			Find(clickedCandies[1], row, column);
			for (unsigned i = row - 1; i < row + 2; i++)
				RemoveRow(i);
			for (unsigned i = column - 1; i < column + 2; i++)
				RemoveColumn(i);
		}
		else if (secondPow == 3 && firstPow > 0 && firstPow < 3)
		{
			unsigned row, column;
			Find(clickedCandies[0], row, column);
			for (unsigned i = row - 1; i < row + 2; i++)
				RemoveRow(i);
			for (unsigned i = column - 1; i < column + 2; i++)
				RemoveColumn(i);
		}
	}

	void GameArea::RemoveRow(unsigned row)
	{
		for (unsigned i = 0; i < MaxWidth; i++)
		{
			if (map[row][i])
			{
				if (!candies[row][i].GetPower())
					candies[row][i].SetStyle(0);
				else 
					ReleasePower(&candies[row][i]);
			}
		}
	}

	void GameArea::RemoveColumn(unsigned column)
	{
		for (unsigned i = 0; i < MaxWidth; i++)
		{
			if (map[i][column])
			{
				if (!candies[i][column].GetPower())
					candies[i][column].SetStyle(0);
				else
					ReleasePower(&candies[i][column]);
			}
		}
	}

	void GameArea::RemoveSquare(unsigned row, unsigned column, int level)
	{	//Level 1: wrapped candy be activated by normal way
		if (level == 1)
		{
			for (unsigned i = row - 1; i < row + 2; i++)
				for (unsigned j = column - 1; j < column + 2; j++)
				{
					if (i == row && j == column) continue;
					if (i > 0 && i < MaxHeight && j > 0 && j < MaxWidth)
						ReleasePower(NULL, i, j);
				}
		}
		//Level 2: two wrapped candies being swapped with each other
		else if (level == 2)
		{
			for (unsigned i = row - 2; i < row + 3; i++)
				for (unsigned j = column - 2; j < column + 3; j++)
				{
					if (i == row && j == column) continue;
					if (i > 0 && i < MaxHeight && j > 0 && j < MaxWidth)
						ReleasePower(NULL, i, j);
				}
		}
		//Level 3: two superCandy being swapped with each other
		else if (level == 3)
		{
			for (unsigned i = 0; i < MaxHeight; i++)
				for (unsigned j = 0; j < MaxWidth; j++)
					if (map[i][j]) ReleasePower(NULL, i, j);
		}
	}

	void GameArea::RemoveStyle(int style)
	{
		if (!style) style = rand() % MAX_RAND_NUM + 1;

		for (int i = 0; i < MaxHeight; i++)
			for (int j = 0; j < MaxWidth; j++)
				if (candies[i][j].GetStyle() == style)
					ReleasePower(&candies[i][j]);
	}

	void GameArea::PowerAll(int style, int power)
	{
		for (int i = 0; i < MaxHeight; i++)
			for (int j = 0; j < MaxWidth; j++)
				if (candies[i][j].GetStyle() == style)
				{
					if (power == 1 || power == 2) power = rand() % 2 + 1;
					candies[i][j].SetPower(power);
				}
	}

	int GameArea::GetScore()
	{
		return score->GetInteger();
	}

	void GameArea::OnShow()
	{
		///////////////////////////////////////////
		// Show score board  					///
		///////////////////////////////////////////
		score_board.SetTopLeft((SIZE_X - 1211) / 2, ((SIZE_Y - 420) / 2));
		score_board.ShowBitmap();
		ShowScore();
		ShowStarBar();
		score->ShowBitmap();
		for (int i = 0; i < 129; i++) {
			loading[i].ShowBitmap();
		}
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
				if (candies[i][j].GetStyle() != 0 && candies[i][j].GetCurrentY() > 35)
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
			{//If there is a combo after swapping candies, initiate click
				InitClickedCandy();
			}
			else if (!amountCleared && clickedCandies.size() == 2)
			{ //else swap two candies back to original position
				SwapCandy();
				InitClickedCandy();
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
			auto candy = find(clickedCandies.begin(), clickedCandies.end(), clickedCandy); //GetCandyIterator

			if (candy == clickedCandies.end())
				clickedCandies.push_back(clickedCandy);
			else clickedCandies.erase(candy);			//If player click a candy twice, initiate click

			if (clickedCandies.size() == 2)
			{	//if two candies clicked, swap if they are neighbour
				if (IsNeighbour(*clickedCandies[0], *clickedCandies[1]))
				{
					SwapCandy();
					//Release swapPower when each of clickedCandy is superCandy or both are poweredCandy
					if (clickedCandies[0]->GetPower() == 4 || clickedCandies[1]->GetPower() == 4 || (clickedCandies[0]->GetPower() && clickedCandies[1]->GetPower()))
						ReleaseSwap();
				}
				else InitClickedCandy();
			}
		}
	}

	void GameArea::OnLButtonUp(UINT nFlags, CPoint point)
	{

	}

	void GameArea::OnMouseMove(UINT nFlags, CPoint point)
	{

	}

	void GameArea::InitCandy(bool drop)
	{
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				switch (map[i][j])
				{
				case 0:
					candies[i][j] = Candy();
					break;

				default:
					int id = drop == true ? 0 : rand() % MAX_RAND_NUM + 1;
					candies[i][j] = Candy(id, j * 50 + x, i * 50 + y);
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
				{	//Drop in current column
					if (!candies[i + 1][j].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
					//drop into left column
					else if (map[i + 1][j - 1] && !candies[i][j - 1].GetStyle() && !candies[i + 1][j - 1].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftX() - 50, candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j - 1] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
					//drop into right column
					else if (map[i + 1][j + 1]&& !candies[i][j + 1].GetStyle() && !candies[i + 1][j + 1].GetStyle())
					{
						candies[i][j].SetDestination(candies[i][j].GetTopLeftX() + 50, candies[i][j].GetTopLeftY() + 50);

						candies[i + 1][j + 1] = candies[i][j];
						candies[i][j].SetStyle(0);
					}
				}
	}

	int GameArea::ClearCombo()
	{
		set<Candy*> accumulateCandy;
		int comboDeleted = 0;
		for (int i = 0; i < MaxHeight; i++)
		{
			for (int j = 0; j < MaxWidth; j++)
			{
				if (!candies[i][j].GetStyle()) continue;
				accumulateCandy.insert(&candies[i][j]);						//put the first candy into set
				GetCandies(accumulateCandy, i, j, candies[i][j].GetStyle());//collect all similar candies that follow-up with first
				comboDeleted += DeleteCombo(accumulateCandy);				//delete all combo
			}
		}
		return comboDeleted;
	}

	void GameArea::GetCandies(set<Candy*>& accumulateCandy, int i, int j, int checkStyle)
	{	//Recursive condition: there is(are) same candy(ies) nearby
		int currentStyle = candies[i][j].GetStyle();
		candies[i][j].SetStyle(0);
		if (j + 1 < MaxWidth && candies[i][j + 1].GetStyle() == checkStyle && candies[i][j + 1].GetPower() != 4)
		{//check to the right
			accumulateCandy.insert(&candies[i][j + 1]);
			GetCandies(accumulateCandy, i, j + 1, checkStyle);
		}
		if (i + 1 < MaxHeight && candies[i + 1][j].GetStyle() == checkStyle && candies[i + 1][j].GetPower() != 4)
		{//Check downward
			accumulateCandy.insert(&candies[i + 1][j]);
			GetCandies(accumulateCandy, i + 1, j, checkStyle);
		}
		if (j - 1 >= 0 && candies[i][j - 1].GetStyle() == checkStyle && candies[i][j - 1].GetPower() != 4)
		{//Check to the left
			accumulateCandy.insert(&candies[i][j - 1]);
			GetCandies(accumulateCandy, i, j - 1, checkStyle);
		}
		if (i - 1 >= 0 && candies[i - 1][j].GetStyle() == checkStyle && candies[i - 1][j].GetPower() != 4)
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
		int comboDeleted = 0;
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
		comboDeleted += RemoveContinuous(toDelete, 'y', &CompareY);
		for (auto i = accumulateCandy.begin(); i != accumulateCandy.end(); i++)
		{	/*delete if more than 3 candies on a horizontal line*/
			if (count(y.begin(), y.end(), (*i)->GetTopLeftY()) >= 3)
				toDelete.push_back(*i);
		}
		comboDeleted += RemoveContinuous(toDelete, 'x', &CompareX);
		accumulateCandy.clear();
		return comboDeleted;
	}

	int GameArea::RemoveContinuous(vector<Candy*>& toDelete, char axis, bool(*Compare)(Candy*, Candy*))
	{
		if (!toDelete.size()) return 0; //pass

		vector<Candy*> line;
		char check = axis == 'x' ? 'y' : 'x';
		int conboDeleted = 0;
		while(1)
		{	
			GetLine(line, toDelete, check);					//collect candies on a same line
			stable_sort(line.begin(), line.end(), Compare);	//When their x/y are same, sort according to y/x

			int count = 1;
			for (unsigned int i = 0; i < line.size() - 1; i++)
			{
				if (line[i]->GetTopLeft(axis) + 50 == line[i + 1]->GetTopLeft(axis)) count++;	//If next candy is follow-up with current, keep counting
				else if (count < 3) count = 1;											//else, if count >= 3 -> combo, or pass
				else
				{
					RemoveContinuous(line, i - count, i, axis);
					count = 1;
					conboDeleted++;
				}
			}
			if (count >= 3)
			{
				RemoveContinuous(line, line.size() - count, line.size(), axis);
				conboDeleted++;
			}
			line.clear();
			if (toDelete.size() < 3) break;	//break if there is not enough candies to form a combo
		}
		toDelete.clear();
		return conboDeleted;
	}

	void GameArea::RemoveContinuous(vector<Candy*>& line, unsigned offset, unsigned lineSize, char axis)
	{
		bool linePower = lineSize - offset == 4 ? true : false;
		bool superCandy = lineSize - offset > 4 ? true : false;
		vector<Candy*> temp;
		for (unsigned int j = offset; j < lineSize; j++)
		{	
			if (line[j]->GetPower()) temp.push_back(line[j]);
			if (linePower && find(clickedCandies.begin(), clickedCandies.end(), line[j]) != clickedCandies.end())
			{
				line[j]->SetPower(axis == 'x' ? 2 : 1);
				linePower = false;
				continue;
			}
			if (!line[j]->GetStyle())
			{
				line[j]->SetPower(3);
				line[j]->Relive();
				superCandy = false;
				continue;
			}
			if (superCandy && find(clickedCandies.begin(), clickedCandies.end(), line[j]) != clickedCandies.end())
			{
				superCandy = false;
				line[j]->SetPower(4);
				continue;
			}
			ReleasePower(line[j]);
			score->Add(60);
		}
		if (linePower) line[0]->SetPower(axis == 'x' ? 2 : 1);
		if (superCandy) line[0]->SetPower(4);
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

	void GameArea::InitClickedCandy()
	{
		clickedCandies[0]->Click();
		clickedCandies[1]->Click();
		clickedCandies.clear();
	}
}