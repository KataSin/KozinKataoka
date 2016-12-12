#include "GamePlay.h"
#include "../AllInclude.h"
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
#include "../UIactor/fadePanel/FadePanel.h"
#include "../game/Random.h"

#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include "../actor/ParticleManager/ParticleManager.h"
#include "../actor/ID.h"
#include "../actor/StageLineManager/StageLine/StageLine.h"
#include "../actor/Pool/Pool.h"
//コンストラクタ
GamePlay::GamePlay()
{

}

//デストラクタ
GamePlay::~GamePlay()
{

}

//開始
void GamePlay::Initialize()
{
	test = 0;
	mIsEnd = false;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));

	SetLightEnable(true);
	SetLightDirection(Vector3::ToVECTOR(Vector3(-1, -1, -1)));

	//ライトの設定(不具合あり)
	//light.SetDirectionalLight("GamePlayLight", Vector3(-1, -1, -1));
}

void GamePlay::Update()
{
	wo.Update();
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}

}

//描画
void GamePlay::Draw()
{
	//カメラの描写の位置を設定
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_1).get())->SetCamera();
	//カメラの描写位置を設定し終わった後にプレイヤーごとのUIをUpdateしてDrawをしなくてはいけない
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_2).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_2);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_3).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_3);
	wo.Draw();
	dynamic_cast<CameraActor*>(wo.GetCamera(PLAYER_NUMBER::PLAYER_4).get())->SetCamera();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_4);
	wo.Draw();

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
	return Scene::Title;
}

void GamePlay::End()
{
	wo.Clear();
}