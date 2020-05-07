#ifndef SCOREBOARD_H
#define SCOREBOARD_H

namespace game_framework
{
	class ScoreBoard
	{
		friend class GameArea;
	public:
		ScoreBoard();
		void OnShow();
		void LoadBitmap();

	private:
		void ShowStars();
		void ShowMoves();
		void ShowScoreBar();
		void ShowScore();

		CMovingBitmap scoreBar, blackBar, scoreBoard;
		CMovingBitmap yellowStar, greenStar, redStar;
		CMovingBitmap emptyStar2, emptyStar1;
		CInteger score, moves;
		double oneStar, twoStar, threeStar, lastHighScore;
	};
}

#endif