#pragma once
#ifndef STAGE_H
#define STAGE_H


namespace game_framework
{
	class Stage
	{
		friend class GameArea;
	public:
		Stage(int);
		void LoadStage();
		double GetScoreOne();
		double GetScoreTwo();
		double GetScoreThree();
		double GetLastScoreHistory();
		bool IsUnlock();
		void RemoveLine();
		void WriteBack();
		void SetUnlock();
		int GetCurrentScore();
		int GetCurrentStage();
		void SetCurrentScore(int score);
	private:
		int map[13][20];
		double scoreOne, scoreTwo, scoreThree;		//Target score for three star
		int vertical, horizontal, pack, chocolate;	//total special candy spawn onInit
		int candyType;								//Max candy type in this game
		double lastHighScore;						//History highest score
		int maxStep;
		int mode;
		bool isUnlock;
		bool initcandy;
		string stageTxt[2];
		int currentStage;
		int currentScore;
	};
}
#endif