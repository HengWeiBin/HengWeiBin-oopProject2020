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
		void SetXY(int, int);
		bool IsAlive();
		void SetAlive(bool);
	private:
		CMovingBitmap bmp;
		int style;
		bool alive;
		int x, y;
	};
}

