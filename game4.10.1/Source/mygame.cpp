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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		//ShowInitProgress(0);	// 一開始的loading進度為0%
		ShowLoading();
		//
		// 開始載入資料
		//
		background.LoadBitmap("Bitmaps/InitBackground.bmp");
		playButton.LoadBitmap("Bitmaps/PlayButton.bmp", RGB(0, 0, 0));
		//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
		
		static int TiffyBitmap[10] = { IDB_TIFFY_0 , IDB_TIFFY_1 ,IDB_TIFFY_2,IDB_TIFFY_3,IDB_TIFFY_4,IDB_TIFFY_5,IDB_TIFFY_6,IDB_TIFFY_7,IDB_TIFFY_8,IDB_TIFFY_9 };
		for (int i = 0; i < 10; i++) {
			tiffy.AddBitmap(TiffyBitmap[i], RGB(255, 255, 255));
		}
		for (int i = 8; i > 0; i--)
		{
			tiffy.AddBitmap(TiffyBitmap[i], RGB(255, 255, 255));
		}
		tiffy.SetDelayCount(2);
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
	}

	void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
	{
		int playButTopLX = SIZE_X / 2 - playButton.Width() / 2;		//Top left of play button (x)
		int playButTopLY = SIZE_Y / 5 * 4 - playButton.Height();	//Top left of play button (y)
		int playButBotRX = SIZE_X / 2 + playButton.Width() / 2;		//Bottom right of play button(x)
		int playButBotRY = SIZE_Y / 5 * 4;							//Bottom right of play button(y)

		if (point.x >= playButTopLX && point.y >= playButTopLY && point.x <= playButBotRX && point.y <= playButBotRY)
		{
			GotoGameState(GAME_STATE_MENU);		// 切換至GAME_STATE_RUN
		}
	}

	void CGameStateInit::OnShow()
	{
		// 貼上背景
		background.SetTopLeft(0, 0);
		background.ShowBitmap();

		//貼上Play Button
		playButton.SetTopLeft(SIZE_X / 2 - playButton.Width() / 2, SIZE_Y / 5 * 4 - playButton.Height());
		playButton.ShowBitmap();

		tiffy.SetTopLeft(95, 400);
		tiffy.OnShow();
		tiffy.OnMove();
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_MENU);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		//ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		//ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
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
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
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
			GotoGameState(GAME_STATE_OVER);
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		//ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//

		background.LoadBitmap("Bitmaps/inGameBG1.bmp");					// 載入背景的圖形
		//
		// 完成部分Loading動作，提高進度
		//
		//ShowInitProgress(50);
		//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 繼續載入其他資料
		//
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
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
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
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		gameArea.OnLButtonDown(nFlags, point);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{	}

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

	CGameStateMenu::CGameStateMenu(CGame *g) : CGameState(g), totalStage(6), drag(false), mouseDisplayment(0)
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
		woodBackgourd.LoadBitmap("Bitmaps/WoodBackground.bmp");
		menuBackground.LoadBitmap("Bitmaps/stage_map.bmp");

		//tunlock ion
		unlockIcon.LoadBitmap("Bitmaps/Unlock_Level .bmp", RGB(255, 255, 255));
		CAudio::Instance()->Load(AUDIO_STAGE, "sounds\\Overworld_Level_Select.mp3");

		//star icon
		star1.LoadBitmap("Bitmaps/SmallRedStar.bmp", RGB(255, 255, 255));
		star2.LoadBitmap("Bitmaps/SmallGreenStar.bmp", RGB(255, 255, 255));
		star3.LoadBitmap("Bitmaps/SmallYellowStar.bmp", RGB(255, 255, 255));
		
		//load stage
		for (int i = 0; i < totalStage + 1; i++) {
			stages.push_back(new Stage(i+1));
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
		if (nChar == KEY_UP) {
			IsMovingUp=true;
		}
		if (nChar == KEY_DOWN) {
			IsMovingDown=true;
		}
	}

	void CGameStateMenu::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;

		if (nChar == KEY_UP) IsMovingUp = false;
		if (nChar == KEY_DOWN) IsMovingDown = false;
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
				if (stages[i]->IsUnlock())
				{
					gameArea.LoadStage(stages, i);
					CAudio::Instance()->Stop(AUDIO_STAGE);
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}
	}

	void CGameStateMenu::OnMouseMove(UINT nFlags, CPoint point)
	{
		if (drag) sy = clickSY + (point.y - clickY);
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
		for (int i = 0; i < totalStage; i++) {
			if (!stages[i]->IsUnlock()) {
				unlockIcon.SetTopLeft(StagePos[i][0] - 3, StagePos[i][1] + sy);
				unlockIcon.ShowBitmap();
			}
			else {
				int xTemp = StagePos[i][0] - 15;
				int yTemp = StagePos[i][1] + sy + 50;
				if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreOne())
				{
					star1.SetTopLeft(xTemp, yTemp);
					star1.ShowBitmap();
				}
				if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreTwo())
				{
					star2.SetTopLeft(xTemp + 30, yTemp);
					star2.ShowBitmap();
				}
				if (stages[i]->GetLastScoreHistory() >= stages[i]->GetScoreThree())
				{
					star3.SetTopLeft(xTemp + 60, yTemp);
					star3.ShowBitmap();
				}
			}
		}
	}
}