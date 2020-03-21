﻿#ifndef CANDY_H
#define CANDY_H

namespace game_framework
{
	class Candy
	{
	public:
		Candy(int, int, int);
		Candy();
		~Candy();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetDestination(int, int);
		bool IsAlive();
		void SetAlive(bool);
		int GetStyle();
	private:
		CMovingBitmap bmp;
		int style;				//0 = non-exist
		bool alive;
		int x, y;				//current coordinate
		int dx, dy;				//destination coordinate 
	};
}

#endif
