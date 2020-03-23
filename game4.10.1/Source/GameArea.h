#ifndef GAMEAREA_H
#define GAMEAREA_H

namespace game_framework
{
	class GameArea
	{
	public:
		GameArea();										
		~GameArea();
		void LoadBitmap();								//load game area's background
		void LoadStage();								
		void OnShow();									//Display game area and candy
		void OnMove();
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void InitCandy();
		void CheckCombo();
		void KillCombo(int&, vector<Candy*>&, int, int);
		void KillCandy(vector<Candy*>&);
		void DropCandy();
	private:
		int map[13][20];
		int x, y;	
		Candy** candies;
		CMovingBitmap Area;

	};
}

#endif 