#pragma once
#ifndef STAGE_H
#define STAGE_H


namespace game_framework
{
	class Stage
	{
		friend class GameArea;
	public:
		Stage();
		void LoadStage(string);
		int GetScoreOne();
		int GetScoreTwo();
		int GetScoreThree();
		int GetVertical();
		int GetHorizontal();
		int GetPack();
		int GetChocolate();
		int GetCandyType();
		int GetLastScoreHistory();
		int GetMaxStep();
		int GetMode();
		bool IsUnlock();
	private:
		int map[13][20];
		int scoreOne, scoreTwo, scoreThree;			//Target score for three star
		int vertical, horizontal, pack, chocolate;	//total special candy spawn onInit
		int candyType;								//Max candy type in this game
		int lastHighScore;							//History highest score
		int maxStep;
		int mode;
		bool isUnlock;

	};
}
#endif