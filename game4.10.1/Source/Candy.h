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
		void LoadBitmap();					//Load candy's bitmap according to style
		void OnMove();						//move if current coordinate != destination coordinate
		void OnShow();						//display candy
		void SetDestination(int, int);		//set destination x,y
		void SetDestination(int);			//set destination y
		int GetStyle();						//get current style
		void SetStyle(int);					//change current style
		void GetBitmapDirectory(char*);		//Get bitmap directory according to style
		int GetTopLeftX();					//Get destination x
		int GetTopLeftY();					//Get destination y
		int GetTopLeft(char c);				//Get destination(c) 'x'/'y'
		int GetCurrentX();					//Get current x
		int GetCurrentY();					//Get current y
		bool IsMoving();					//return current coordinate != destination coordinate
	private:
		CMovingBitmap bmp;		//candy's bitmap
		int style;				//0 = non-exist
		int x, y;				//current coordinate
		int dx, dy;				//destination coordinate
		bool onClick;
	};
}

#endif
