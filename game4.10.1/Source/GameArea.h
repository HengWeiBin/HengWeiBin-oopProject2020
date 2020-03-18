namespace game_framework
{
	class GameArea
	{
	public:
		GameArea();
		~GameArea();
		void LoadBitmap();
		void LoadStage();
		void OnShow();
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnLButtonUp(UINT nFlags, CPoint point);
		void OnMouseMove(UINT nFlags, CPoint point);
		void InitCandy();
		void CheckCombo();
	private:
		int map[13][20];
		int x, y;	
		Candy* candies;
	};
}