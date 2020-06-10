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
		~Stage();
		void LoadStage();
		double GetScoreOne();
		double GetScoreTwo();
		double GetScoreThree();
		double GetLastScoreHistory();
		bool IsUnlock();
		bool IsFail();
		void SetPassOrFail(int);
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
		bool isFail;
		bool initcandy;
		string stageTxt;
		int currentStage;
		int currentScore;
		bool hasPortal;
		vector<pair<CPoint, CPoint>> portalList;
	};
}
#endif