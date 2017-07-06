#include "GameFrame.h"
#include "../Def.h"
#include <DxLib.h>
#include "../scene/SceneManager.h"
#include "../scene/GamePlay.h"
#include "../scene/TitleScene.h"

bool GameFrame::mIsEnd = false;

void GameFrame::Run()
{
	SetAlwaysRunFlag(TRUE);
	SetUseBackCulling(TRUE);
	SetLogDrawOutFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT_DEPTH, REFRESH_RATE);
	
	SetBackgroundColor(0, 0, 0);
	SetMainWindowText(GAMENAME);
	SetZBufferBitDepth(24);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetWaitVSyncFlag(TRUE);
	//SetWindowSizeExtendRate(0.5f);
	//ウィンドゥモード
	ChangeWindowMode(TRUE);

	//フォントの読み込み
																																																																																																																																																																																																																																																																																																																					LPCSTR font_path = "res/TextFile/FontDate.ttf"; // 読み込むフォントファイルのパス
																																																																																																																																																																																																																																																																																																																					if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	ChangeFont("PixelMplus10");

	if (DxLib_Init() == -1)
	{
		DxLib_End();
		return;
	}
	
	SetDrawScreen(DX_SCREEN_BACK);

	Initialize();

	RECT screen = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

	bool isBegin = false;

	while (ProcessMessage() == 0 && !IsEnd())
	{
		Update(); 

		ClearDrawScreen(&screen);
		ClearDrawScreenZBuffer(&screen);

		Draw();
		
		ScreenFlip();
	}
	//フォントクローズ
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}
	else {
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
	Finalize();
	DxLib_End();
}

bool GameFrame::IsEnd()
{
	return mIsEnd;
}

void GameFrame::GameEnd()
{
	mIsEnd = true;
}