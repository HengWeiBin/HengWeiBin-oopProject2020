/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_JELLY.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "Candy.h"
#include "Stage.h"
#include "GameArea.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	#ifndef AUDIO_ID
	#define AUDIO_ID
	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_JELLY,
		AUDIO_NEG_SWAP, AUDIO_SWAP,
		AUDIO_SUPER_CREATE, AUDIO_LINE_CREATE, AUDIO_PACK_CREATE, AUDIO_POWER_ALL,
		AUDIO_SQUARE_REMOVE1, AUDIO_SQUARE_REMOVE2, AUDIO_LINE_BLAST,
		AUDIO_CANDY_LAND1, AUDIO_CANDY_LAND2, AUDIO_CANDY_LAND3, AUDIO_CANDY_LAND4,
		AUDIO_COMBO1, AUDIO_COMBO2, AUDIO_COMBO3, AUDIO_COMBO4, AUDIO_COMBO5, AUDIO_COMBO6,
		AUDIO_COMBO7, AUDIO_COMBO8, AUDIO_COMBO9, AUDIO_COMBO10, AUDIO_COMBO11, AUDIO_COMBO12
	};
	#endif

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap background, playButton;			// Candycrush starter background, play button
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////


	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);						//Run Default game
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	background;	// 背景圖
		GameArea		gameArea;	//游戲區
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

	class CGameStateMenu : public CGameState
	{
	public:
		CGameStateMenu(CGame *g);
		~CGameStateMenu();
		void OnInit();
		void OnBeginState();
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);				// handle keyboard behavior
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);					// handle keyboard behavior
		void OnLButtonDown(UINT nFlags, CPoint point);  // handle mouse behavior
		void OnLButtonUp(UINT nFlags, CPoint point);	// handle mouse behavior
		void OnMouseMove(UINT nFlags, CPoint point);	// handle mouse behavior 
		void OnRButtonDown(UINT nFlags, CPoint point);  // handle mouse behavior
		void OnRButtonUp(UINT nFlags, CPoint point);	// handle mouse behavior
		void SetMovingUp(bool status);
		void SetMovingDown(bool status);

	protected:
		void OnMove();
		void OnShow();

	private:
		void LoadStage();
		void StartGame();

		CMovingBitmap menuBackground, woodBackgourd;
		const int totalStage;
		vector<Stage> stages;
		int sy;
		int MAX_Y, MIN_Y;
		bool IsMovingUp, IsMovingDown;
	};
}