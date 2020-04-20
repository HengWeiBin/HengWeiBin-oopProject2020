#ifndef CANDY_H
#define CANDY_H

namespace game_framework
{
#ifndef AUDIO_ID
#define AUDIO_ID
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_JELLY,AUDIO_STAGE,
		AUDIO_NEG_SWAP, AUDIO_SWAP,
		AUDIO_SUPER_CREATE, AUDIO_LINE_CREATE, AUDIO_PACK_CREATE, AUDIO_POWER_ALL,
		AUDIO_SQUARE_REMOVE1, AUDIO_SQUARE_REMOVE2, AUDIO_LINE_BLAST,
		AUDIO_CANDY_LAND1, AUDIO_CANDY_LAND2, AUDIO_CANDY_LAND3, AUDIO_CANDY_LAND4,
		AUDIO_COMBO1, AUDIO_COMBO2, AUDIO_COMBO3, AUDIO_COMBO4, AUDIO_COMBO5, AUDIO_COMBO6,
		AUDIO_COMBO7, AUDIO_COMBO8, AUDIO_COMBO9, AUDIO_COMBO10, AUDIO_COMBO11, AUDIO_COMBO12
	};
#endif

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
		void Kill();
		void LoadBitmap();					//Load candy's bitmap according to style
		void OnMove();						//move if current coordinate != destination coordinate
		void OnShow();						//display candy
		void Push(int, int);				//Push candies around self
		void Relive();						//reset candy's style
		void SetDestination(int, int);		//set destination x,y
		void SetDestination(int);			//set destination y
		void SetStyle(int);					//change current style
		void SetPower(int);					//Set current power
	private:
		void GetCurrentShow(CMovingBitmap**, CMovingBitmap**);

		CAnimation minify;
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
		bool isBlast;
	};
}

#endif
