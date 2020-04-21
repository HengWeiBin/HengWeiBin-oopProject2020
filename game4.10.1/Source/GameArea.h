#ifndef GAMEAREA_H
#define GAMEAREA_H

#define MaxHeight 13
#define MaxWidth 20

namespace game_framework
{
	#ifndef AUDIO_ID
	#define AUDIO_ID
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_JELLY,
		AUDIO_NEG_SWAP, AUDIO_SWAP,
		AUDIO_SUPER_CREATE, AUDIO_LINE_CREATE, AUDIO_PACK_CREATE, AUDIO_POWER_ALL,
		AUDIO_SQUARE_REMOVE1, AUDIO_SQUARE_REMOVE2, AUDIO_LINE_BLAST,
		AUDIO_CANDY_LAND1, AUDIO_CANDY_LAND2, AUDIO_CANDY_LAND3, AUDIO_CANDY_LAND4,
		AUDIO_COMBO1, AUDIO_COMBO2, AUDIO_COMBO3, AUDIO_COMBO4, AUDIO_COMBO5, AUDIO_COMBO6,
		AUDIO_COMBO7, AUDIO_COMBO8, AUDIO_COMBO9, AUDIO_COMBO10, AUDIO_COMBO11, AUDIO_COMBO12
	};
	#endif

	class GameArea
	{
	public:
		GameArea();
		GameArea(Stage& stage);
		~GameArea();
		void InitCandy(bool drop = true);				//spawn all candies randomly
		void LoadBitmap();								//load game area's background
		void LoadStage(int);							//read map from file
		void LoadStage(Stage& stage);
		void OnShow();									//Display game area and candy
		void OnMove();
		void OnLButtonDown(UINT nFlags, CPoint point);	//handle mouse click
		void OnLButtonUp(UINT nFlags, CPoint point);	//handle mouse unclick
		void OnMouseMove(UINT nFlags, CPoint point);	//handle mouse move
	private:
		int ClearCombo();								//search and delete all combo
		int Compare(int, int);							//Compare two int
		void DropCandy();
		int DropCandyStraight();
		int DropCandySide();
		int DeleteCombo(set<Candy*>&);					//analyze and delete combo
		void Find(Candy*, unsigned&, unsigned&);		//find candy and return row and column
		void GetCandies(set<Candy*>&, int, int, int);	//get continuous candies
		void GetLine(vector<Candy*>&, vector<Candy*>&, char check);									//collect candies on a same line
		int GetScore();									//Get current score
		void InitClickedCandy();						//unclick & clear candies in clickedCandies
		bool IsDropping();								//check all candies are still
		bool IsNeighbour(Candy&, Candy&);				//return are candies in clickedCandies is neighbour
		void PowerAll(int, int);						//Power all specific candy
		int PutCandy();									//spawn candies at spawning area
		int RemoveContinuous(vector<Candy*>&, char, bool(*Compare)(Candy*, Candy*), set<Candy*>&);	//Find and remove continuous candy
		void RemoveContinuous(vector<Candy*>&, unsigned, unsigned, char, set<Candy*>&);				//Remove continuous candy
		void ReleasePower(Candy*, unsigned row = 0, unsigned column = 0);							//remove candy with consider its' power
		void ReleaseSwap();								//activate power of candy when 2 powered candy swapped
		void RemoveRow(unsigned);						//remove whole row of candies
		void RemoveColumn(unsigned);					//remove whole column of candies
		void RemoveSquare(int, int, int);				//remove surrounding candies according to level
		void RemoveStyle(int style = 0);				//remove all specific candy
		void ShowScoreBoard();
		void SwapCandy();								//Swap candies in clickedCandies
		void UpdateCurPosition();						//update current position of every candy

		const int x, y;									//top left x,y of gameArea
		int map[MaxHeight][MaxWidth];					//Array of container
		Candy* curPosition[MaxHeight][MaxWidth];		//save current position of every candy
		list<pair<int, int>> spawnArea;					
		Candy candies[MaxHeight][MaxWidth];				//Array of candy
		CMovingBitmap area, singleJelly, doubleJelly;	//container bmp
		CMovingBitmap scoreBar, blackBar, scoreBoard;	//scoreboard		
		CInteger score;
		vector<Candy*> clickedCandies;
		list<Blast*> blasts;

		int MAX_RAND_NUM;								//types of candies in this games
		int oneStar, twoStar, threeStar, lastHighScore;//Target
		int step;
		bool running;
	};
}

#endif 