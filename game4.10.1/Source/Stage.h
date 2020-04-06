#pragma once
#ifndef STAGE_H
#define STAGE_H


namespace game_framework
{
	class Stage
	{
	public:
		Stage();
		void LoadStage();
		int GetScoreOne();
		int GetScoreTwo();
		int GetScoreThree();
		int GetVertical();
		int GetHorizontal();
		int GetTEffect();
		int GetChocolate();
		int GetCandyType();
		int GetLastScoreHistory();
	private:
		int map[13][20];
		int ScoreOne, ScoreTwo, ScoreThree, Vertical, Horizontal, TEffect, Chocolate, CandyType, LastScoreHistory;

	};
}
#endif