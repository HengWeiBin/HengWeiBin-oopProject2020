namespace game_framework
{
	class Candy
	{
	public:
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
		bool alive;
		int x, y;
	};
}

