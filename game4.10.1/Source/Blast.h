#pragma once
#ifndef BLAST_H
#define BLAST_H

#define REDCANDY 5
#define YELLOWCANDY 6
#define ORANGECANDY 3
#define GREENCANDY 4
#define BLUECANDY 1
#define PURPLECANDY 2

namespace game_framework
{
	class Blast
	{
	public:
		virtual void LoadBitmap() {};
		virtual void OnShow() {};
		virtual void OnMove() {};
		virtual void SetTopLeft(int, int);
		virtual bool IsLast() = 0;
	protected:
		void GetBmpId(int*&, int style);
		int x, y;
	};

	class NormalBlast :public Blast
	{
	public:
		NormalBlast();
		NormalBlast(int, int, int);
		void LoadBitmap(int);
		void OnMove();
		void OnShow();
		bool IsLast();
	private:

		CMovingBitmap candy[4];
		CMovingBitmap normalBlast[10];
		CMovingBitmap shatter[15];
		int curShow;
		int shift[3][3];				//move direction/ moving speed/ spin direction
		int shatPosition[3][2];			//every shatter current position
		int shatShow[3];				//shatter current frame
		const int totalShow;			//total shatter spawned
		double size;					//current size
	};

	class LineBlast :public Blast
	{
	public:
		LineBlast(int, int, int, int);
		void LoadBitmap(int);
		void OnMove();
		void OnShow();
		bool IsLast();
	private:
		CMovingBitmap horizontal[30];
		CMovingBitmap vertical[30];
		int curShow;
		int powStyle;
	};
}

#endif
