#pragma once
#ifndef STAGE_H
#define STAGE_H


namespace game_framework
{
	class Stage
	{
		friend class GameArea;
	public:
		Stage(string);
		void LoadStage();
		int GetScoreOne();
		int GetScoreTwo();
		int GetScoreThree();
		int GetLastScoreHistory();
		bool IsUnlock();
		void RemoveLine();
		void WriteBack(int LastScore);
	private:
		int map[13][20];
		int scoreOne, scoreTwo, scoreThree;			//Target score for three star
		int vertical, horizontal, pack, chocolate;	//total special candy spawn onInit
		int candyType;								//Max candy type in this game
		int lastHighScore;							//History highest score
		int maxStep;
		int mode;
		bool isUnlock;
		bool initcandy;
		string stageTxt;
	};
}
#endif