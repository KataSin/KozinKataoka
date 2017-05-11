#include "Result.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
#include "../input/GamePad.h"
#include "../actor/ResultPlayer/ResultPlayer.h"
Result::Result(GameManager & gameManager) :
	mGameManager(&gameManager),
	mIsEnd(false),
	mStageMat(Matrix4::Identity),
	mDaiMat(Matrix4::Identity)
{


}

Result::~Result()
{
}

void Result::Initialize()
{
	//マトリクス設定
	mStageMat =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(Vector3::Zero);

	mDaiMat =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(Vector3(30, 10, 0));

	mSkyMat =
		Matrix4::Scale(5)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(Vector3::Zero);

	//カメラ設定
	Camera::GetInstance().Position.Set(Vector3(30, 90, -300));
	Camera::GetInstance().Target.Set(Vector3(30,80,0));
	Camera::GetInstance().Update();

	//プレイヤー追加
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<ResultPlayer>
		(wo,Vector3(30, 80, 0),MODEL_ID::PLAYER1_MODEL,ANIMATION::PLAYER_WIN2));
	mIsEnd = false;
}

void Result::Update()
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1)||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
		mIsEnd = true;
	}
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

}

void Result::Draw()
{
	wo.Draw();
	wo.UIDraw();
	Model::GetInstance().Draw(MODEL_ID::PLAYER1_MODEL, Vector3(30, 0, 30));
	Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, mStageMat);
	Model::GetInstance().Draw(MODEL_ID::DAI_MODEL, mDaiMat);
	//スカイボックス
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkyMat);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "リザルト");
	DrawFormatString(0, 64, GetColor(255, 255, 255), "勝ち,%d",(int)(mGameManager->GetPlayerRank().front()));
}

bool Result::IsEnd() const
{
	return mIsEnd;
}
Scene Result::Next() const
{
	return Scene::Title;
}

void Result::End()
{
	mGameManager->Initialize();
}
