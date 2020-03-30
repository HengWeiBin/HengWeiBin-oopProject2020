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
		void LoadStage();
	private:
		int map[13][20];
		int ScoreOne, ScoreTwo, ScoreThree, Vertical, Horizontal, TEffect, Chocolate, CandyType, LastScoreHistory;

	};
}
#endif