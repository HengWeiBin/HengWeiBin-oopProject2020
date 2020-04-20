
#include "stdafx.h"
#include <fstream>
#include <string>
#include "Stage.h"

using namespace std;

game_framework::Stage::Stage()
{
}

void game_framework::Stage::LoadStage()
{
	fstream InputStage;
	InputStage.open("\\Stages\\cnt_stage1.txt");
	string data[11];
	string file;
	//LAST SCORE
	getline(InputStage, file, '\n');
	data[0] = file.substr(0, file.find("#"));
	//MAP
	for (int i = 0; i < 13; i++) {
		getline(InputStage, file, '\n');
		for (int j = 0; j < 20; j++) {
			map[i][j] = file[j] == '1' ? 1 : 0;
		}
	}
	//ETC
	for (int i = 1; i < 10; i++) {
		getline(InputStage, file, '\n');
		data[i] = file.substr(0, file.find("#"));
	}
	double lastHighScore = stod(data[0]), scoreOne = stod(data[1]), scoreTwo = stod(data[2]), scoreThree = stod(data[3]), vertical = stod(data[4]), horizontal = stod(data[5]), pack = stod(data[6]), chocolate = stod(data[7]), maxStep = stod(data[8]), candyType = stod(data[9]), mode = stod(data[10]);
	InputStage.close();
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

