#ifndef GAMEAREA_H
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
		void LoadBitmap();								//load game area's background
		void LoadStage();								//read map from file
		void OnShow();									//Display game area and candy
		void OnMove();
		void OnLButtonDown(UINT nFlags, CPoint point);	//handle mouse click
		void OnLButtonUp(UINT nFlags, CPoint point);	//handle mouse unclick
		void OnMouseMove(UINT nFlags, CPoint point);	//handle mouse move
		void InitCandy();								//spawn all candies randomly
	private:
		void DropCandy();
		void ClearCombo();								//search and delete all combo
		void GetCandies(set<Candy*>&, int, int, int);	//get continuous candies
		void DeleteCombo(set<Candy*>&);					//analyze and delete combo
		void RemoveContinuous(vector<Candy*>&, char, bool(*Compare)(Candy*, Candy*));			//Remove continuous candy
		void PutCandy();								//spawn candies at spawning area
		bool IsDropping();								//check all candies are still
		void ExchangeCandy();
		bool IsNeighbour(Candy&, Candy&);

		int map[MaxHeight][MaxWidth];
		int x, y;										//top left x,y of gameArea
		Candy candies[MaxHeight][MaxWidth];
		CMovingBitmap Area;
		int MAX_RAND_NUM;								//types of candies in this games
		CInteger score;
		vector<Candy*> clickedCandies;

	};
}

#endif 