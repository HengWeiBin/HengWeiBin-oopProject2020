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

game_framework::Stage::Stage(int files)
{
	scoreOne = 0; scoreTwo = 0; scoreThree = 0;		//Target score for three star
	vertical = 0; horizontal = 0; pack = 0; chocolate = 0;	//total special candy spawn onInit
	candyType = 0;								//Max candy type in this game
	lastHighScore = 0;							//History highest score
	maxStep = 0;
	mode = 0;
	currentScore = 0;
	currentStage = files;
	isUnlock = 0;
	for (int i = 0; i < 2; i++)
		stageTxt[i] = "Stages\\cnt_stage" + to_string(files + i) + ".txt";
}

void game_framework::Stage::LoadStage()
{
	fstream InputStage;
	InputStage.open(stageTxt[0]);
	if (!InputStage.is_open())
	{
		char fileName[200] = "\nOpen file failed! file: ";
		strcat(fileName, stageTxt[0].c_str());
		strcat(fileName, "\nReason: ");
		GAME_ASSERT(0, strcat(fileName, strerror(errno)));
	}
	string data[13];
	string file;
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
	for (int i = 2; i < 13; i++) {
		getline(InputStage, file, '\n');
		data[i] = file.substr(0, file.find('\t'));
	}
	//LAST SCORE
	getline(InputStage, file, '\n');
	data[0] = file.substr(0, file.find('\t'));
	//data[0] = file;
	//IS_UNCLOCK
	getline(InputStage, file, '\n');
	data[1] = file.substr(0, file.find('\t'));

	lastHighScore = stod(data[0]);
	isUnlock = stoi(data[1]);
	scoreOne = stod(data[2]);
	scoreTwo = stod(data[3]);
	scoreThree = stod(data[4]);
	maxStep = stoi(data[5]);
	vertical = stoi(data[6]);
	horizontal = stoi(data[7]);
	pack = stoi(data[8]);
	chocolate = stoi(data[9]);
	candyType = stoi(data[10]);
	mode = stoi(data[11]);
	initcandy = stoi(data[12]);
	InputStage.close();
}

double game_framework::Stage::GetScoreOne()
{
	return scoreOne;
}

double game_framework::Stage::GetScoreTwo()
{
	return scoreTwo;
}

double game_framework::Stage::GetScoreThree()
{
	return scoreThree;
}
double game_framework::Stage::GetLastScoreHistory()
{
	return lastHighScore;
}
bool game_framework::Stage::IsUnlock()
{
	return isUnlock == 1 ? true : false;
}
double game_framework::Stage::GetCurrentScore()
{
	return currentScore;
}
int game_framework::Stage::GetCurrentStage()
{
	return currentStage;
}

/*function to re-create the cnt_stg.txt  
without last 2 lines(last score and isunlock*/
void game_framework::Stage::RemoveLine()
{

	for (int i = 0; i < 2; i++)
	{
		ifstream read(stageTxt[i]);
		ofstream myFile;
		string file;
		const char* data = stageTxt[i].data();
		myFile.open("temp.txt", ofstream::out);
		int line_no = 1, n = 26;
		while (!read.eof())
		{
			getline(read, file, '\n');
			line_no++;
			/*REMEMBER CHANGE THESE 2LINE, REMOVE THE +2 
			WHEN WE'RE DONE CREATE THE GAME_END_STATE*/
			if (line_no < n )
			{
				myFile << file;
				myFile << '\n';
			}
		}
		myFile.close();
		read.close();
		remove(data);
		rename("temp.txt", data);
	}

}

void game_framework::Stage::WriteBack()
{
		RemoveLine();
		ofstream myFile(stageTxt[0], ofstream::app);
		myFile << lastHighScore << "\t#LastScore";
		myFile << "\n1\t#IsUnlock";
		myFile.close();

		ofstream myFile1(stageTxt[1], ofstream::app);
		myFile1 << "0\t#LastScore";
		myFile1 << "\n1\t#IsUnlock";
		myFile1.close();
}
void game_framework::Stage::SetCurrentScore(int score)
{
	currentScore = score;
}

void game_framework::Stage::SetUnlock()
{
	isUnlock = true;
}

