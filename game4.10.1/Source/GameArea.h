﻿#ifndef GAMEAREA_H
#define GAMEAREA_H

#define MaxHeight 13
#define MaxWidth 20

namespace game_framework
{
	class GameArea
	{
	public:
		GameArea();
		~GameArea();
		int GetScore();									//Get current score
		void InitCandy(bool drop = true);				//spawn all candies randomly
		bool IsGameOver();
		int GetCurrentStage();
		void LoadBitmap();								//load game area's background
		void LoadStage(vector<Stage*>& stages, int);	//read map from file
		void OnShow();									//Display game area and candy
		void OnMove();
		void OnKeyDown(UINT, UINT, UINT);				//handle keyboard press
		void OnKeyUp(UINT, UINT, UINT);					//handle keyboard unpress
		void OnLButtonDown(UINT nFlags, CPoint point);	//handle mouse click
		void OnLButtonUp(UINT nFlags, CPoint point);	//handle mouse unclick
		void OnMouseMove(UINT nFlags, CPoint point);	//handle mouse move
		void SetSound(bool);							//switch sound on/off
	private:
		int ClearCombo();								//search and delete all combo
		int Compare(int, int);							//Compare two int
		void Delay();									//pause game state for (delay)secs
		void DropCandy();
		int DropCandyStraight();
		int DropCandySide();
		int DeleteCombo(set<Candy*>&);					//analyze and delete combo
		void Find(Candy*, unsigned&, unsigned&);		//find candy and return its' row and column
		int FindCombo();
		void GetCandies(set<Candy*>&, int, int, int);	//get continuous candies
		void GetLine(vector<Candy*>&, vector<Candy*>&, char check);									//collect candies on a same line
		void InitClickedCandy();						//unclick & clear candies in clickedCandies
		bool IsDropping();								//check all candies are still
		bool IsNeighbour(Candy&, Candy&);				//return are candies in clickedCandies is neighbour
		void OnMoveBlasts();
		void OnMoveEnding();
		void PowerAll(int style, int power, int x, int y);	//Power all specific candy
		int PutCandy();									//spawn candies at spawning area
		void PutEndingBonus();
		int RemoveContinuous(vector<Candy*>&, char, bool(*Compare)(Candy*, Candy*), set<Candy*>&);	//Find and remove continuous candy
		void RemoveContinuous(vector<Candy*>&, unsigned, unsigned, char, set<Candy*>&);				//Remove continuous candy
		void ReleaseInOrder();
		void ReleasePower(Candy*, unsigned row = 0, unsigned column = 0);							//remove candy with consider its' power
		void ReleaseSwap();								//activate power of candy when 2 powered candy swapped
		void RemoveAll(int row, int column);			//remove all candies
		void RemoveRow(unsigned);						//remove whole row of candies
		void RemoveColumn(unsigned);					//remove whole column of candies
		void RemoveSquare(int, int, int);				//remove surrounding candies according to level
		void RemoveStyle(int x, int y, int style = 0);	//remove all specific candy
		void ShowLoading();								//Show loading image
		void SwapCandy();								//Swap candies in clickedCandies
		void TeleportCandy();
		void UpdateCurPosition();						//update current position of every candy

		const int x, y;									//top left x,y of gameArea
		bool sound;
		int map[MaxHeight][MaxWidth];					//Array of container
		int delay, delayRemoveStyle;
		bool delayRemove, releaseSwap;
		int currentComboSound, totalCandyCleared;
		Candy* curPosition[MaxHeight][MaxWidth];		//save current position of every candy
		list<pair<int, int>> spawnArea;					//save position where candy spawn
		Candy candies[MaxHeight][MaxWidth];				//Array of candy
		CMovingBitmap area, singleJelly, doubleJelly;	//container bmp
		vector<Candy*> clickedCandies;					//save clicked candy/ies maximun size = 2
		list<Blast*> blasts;
		list<list<Candy*>*> removeList;					//These candies will be removed after delay
		list<Candy*> endingBonus;
		ScoreBoard scoreBoard;

		vector<Stage*>::iterator stage;
		int MAX_RAND_NUM;								//types of candies in this games
		bool initiating, ending, running, gameOver;

		bool goldFinger;
	};
}

#endif 