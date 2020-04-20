#pragma once
#ifndef BLAST_H
#define BLAST_H

namespace game_framework
{
	class Blast
	{
	public:
		Blast();
		virtual void LoadBitmap() {};
		virtual void OnShow() {};
		virtual void OnMove() {};
		virtual void SetTopLeft() {};
	private:
		CMovingBitmap normal;
	};

	class NormalBlast :public Blast
	{
	public:
		NormalBlast();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetTopLeft(int, int);
	private:
		CMovingBitmap bmp;
		int delay;
		double zoom;
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
		int delay;
		double zoom;
	};
}

#endif
