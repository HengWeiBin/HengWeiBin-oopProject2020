#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <fstream>
#include <string>
#include "audio.h"
#include "gamelib.h"
#include "Stage.h"

using namespace std;

game_framework::Stage::Stage()
{
	scoreOne = 0; scoreTwo = 0; scoreThree = 0;		//Target score for three star
	vertical = 0; horizontal = 0; pack = 0; chocolate = 0;	//total special candy spawn onInit
	candyType = 0;								//Max candy type in this game
	lastHighScore = 0;							//History highest score
	maxStep = 0;
	mode = 0;
	isUnlock = 0;
}

void game_framework::Stage::LoadStage(string StageTxt)
{
	fstream InputStage;
	InputStage.open(StageTxt);
	string data[12];
	string file;
	//LAST SCORE
	getline(InputStage, file, '\n');
	data[0] = file.substr(0, file.find('\t'));
	//data[0] = file;
	//IS_UNCLOCK
	getline(InputStage, file, '\n');
	data[1] = file.substr(0, file.find('\t'));
	//MAP
	for (int i = 0; i < 13; i++) {
		getline(InputStage, file);
		for (int j = 0; j < 20; j++) {
			switch (file[j])
			{
			case '0': map[i][j] = 0; break;		//0 = none, !0 = gameArea
			case '2': map[i][j] = 2; break;		//2 = normalArea
			case '3': map[i][j] = 3; break;		//3 = singleJelly
			case '4': map[i][j] = 4; break;		//4 = doubleJelly
			case '1': map[i][j] = 1; break;		//1 = candy spawning area
			}
		}
	}
	//ETC
	for (int i = 2; i < 12; i++) {
		getline(InputStage, file, '\n');
		data[i] = file.substr(0, file.find('\t'));
	}
	InputStage.close();
	lastHighScore = stoi(data[0]);
	isUnlock = stoi(data[1]);
	scoreOne = stoi(data[2]);
	scoreTwo = stoi(data[3]);
	scoreThree = stoi(data[4]);
	vertical = stoi(data[5]);
	horizontal = stoi(data[6]);
	pack = stoi(data[7]);
	chocolate = stoi(data[8]);
	maxStep = stoi(data[9]);
	candyType = stoi(data[10]);
	mode = stoi(data[11]);
}

int game_framework::Stage::GetScoreOne()
{
	return scoreOne;
}

int game_framework::Stage::GetScoreTwo()
{
	return scoreTwo;
}

int game_framework::Stage::GetScoreThree()
{
	return scoreThree;
}

int game_framework::Stage::GetVertical()
{
	return vertical;
}

int game_framework::Stage::GetHorizontal()
{
	return horizontal;
}

int game_framework::Stage::GetPack()
{
	return pack;
}

int game_framework::Stage::GetChocolate()
{
	return chocolate;
}

int game_framework::Stage::GetCandyType()
{
	return candyType;
}

int game_framework::Stage::GetLastScoreHistory()
{
	return lastHighScore;
}

int game_framework::Stage::GetMaxStep()
{
	return maxStep;
}

int game_framework::Stage::GetMode()
{
	return mode;
}

bool game_framework::Stage::IsUnlock()
{
	return isUnlock == 1 ? true : false;
}

