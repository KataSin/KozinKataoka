#include "GamePlay.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"

#include "../math/Math.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../game/Random.h"

#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include "../actor/ParticleManager/ParticleManager.h"
#include "../actor/ID.h"
#include "../actor/StageLineManager/StageLine/StageLine.h"
#include "../actor/Pool/Pool.h"
#include "../UIactor/GameTimer/GameTimerUI.h"
#include "../UIactor/GameFrameUI/GameFrameUI.h"
#include "../UIactor/ResultUI/ResultUI.h"
#include "../UIactor/GamePlayFontUI/GamePlayFontUI.h"
//コンストラクタ
GamePlay::GamePlay(GameManager& gameManager) :
	mGameManager(&gameManager),
	mRandCount(0),
	mPlayerNum(0)
{
	mGamePlayManager = std::make_shared<GamePlayManager>(wo);
}

//デストラクタ
GamePlay::~GamePlay()
{

}

//開始
void GamePlay::Initialize()
{
	//フラグ初期化
	mIsEnd = false;
	mIsEndRanund = false;
	mStartFontFlag = true;
	mFontFlag = true;
	//プレイ人数設定
	mPlayerNum = mGameManager->GetPlayerNum();
	wo.SetPlayerNum(mPlayerNum);
	//パッド情報をワールドに設定
	wo.SetPadNum(mGameManager->GetPlayerPad());
	//次もゲームプレイに移行
	mNextScene = Scene::GamePlay;
	//ラウンドを設定
	mEndRaundCount = mGameManager->GetRaundCount();
	//ステージを追加
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	//タイマー設定
	auto gameTimer = std::make_shared<GameTimerUI>(wo, Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 2.0f);
	//タイマーを追加
	wo.UIAdd(UI_ID::GAMETIMER_UI, gameTimer);
	mGameTimer = gameTimer.get();
	//ゲームフレームを追加
	wo.UIAdd(UI_ID::GAMEFRAME_UI, std::make_shared<GameFrameUI>(wo, Vector2::Zero,mPlayerNum));
	auto font = std::make_shared<GamePlayFontUI>(wo);
	//フォントマネージャーを追加
	wo.UIAdd(UI_ID::FONT_UI, font);
	fontUi = static_cast<GamePlayFontUI*>(font.get());
	//最初に出すフォントを設定
	fontUi->StartFont(SPRITE_ID::YO_I_FONT_SPRITE);

	//SetLightEnable(true);
	//SetLightDirection(Vector3::ToVECTOR(Vector3(-1, -1, -1)));

	//勝ったプレイヤー初期化
	mWinPlayer = PLAYER_NUMBER::PLAYER_NULL;
	//プレイヤー操作不能
	wo.SetInputPlayer(false);
	//支所はタイマーが動いていない
	gameTimer->StopTimer(true);
}

void GamePlay::Update()
{
	//よーいフォントが終わったらプレイヤーの操作開始
	if (fontUi->GetEndFont(SPRITE_ID::YO_I_FONT_SPRITE) && mStartFontFlag) {
		fontUi->StartFont(SPRITE_ID::DON_SPRITE, 8.0f);
		wo.SetInputPlayer(true);
		mGameTimer->StopTimer(false);
		mStartFontFlag = false;
	}

	if (mIsEndRanund) {
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
			mIsEnd = true;
			mRandCount++;
			//全ラウンド終わってたらリザルトへ
			if (mRandCount >= mEndRaundCount) {
				mNextScene = Scene::Result;
				//勝った人たちをセット
				mGameManager->SetPlayerRank(mGamePlayManager->IsFinalWinPlayer());
			}
		}
	}
	else
	{
		if (mGamePlayManager->EndRaund()) {
			if (mFontFlag) {
				mGameTimer->StopTimer(true);
				//勝ったプレイヤーを入れる
				mWinPlayer = mGamePlayManager->IsWinPlayer();
				//そこまで表示
				fontUi->StartFont(SPRITE_ID::SOKOMADE_FONT_SPRITE);
				mFontFlag = false;
			}
			else if (fontUi->GetEndFont(SPRITE_ID::SOKOMADE_FONT_SPRITE)) {
				//そこまで表示終わったらリザルト画像を表示
				wo.UIAdd(UI_ID::RESULT_UI, std::make_shared<ResultUI>(wo, *mGamePlayManager.get(), mWinPlayer));
				mIsEndRanund = true;
				mFontFlag = true;
			}
		}
		else if (mGamePlayManager->TimeUp()) {
			if (mFontFlag) {
				mGameTimer->StopTimer(true);
				//そこまで表示
				fontUi->StartFont(SPRITE_ID::SOKOMADE_FONT_SPRITE);
				mFontFlag = false;
			}
			else if (fontUi->GetEndFont(SPRITE_ID::SOKOMADE_FONT_SPRITE)) {
				//引き分け表示(ずっと)
				fontUi->StartFont(SPRITE_ID::HIKIWAKE_FONT_SPRITE, true);
				mFontFlag = true;
				mIsEndRanund = true;
			}
		}
	}
	wo.Update();
}

//描画
void GamePlay::Draw()
{
	//カメラ分割の設定
	SetCamera(mPlayerNum);
	//UI表示のため設定を初期化
	SetCameraScreenCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	SetDrawArea(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//UIは一回だけdrawでOK
	wo.UIDraw();
	DrawFormatString(0, 368, GetColor(255, 255, 255), "ゲームプレイシーン");
	//DrawSphere3D(Vector3::ToVECTOR(Vector3(0,0,0)), 1.0f, 20, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

//終了しているか？
bool GamePlay::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene GamePlay::Next() const
{
	return mNextScene;
}

void GamePlay::End()
{
	//リザルトだったら0にする＆勝ち数リセット
	if (mNextScene == Scene::Result) {
		mRandCount = 0;
		mGamePlayManager->ResetWin();
	}
	wo.Clear();
}

void GamePlay::SetCamera(int num)
{
	switch (num)
	{
	case 2:
	{
		//カメラの描写の位置を設定
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//カメラの描写位置を設定し終わった後にプレイヤーごとのUIをUpdateしてDrawをしなくてはいけない
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		wo.Draw();
		break;
	}
	case 3:
	{
		//カメラの描写の位置を設定
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//カメラの描写位置を設定し終わった後にプレイヤーごとのUIをUpdateしてDrawをしなくてはいけない
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
		wo.Draw();
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
		break;
	}
	case 4:
	{
		//カメラの描写の位置を設定
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera(num);
		//カメラの描写位置を設定し終わった後にプレイヤーごとのUIをUpdateしてDrawをしなくてはいけない
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
		wo.Draw();
		dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_4).get())->SetCamera(num);
		wo.UpdateUI(PLAYER_NUMBER::PLAYER_4);
		wo.Draw();
		break;
	}

	}
}
