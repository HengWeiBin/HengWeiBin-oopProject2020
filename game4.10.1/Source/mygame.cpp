/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_JELLY.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <set>
#include <string.h>
#include <string>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame* g)
		: CGameState(g), playBtnClicked(false)
	{
	}

	void CGameStateInit::OnInit()
	{
		ShowLoading();
		//
		// 開始載入資料
		//
		background.LoadBitmap("Bitmaps\\InitBackground.bmp");
		// Load play button
		int playBtnBmp[] = { IDB_PLAYBUTTON_1, IDB_PLAYBUTTON_2, IDB_PLAYBUTTON_3, IDB_PLAYBUTTON_4,
							 IDB_PLAYBUTTON_5, IDB_PLAYBUTTON_6, IDB_PLAYBUTTON_7, IDB_PLAYBUTTON_8,
							 IDB_PLAYBUTTON_9, IDB_PLAYBUTTON_10, IDB_PLAYBUTTON_11, IDB_PLAYBUTTON_12
		};

		for (int i = 0; i < 12; i++)
		{
			playButton.AddBitmap(playBtnBmp[i], RGB(0, 0, 0));
		}

		playButton.SetDelayCount(4);
		clickedPlayButton.LoadBitmap("Bitmaps\\PlayButtonClicked.bmp", RGB(0, 0, 0));
		playButTopLX = SIZE_X / 2 - playButton.Width() / 2;
		playButTopLY = SIZE_Y / 5 * 4 - playButton.Height();
		playButBotRX = SIZE_X / 2 + playButton.Width() / 2;
		playButBotRY = SIZE_Y / 5 * 4;
		//Load tiffy
		int TiffyBitmap[10] = { IDB_TIFFY_0, IDB_TIFFY_1, IDB_TIFFY_2, IDB_TIFFY_3, IDB_TIFFY_4,
								IDB_TIFFY_5, IDB_TIFFY_6, IDB_TIFFY_7, IDB_TIFFY_8, IDB_TIFFY_9
		};

		for (int i = 0; i < 10; i++)
		{
			tiffy.AddBitmap(TiffyBitmap[i], RGB(255, 255, 255));
		}

		for (int i = 8; i > 0; i--)
		{
			tiffy.AddBitmap(TiffyBitmap[i], RGB(255, 255, 255));
		}

		tiffy.SetDelayCount(4);
		//Load Toffee
		int ToffeeBitmap[6] = { IDB_TOFFEE_1, IDB_TOFFEE_2, IDB_TOFFEE_3, IDB_TOFFEE_4, IDB_TOFFEE_5, IDB_TOFFEE_6 };

		for (int i = 0; i < 6; i++)
		{
			toffee.AddBitmap(ToffeeBitmap[i], RGB(255, 255, 255));
		}

		for (int i = 5; i > 0; i--)
		{
			toffee.AddBitmap(ToffeeBitmap[i], RGB(255, 255, 255));
		}

		toffee.SetDelayCount(4);

		int CandyCrush[] = { IDB_CANDY_CRUSH_1, IDB_CANDY_CRUSH_2, IDB_CANDY_CRUSH_3, IDB_CANDY_CRUSH_4, IDB_CANDY_CRUSH_5, IDB_CANDY_CRUSH_6, 
						IDB_CANDY_CRUSH_8, IDB_CANDY_CRUSH_10, IDB_CANDY_CRUSH_12, IDB_CANDY_CRUSH_14, IDB_CANDY_CRUSH_16, IDB_CANDY_CRUSH_18, 
						IDB_CANDY_CRUSH_20, IDB_CANDY_CRUSH_21, IDB_CANDY_CRUSH_22, IDB_CANDY_CRUSH_23,
						IDB_CANDY_CRUSH_22, IDB_CANDY_CRUSH_21, IDB_CANDY_CRUSH_20, IDB_CANDY_CRUSH_19, IDB_CANDY_CRUSH_18, IDB_CANDY_CRUSH_17, 
						IDB_CANDY_CRUSH_16, IDB_CANDY_CRUSH_15, IDB_CANDY_CRUSH_14, IDB_CANDY_CRUSH_13, IDB_CANDY_CRUSH_12, IDB_CANDY_CRUSH_11,
						IDB_CANDY_CRUSH_10, IDB_CANDY_CRUSH_9, IDB_CANDY_CRUSH_7, IDB_CANDY_CRUSH_7, IDB_CANDY_CRUSH_6, 
						IDB_CANDY_CRUSH_7, IDB_CANDY_CRUSH_9,IDB_CANDY_CRUSH_10, IDB_CANDY_CRUSH_11, IDB_CANDY_CRUSH_12, IDB_CANDY_CRUSH_13, 
						IDB_CANDY_CRUSH_14, IDB_CANDY_CRUSH_15, IDB_CANDY_CRUSH_16, IDB_CANDY_CRUSH_17, IDB_CANDY_CRUSH_18, IDB_CANDY_CRUSH_19,
						IDB_CANDY_CRUSH_19, IDB_CANDY_CRUSH_18, IDB_CANDY_CRUSH_17, IDB_CANDY_CRUSH_16, IDB_CANDY_CRUSH_15 };
		for (int i = 0; i < 50; i++) {
			candyCrush.AddBitmap(CandyCrush[i], RGB(255, 255, 255));
		}
		candyCrush.SetDelayCount(1);
		candyCrush.SetCycle(false);
	}

	void CGameStateInit::OnBeginState()
	{
		candyCrush.Reset();
		playBtnClicked = false;
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';

		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);							// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)									// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (point.x >= playButTopLX && point.y >= playButTopLY && point.x <= playButBotRX && point.y <= playButBotRY)
		{
			playBtnClicked = true;
		}
		else playBtnClicked = false;
	}

	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if (point.x >= playButTopLX && point.y >= playButTopLY && point.x <= playButBotRX && point.y <= playButBotRY)
		{
			GotoGameState(GAME_STATE_MENU);		// 切換至GAME_STATE_RUN
		}
		else playBtnClicked = false;
	}

	void CGameStateInit::OnShow()
	{
		// 貼上背景
		background.SetTopLeft(0, 0);
		background.ShowBitmap();

		//貼上Play Button
		if (playBtnClicked)
		{
			clickedPlayButton.SetTopLeft(SIZE_X / 2 - playButton.Width() / 2, SIZE_Y / 5 * 4 - playButton.Height());
			clickedPlayButton.ShowBitmap();
		}
		else
		{
			playButton.SetTopLeft(SIZE_X / 2 - playButton.Width() / 2, SIZE_Y / 5 * 4 - playButton.Height());
			playButton.OnShow();
		}

		tiffy.SetTopLeft(95, 400);
		tiffy.OnShow();
		toffee.SetTopLeft(700, 60);
		toffee.OnShow();
		candyCrush.SetTopLeft(250, -50);
		candyCrush.OnShow();
	}

	void CGameStateInit::OnMove()
	{
		candyCrush.OnMove();
		if (!playBtnClicked) playButton.OnMove();
		tiffy.OnMove();
		toffee.OnMove();
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
		stageNum = 0;
	}

	void CGameStateOver::OnMove()
	{
		counter--;

		if (counter < 0)
			GotoGameState(GAME_STATE_MENU);
	}

	void CGameStateOver::OnBeginState()
	{

		//stageNum = stage - 1;
		counter = 60 * 5; // 5 seconds

		currentStage = current_stage;
		currentScore = (int)stages[current_stage - 1]->GetCurrentScore();
	}

	void CGameStateOver::OnInit()
	{

		//currentScore.SetType(3);
		//currentStage.SetType(3);

		//load background
		backgroundOver.LoadBitmap("Bitmaps/inGameBG1.bmp");

		//load score board
		scoreBoardOver.LoadBitmap("Bitmaps/score_state_over.bmp", RGB(0, 0, 0));

		//load star
		redStar.LoadBitmap("Bitmaps/RedStar.bmp", RGB(251, 230, 239));
		greenStar.LoadBitmap("Bitmaps/GreenStar.bmp", RGB(251, 230, 239));
		yellowStar.LoadBitmap("Bitmaps/YellowStar.bmp", RGB(251, 230, 239));
		emptyStar.LoadBitmap("Bitmaps/ContainerStar.bmp", RGB(251, 230, 239));

		//load button
		exitButton.LoadBitmap("Bitmaps/ExitButton.bmp", RGB(255, 255, 255));
		nextButton.LoadBitmap("Bitmaps/NextButton.bmp", RGB(251, 230, 239));
		retryButton.LoadBitmap("Bitmaps/RetryButton.bmp", RGB(251, 230, 239));
	}
	int CGameStateOver::GetDigit(int n)
	{
		n = abs(n);
		int digit = 0;
		while (n > 0)
		{
			digit++;
			n /= 10;
		}
		return digit == 0 ? 1 : digit;
	}
	void CGameStateOver::ShowStars(int amount, int xStar, int yStar)
	{
		if (amount == 3)
		{
			yellowStar.SetTopLeft(xStar, yStar);
			yellowStar.ShowBitmap();
			yellowStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
			yellowStar.ShowBitmap();
			yellowStar.SetTopLeft(xStar + 220 + 40, yStar);
			yellowStar.ShowBitmap();
		}
		else if (amount >= 1)
		{
			redStar.SetTopLeft(xStar, yStar);
			redStar.ShowBitmap();

			if (amount == 2)
			{
				greenStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
				greenStar.ShowBitmap();
			}
			else {
				emptyStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
				emptyStar.ShowBitmap();
			}
			emptyStar.SetTopLeft(xStar + 220 + 40, yStar);
			emptyStar.ShowBitmap();
		}
		else {
			emptyStar.SetTopLeft(xStar, yStar);
			emptyStar.ShowBitmap();
			emptyStar.SetTopLeft(xStar + 110 + 20, yStar - 20);
			emptyStar.ShowBitmap();
			emptyStar.SetTopLeft(xStar + 220 + 40, yStar);
			emptyStar.ShowBitmap();
		}
	}
	void CGameStateOver::OnShow()
	{
		//show background
		backgroundOver.SetTopLeft(0, 0);
		backgroundOver.ShowBitmap();

		//show score board
		scoreBoardOver.SetTopLeft((backgroundOver.Width() / 2) - (scoreBoardOver.Width() / 2), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2));
		scoreBoardOver.ShowBitmap();

		//show stage 
		currentStage.SetTopLeft((backgroundOver.Width() / 2) + 60, (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 90);
		currentStage.ShowBitmap();

		//show star
		int xStar = (backgroundOver.Width() / 2) - (370 / 2);
		int yStar = (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 205;
		if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreThree())
		{	//Show 3 yellow star if current score higher than star three
			ShowStars(3, xStar, yStar);
		}
		else if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreTwo())
		{	//Show 2 star if current score higher than star two
			ShowStars(2, xStar, yStar);
		}
		else if (stages[current_stage]->GetCurrentScore() >= stages[current_stage]->GetScoreOne())
		{	//Show 1 star if current score higher than star one
			ShowStars(1, xStar, yStar);
		}
		else if (stages[current_stage]->GetCurrentScore() < stages[current_stage]->GetScoreOne())
		{	//Show 0 star if current score higher than star one
			ShowStars(1, xStar, yStar);
		}

		//show score
		currentScore.SetTopLeft((backgroundOver.Width() / 2) - (50 * GetDigit(currentScore.GetInteger()) / 2), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 400);
		currentScore.ShowBitmap();

		//show button
		exitButton.SetTopLeft(scoreBoardOver.Left() + scoreBoardOver.Width() - exitButton.Width(), scoreBoardOver.Top());
		exitButton.ShowBitmap();
		retryButton.SetTopLeft((backgroundOver.Width() / 2) - 10 - nextButton.Width(), (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 530);
		retryButton.ShowBitmap();
		nextButton.SetTopLeft((backgroundOver.Width() / 2) + 10, (backgroundOver.Height() / 2) - (scoreBoardOver.Height() / 2) + 530);
		nextButton.ShowBitmap();



		/*
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(SIZE_X / 2 - 100, SIZE_Y / 2 - 50, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		*/
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
	{}

	CGameStateRun::~CGameStateRun()
	{}

	void CGameStateRun::OnBeginState()
	{
		background.SetTopLeft(0, 0);						// 設定背景的起始座標
		CAudio::Instance()->Play(AUDIO_JELLY, true);		// 撥放 MIDI
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		//
		// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		gameArea.OnMove();

		if (gameArea.IsGameOver())
		{
			GotoGameState(GAME_STATE_OVER);
			CAudio::Instance()->Stop(AUDIO_JELLY);
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		background.LoadBitmap("Bitmaps\\inGameBG1.bmp");// 載入背景的圖形

		//載入游戲音效
		CAudio::Instance()->Load(AUDIO_JELLY, "sounds\\MovesJellyLevels.mp3");
		CAudio::Instance()->Load(AUDIO_NEG_SWAP, "sounds\\negative_switch_sound1.wav");
		CAudio::Instance()->Load(AUDIO_SWAP, "sounds\\switch_sound1.wav");
		CAudio::Instance()->Load(AUDIO_SUPER_CREATE, "sounds\\colour_bomb_created.wav");
		CAudio::Instance()->Load(AUDIO_LINE_CREATE, "sounds\\striped_candy_created1.wav");
		CAudio::Instance()->Load(AUDIO_PACK_CREATE, "sounds\\wrapped_candy_created1.wav");
		CAudio::Instance()->Load(AUDIO_POWER_ALL, "sounds\\colour_bomb1.wav");
		CAudio::Instance()->Load(AUDIO_SQUARE_REMOVE1, "sounds\\square_removed1.wav");
		CAudio::Instance()->Load(AUDIO_SQUARE_REMOVE2, "sounds\\square_removed2.wav");
		CAudio::Instance()->Load(AUDIO_LINE_BLAST, "sounds\\line_blast1.wav");
		CAudio::Instance()->Load(AUDIO_CANDY_LAND1, "sounds\\candy_land1.wav");
		CAudio::Instance()->Load(AUDIO_CANDY_LAND2, "sounds\\candy_land2.wav");
		CAudio::Instance()->Load(AUDIO_CANDY_LAND3, "sounds\\candy_land3.wav");
		CAudio::Instance()->Load(AUDIO_CANDY_LAND4, "sounds\\candy_land4.wav");

		for (int i = 0; i < 12; i++)
		{
			char sound[30] = { 0 };
			sprintf(sound, "sounds\\combo_sound%d.wav", i + 1);
			CAudio::Instance()->Load(AUDIO_COMBO1 + i, sound);
		}

		gameArea.LoadBitmap();
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const int KEY_TAB = 0x09;

		if (nChar == KEY_TAB)
		{
			CAudio::Instance()->Stop(AUDIO_JELLY);
			GotoGameState(GAME_STATE_MENU);
		}
		
		gameArea.OnKeyDown(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		gameArea.OnKeyUp(nChar, nRepCnt, nFlags);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		gameArea.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		gameArea.OnLButtonUp(nFlags, point);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{}


	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		//
		background.ShowBitmap();			// 貼上背景圖
		gameArea.OnShow();
	}

	CGameStateMenu::CGameStateMenu(CGame *g)
		: CGameState(g), totalStage(9), drag(false), mouseDisplayment(0), inertia(0), goldFinger(false)
	{
		IsMovingUp = false; IsMovingDown = false;
		MAX_Y = 0; MIN_Y = -3600;
		sy = -3600;

		int Pos[][2] = { {270,4030},{495,3980},{530,3850},{320,3870},{135,3910},
						 {135,3750},{340,3690},{570,3720},{770,3800},{960,3840},
						 {1085,3750},{1010,3600},{760,3540},{520,3590},{280,3585} };
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 2; j++) {
				StagePos[i][j] = Pos[i][j];
			}
		}
	}

	CGameStateMenu::~CGameStateMenu()
	{
		for (unsigned i = 0; i < stages.size(); i++)
			delete stages[i];
	}

	void CGameStateMenu::OnInit()
	{
		woodBackgourd.LoadBitmap("Bitmaps\\WoodBackground.bmp");
		menuBackground.LoadBitmap("Bitmaps\\stage_map.bmp");
		stageNum.SetType(1);

		int StageButton[5] = { IDB_STAGE_BUTTON_BLUE, IDB_STAGE_BUTTON_RED, IDB_STAGE_BUTTON_GREEN, IDB_STAGE_BUTTON_YELLOW, IDB_STAGE_BUTTON_GREY };
		//unlock icon
		for (int i = 0; i < 5; i++) {
			stageButton[i].LoadBitmap(StageButton[i], RGB(255, 255, 255));
		}

		CAudio::Instance()->Load(AUDIO_STAGE, "sounds\\Overworld_Level_Select.mp3");

		//star icon
		star1.LoadBitmap("Bitmaps\\SmallRedStar.bmp", RGB(255, 255, 255));
		star2.LoadBitmap("Bitmaps\\SmallGreenStar.bmp", RGB(255, 255, 255));
		star3.LoadBitmap("Bitmaps\\SmallYellowStar.bmp", RGB(255, 255, 255));

		//load stage
		for (int i = 0; i < totalStage + 1; i++) {
			stages.push_back(new Stage(i + 1));
			stages[i]->LoadStage();
		}


	}

	void CGameStateMenu::OnBeginState()
	{
		CAudio::Instance()->Play(AUDIO_STAGE, true);
	}

	void CGameStateMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;

		if (nChar == KEY_UP) IsMovingUp = true;

		if (nChar == KEY_DOWN) IsMovingDown = true;

		if (nChar == VK_F1) goldFinger = true;
	}

	void CGameStateMenu::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_ESC = 27;

		if (nChar == KEY_UP) IsMovingUp = false;

		if (nChar == KEY_DOWN) IsMovingDown = false;

		if (nChar == VK_F1) goldFinger = false;

		if (nChar == KEY_ESC)
		{
			CAudio::Instance()->Stop(AUDIO_STAGE);
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateMenu::OnLButtonDown(UINT nFlags, CPoint point)
	{
		clickX = point.x;
		clickY = point.y;
		clickSY = sy;
		drag = true;
	}

	void CGameStateMenu::OnLButtonUp(UINT nFlags, CPoint point)
	{
		drag = false;

		int x = point.x;
		int y = point.y - sy;
		int StagePos[][2] = { {270,4030},{495,3980},{530,3850},{320,3870},{135,3910},
							  {135,3750},{340,3690},{570,3720},{770,3800},{960,3840},
							  {1085,3750},{1010,3600},{760,3540},{520,3590},{280,3585} };
		for (int i = 0; i < totalStage; i++) {
			if (StagePos[i][0] < x && x < (StagePos[i][0] + 60) && StagePos[i][1] < y && (y < StagePos[i][1] + 60))
			{
				if (stages[i]->IsUnlock() || goldFinger)
				{
					current_stage = i + 1;
					gameArea.LoadStage(stages, i);
					CAudio::Instance()->Stop(AUDIO_STAGE);
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}
	}

	void CGameStateMenu::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (drag)
		{
			int displayment = point.y - clickY;
			sy = clickSY + displayment;
			inertia = displayment < 0 ? -20 : 20;
		}
	}

	void CGameStateMenu::OnRButtonDown(UINT nFlags, CPoint point)
	{}

	void CGameStateMenu::OnRButtonUp(UINT nFlags, CPoint point)
	{}

	void CGameStateMenu::SetMovingUp(bool status)
	{
		if (status && sy <= MAX_Y)
			sy += 5;
	}

	void CGameStateMenu::SetMovingDown(bool status)
	{
		if (status && sy >= MIN_Y)
			sy -= 5;
	}

	void CGameStateMenu::OnMove()
	{
		SetMovingUp(IsMovingUp);
		SetMovingDown(IsMovingDown);
		if (!drag && inertia > 0) sy += inertia--;
		else if (!drag && inertia < 0) sy += inertia++;
	}

	int CGameStateMenu::GetDigit(int n)
	{
		n = abs(n);
		int digit = 0;
		while (n > 0)
		{
			digit++;
			n /= 10;
		}
		return digit == 0 ? 1 : digit;
	}

	void CGameStateMenu::OnShow()
	{
		//show wood background
		woodBackgourd.SetTopLeft(0, 0);
		woodBackgourd.ShowBitmap();

		//show stage map
		if (sy < MAX_Y && sy < MIN_Y)
			sy = -3600;
		if (sy > MAX_Y && sy > MIN_Y)
			sy = 0;
		menuBackground.SetTopLeft(40, sy);
		menuBackground.ShowBitmap();

		//show unlock icon
		for (int i = 0; i < totalStage; i++)
		{
			int xStar = StagePos[i][0] - 10, xButton = StagePos[i][0] - 5;
			int yStar = StagePos[i][1] + sy + 65, yButton = StagePos[i][1] - 3 + sy;
			stageNum.SetInteger(i + 1);
			if (stages[i]->IsUnlock())
			{
				if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreThree())
				{	//Show yellow button if history score higher than star three
					ShowStageButton(3, i, xButton, yButton);
					ShowStars(3, xStar, yStar);
				}
				else if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreTwo())
				{	//Show green button if history star three > score higher > star two
					ShowStageButton(2, i, xButton, yButton);
					ShowStars(2, xStar, yStar);
				}
				else if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreOne())
				{	//Show red button if star two > history score > star one 
					ShowStageButton(1, i, xButton, yButton);
					ShowStars(1, xStar, yStar);
				}
				else if (stages[i]->GetLastScoreHistory() < stages[i]->GetScoreOne())
				{	//Show blue button if the stage is unlocked but no history score
					ShowStageButton(0, i, xButton, yButton);
				}
			}	//Show gray button if the stage is locked
			else ShowStageButton(4, i, xButton, yButton);
		}
	}

	void CGameStateMenu::ShowStageButton(int stageBtn, int stage, int xButton, int yButton)
	{
		stageButton[stageBtn].SetTopLeft(xButton, yButton);
		stageButton[stageBtn].ShowBitmap();

		if (stages[stage]->IsUnlock())
		{
			stageNum.SetTopLeft(xButton + ((stageButton[stageBtn].Width() / 2) - (10 * GetDigit(stage) / 2)), yButton + (stageButton[stageBtn].Height() / 4));
			stageNum.ShowBitmap();
		}
	}

	void CGameStateMenu::ShowStars(int amount, int xStar, int yStar)
	{
		if (amount == 3)
		{
			star3.SetTopLeft(xStar, yStar);
			star3.ShowBitmap();
			star3.SetTopLeft(xStar + 30, yStar + 5);
			star3.ShowBitmap();
			star3.SetTopLeft(xStar + 60, yStar);
			star3.ShowBitmap();
		}
		else if (amount >= 1)
		{
			star1.SetTopLeft(xStar, yStar);
			star1.ShowBitmap();

			if (amount == 2)
			{
				star2.SetTopLeft(xStar + 30, yStar + 5);
				star2.ShowBitmap();
			}
		}
	}
}