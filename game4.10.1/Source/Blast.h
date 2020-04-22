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
		virtual void SetTopLeft() {};
		virtual bool IsLast() = 0;
	protected:
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
		void SetTopLeft(int, int);
		bool IsLast();
	private:
		void GetBmpId(int*&, int style);

		CMovingBitmap candy[4];
		CMovingBitmap normalBlast[10];
		int curShow;
	};

	class HorizonBlast :public Blast
	{
	public:
		HorizonBlast();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetTopLeft(int, int);
	private:
		CMovingBitmap bmp;
		double zoom;
	};
}

#endif
