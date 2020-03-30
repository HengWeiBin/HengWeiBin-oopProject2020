
#include "stdafx.h"
#include "Stage.h"
#include <fstream>
#include <string>

using namespace std;

namespace game_framework
{
	Stage::Stage()
	{
	}

	void Stage::LoadStage()
	{
		fstream InputStage;
		InputStage.open("\\Stages\\cnt_stage1.txt");
		string data[9];
		string file;
		for (int i = 0; i < 13; i++) {
			getline(InputStage, file, '\n');
			for (int j = 0; j < 20; j++) {
				map[i][j] = file[j] == '1' ? 1 : 0;
			}
		}
		for (int i = 0; i < 8; i++) {
			getline(InputStage, file, '\n');
			data[i] = file.substr(0, file.find("#"));
		}
		double ScoreOne = stod(data[0]), ScoreTwo = stod(data[1]), ScoreThree = stod(data[2]), Vertical = stod(data[3]), Horizontal = stod(data[4]), TEffect = stod(data[5]), Chocolate = stod(data[6]), CandyType = stod(data[7]), LastScoreHistory = stod(data[8]);
		InputStage.close();
	}
}