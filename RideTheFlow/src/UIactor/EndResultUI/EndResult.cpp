#include "EndResult.h"
#include "../../world/IWorld.h"
#include "../../camera/Camera.h"
#include "../../actor/AnimActor/AnimActor.h"
#include "../../graphic/Model.h"
#include "../../graphic/Sprite.h"
#include "../../time/Time.h"
#include "../../game/Random.h"
#include "../../Def.h"
#include "../../math/Math.h"
#include "../../sound/Sound.h"
EndResultUI::EndResultUI(IWorld & world, GameManager& gameManager) :
	UIActor(world),
	mGameManager(&gameManager)
{
	parameter.isDead = false;

	//マトリクス設定
	mStageMat =
		Matrix4::Scale(10)*
		Matrix4::Translate(Vector3::Zero);
	mDaiMat =
		Matrix4::Scale(10)*
		Matrix4::Translate(Vector3(30, 10, 0));
	mSkyMat =
		Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);

	//サイズ取得
	int size = mGameManager->GetPlayerRank().size();
	//勝ちプレイヤー生成
	for (int i = 0; i <= size - 1; i++) {
		Vector3 pos;
		if (size == 1)
			pos = Vector3(30, 80, 0);
		else if (size == 2)
			pos = Vector3(20 + (20 * i), 80, 0);
		else if (size == 3)
			pos = Vector3(15 + (15 * i), 80, 0);
		else if (size == 4)
			pos = Vector3(15 + (10 * i), 80, 0);
		//生成
		ANIMATION randAnim = ANIMATION::PLAYER_WIN1;
		if (Random::GetInstance().Range(0, 1) == 1)
			randAnim = ANIMATION::PLAYER_WIN2;

		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<AnimActor>
			(world, pos, mGameManager->GetPlayerRank()[i], randAnim));
	}
	//観客情報
	SuportSet();
	for (const auto& i : mKankyakuMats)
	{
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<AnimActor>(world, i.mat, i.modelId, i.animId));
	}

	//時間初期化
	mActionTime = 0.0f;

	//カメラ設定
	Camera::GetInstance().Position.Set(Vector3(30, 90, -300));
	Camera::GetInstance().Target.Set(Vector3(30, 80, 0));
	Camera::GetInstance().Update();
	//カメラ初期化系
	mResCameraPos = Vector3(30, 90, -300);
	mCameraPos = mResCameraPos;
	mCameraVelo = Vector3::Zero;
	//注視点初期化系
	mTargetPos = Vector3(30, 80, 0);
	mResTargetPos = mTargetPos;
	mTargetVelo = Vector3::Zero;
	//α値
	mWinnerAlpha = 0.0f;
	mPleaseAphaCount = 0.0f;
	mIsEnd = false;

	Sound::GetInstance().PlaySE(SE_ID::RESULT_PLAYER_START_SE, DX_PLAYTYPE_BACK);
}

EndResultUI::~EndResultUI()
{
}

void EndResultUI::Update(PLAYER_NUMBER playerNumber)
{
	mActionTime += Time::GetInstance().deltaTime();
	//カメラが近づく時間＆注視点補間
	if (mActionTime >= 3.5f) {
		if (!Sound::GetInstance().IsPlayBGM()) {
			Sound::GetInstance().PlayBGM(BGM_ID::RESULT_WIN_BGM, DX_PLAYTYPE_LOOP);
		}
		mResCameraPos = Vector3(10, 70, -100);
		mResTargetPos = Vector3(30, 120, 0);
		mWinnerAlpha += 1.5f*Time::GetInstance().deltaTime();
	}
	if (mActionTime >= 6.0f) {
		mPleaseAphaCount += 200.0*Time::GetInstance().deltaTime();
		mIsEnd = true;
	}

	//補間
	Vector3::Spring(mCameraPos, mCameraVelo, mResCameraPos, 0.2f, 0.5f, 2.0f);
	Vector3::Spring(mTargetPos, mTargetVelo, mResTargetPos, 0.3f, 0.5f, 2.0f);
	//カメラ更新
	Camera::GetInstance().Position.Set(mCameraPos);
	Camera::GetInstance().Target.Set(mTargetPos);
	Camera::GetInstance().Update();
}

void EndResultUI::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, mStageMat);
	Model::GetInstance().Draw(MODEL_ID::DAI_MODEL, mDaiMat);
	//スカイボックス
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkyMat);
	Sprite::GetInstance().Draw(SPRITE_ID::WIN_PLAYER_SPRITE, Vector2::Zero, mWinnerAlpha);

	Sprite::GetInstance().Draw(SPRITE_ID::PLEASE_BUTTON_SPRITE, Vector2((WINDOW_WIDTH / 2)-242, 640), Math::Sin(mPleaseAphaCount));

}

bool EndResultUI::GetIsEnd()
{
	return mIsEnd;
}

void EndResultUI::SuportSet()
{
	//一人目
	{
		Matrix4 mat;
		Stage::KankyakuState state;
		mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(180)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(10, 12, -60));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_HAND_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_1_MODEL;
		mKankyakuMats.push_back(state);
	}
	//二人目
	{
		Matrix4 mat;
		Stage::KankyakuState state;
		mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(-90)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(50, 12, -90));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_OUEN_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_2_MODEL;
		mKankyakuMats.push_back(state);
	}
	//3人目
	{
		Matrix4 mat;
		Stage::KankyakuState state;
		mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(200)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(-30, 12, -100));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_HAND_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_3_MODEL;
		mKankyakuMats.push_back(state);
	}
	//4人目
	{
		Matrix4 mat;
		Stage::KankyakuState state;
		mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(180)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(100, 12, -120));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_HAND_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_4_MODEL;
		mKankyakuMats.push_back(state);
	}
	//5人目
	{
		Matrix4 mat;
		Stage::KankyakuState state;
		mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(180)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(30, 12, -150));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_HAND_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_5_MODEL;
		mKankyakuMats.push_back(state);
	}
}
