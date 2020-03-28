#ifndef CANDY_H
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
		void SetDestination(int);
		int GetStyle();
		void SetStyle(int);
		void GetBitmapDirectory(int, char*);
		int GetTopLeftX();
		int GetTopLeftY();
		int GetTopLeft(char c);
		int GetCurrentX();
		int GetCurrentY();
		bool IsMoving();
	private:
		CMovingBitmap bmp;		//candy's bitmap
		int style;				//0 = non-exist
		//bool alive;
		int x, y;				//current coordinate
		int dx, dy;				//destination coordinate 
	};
}

#endif
