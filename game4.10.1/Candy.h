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
		void LoadBitmap();					//Load candy's bitmap according to style
		void OnMove();						//move if current coordinate != destination coordinate
		void OnShow();						//display candy
		void SetDestination(int, int);		//set destination x,y
		void SetDestination(int);			//set destination y
		int GetStyle();						//get current style
		void SetStyle(int);					//change current style
		int GetTopLeftX();					//Get destination x
		int GetTopLeftY();					//Get destination y
		int GetTopLeft(char c);				//Get destination(c) 'x'/'y'
		int GetCurrentX();					//Get current x
		int GetCurrentY();					//Get current y
		bool IsMoving();					//return current coordinate != destination coordinate
		bool IsClicked();					//return onClick
		Candy* Click();						//Change state of onClick if being clicked
		void SetPower(int);					//Set current power
		int GetPower();						//return current power
		void Relive();						//reset candy's style
	private:
		void GetCurrentShow(CMovingBitmap**, CMovingBitmap**);

		CMovingBitmap red[8];
		CMovingBitmap orange[8];
		CMovingBitmap green[8];
		CMovingBitmap blue[8];
		CMovingBitmap purple[8];
		CMovingBitmap super, superClick;
		int style;					//0 = non-exist
		int rawStyle;
		int x, y;					//current coordinate
		int dx, dy;					//destination coordinate
		bool onClick;
		int fallingSpeed;
		int power;
	};
}

#endif