#ifndef CANDY_H
#define CANDY_H

namespace game_framework
{
	class Candy
	{
	public:
		Candy(int, int, int);
		Candy(int, int);
		Candy();
		~Candy();
		Candy* Click();						//Change state of onClick if being clicked
		void GetBmpId(int**);				//Get bitmap directory according to style
		int GetCurrentX();					//Get current x
		int GetCurrentY();					//Get current y
		int GetPower();						//return current power
		int GetStyle();						//get current style
		int GetTopLeftX();					//Get destination x
		int GetTopLeftY();					//Get destination y
		int GetTopLeft(char c);				//Get destination(c) 'x'/'y'
		void InitClick();					//Unclick self
		bool IsMoving();					//return current coordinate != destination coordinate
		bool IsClicked();					//return onClick
		void Kill();						//simple remove without release power
		void LoadBitmap();					//Load candy's bitmap according to style
		void OnMove(bool mute = false);		//move if current coordinate != destination coordinate
		void OnShow();						//display candy
		void Push(int, int);				//Push candies around self
		void Relive();						//reset candy's style
		void SetDestination(int, int);		//set destination x,y
		void SetDestination(int);			//set destination y
		void SetStyle(int);					//change current style
		void SetPower(int);					//Set current power
	private:
		void GetCurrentShow(CMovingBitmap**, CMovingBitmap**);

		CMovingBitmap normal, normalClick;
		CMovingBitmap horizon, horizonClick;
		CMovingBitmap vertical, verticalClick;
		CMovingBitmap pack, packClick;
		CMovingBitmap super, superClick;
		int style, rawStyle;		//0 = non-exist
		int power;
		int x, y, dx, dy, pushX, pushY;			//current || destination coordinate
		bool onClick;
		int fallingSpeed;
	};
}

#endif
