#ifndef GAMEAREA_H
#define GAMEAREA_H

#define MaxHeight 13
#define MaxWidth 20

namespace game_framework
{
	#ifndef AUDIO_ID
	#define AUDIO_ID
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_JELLY				// 2
	};
	#endif

	class GameArea
	{
	public:
		GameArea();
		GameArea(Stage& stage);
		~GameArea();
		void LoadBitmap();								//load game area's background
		void LoadStage();								//read map from file
		void OnShow();									//Display game area and candy
		void OnMove();
		void OnLButtonDown(UINT nFlags, CPoint point);	//handle mouse click
		void OnLButtonUp(UINT nFlags, CPoint point);	//handle mouse unclick
		void OnMouseMove(UINT nFlags, CPoint point);	//handle mouse move
		void InitCandy(bool drop = true);				//spawn all candies randomly
	private:
		void DropCandy();
		int DropCandyStraight();
		int DropCandySide();
		int ClearCombo();								//search and delete all combo
		void GetCandies(set<Candy*>&, int, int, int);	//get continuous candies
		int DeleteCombo(set<Candy*>&);					//analyze and delete combo
		int RemoveContinuous(vector<Candy*>&, char, bool(*Compare)(Candy*, Candy*));	//Find and remove continuous candy
		void RemoveContinuous(vector<Candy*>&, unsigned, unsigned, char);				//Remove continuous candy
		void GetLine(vector<Candy*>&, vector<Candy*>&, char check);						//collect candies on a same line
		int PutCandy();								//spawn candies at spawning area
		bool IsDropping();								//check all candies are still
		void SwapCandy();								//Swap candies in clickedCandies
		bool IsNeighbour(Candy&, Candy&);				//return are candies in clickedCandies is neighbour
		void InitClickedCandy();						//unclick & clear candies in clickedCandies
		void ShowScore();
		void ShowStarBar();
		void Find(Candy*, unsigned&, unsigned&);		//find candy and return row and column
		void ReleasePower(Candy*, unsigned row = 0, unsigned column = 0);				//remove candy with consider its' power
		void ReleaseSwap();								//activate power of candy when 2 powered candy swapped
		void RemoveRow(unsigned);						//remove whole row of candies
		void RemoveColumn(unsigned);					//remove whole column of candies
		void RemoveSquare(unsigned, unsigned, int);		//remove surrounding candies according to level
		void RemoveStyle(int style = 0);				//remove all specific candy
		void PowerAll(int, int);						//Power all specific candy
		int GetScore();									//Get current score
		void UpdateCurPosition();						//update current position of every candy

		const int MAX_RAND_NUM;							//types of candies in this games
		const int x, y;									//top left x,y of gameArea
		int map[MaxHeight][MaxWidth];					//Array of container
		Candy* curPosition[MaxHeight][MaxWidth];		//save current position of every candy
		list<pair<int, int>> spawnArea;					
		Candy candies[MaxHeight][MaxWidth];				//Array of candy
		CMovingBitmap area;
		CMovingBitmap scoreBar, scoreBoard;							
		CInteger score;
		vector<Candy*> clickedCandies;
	};
}

#endif 