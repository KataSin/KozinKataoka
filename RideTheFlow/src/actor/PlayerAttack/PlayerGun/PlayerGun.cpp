#include "PlayerGun.h"
#include "../../Collision.h"
#include "../../../world/IWorld.h"
#include "../../../graphic/Model.h"
#include "../../../time/Time.h"
#include "./../../../math/Math.h"
PlayerGun::PlayerGun(IWorld & word, Actor& player) :
	Actor(world),
	mIsDrawFlag(false),
	mAlpha(1.0f),
	mPlayer(&player)
{
	parameter.isDead = false;

	switch (player.GetParameter().playNumber)
	{
	case PLAYER_1:
		mId = MODEL_ID::GUN1_MODEL;
		break;
	case PLAYER_2:
		mId = MODEL_ID::GUN2_MODEL;
		break;
	case PLAYER_3:
		mId = MODEL_ID::GUN3_MODEL;
		break;
	case PLAYER_4:
		mId = MODEL_ID::GUN4_MODEL;
		break;
	}

	//Matrix4 mat = MV1GetFrameLocalWorldMatrix(Model::GetInstance().GetHandle(MODEL_ID::PLAYER1_MODEL),)


	Matrix4 mat = player.GetParameter().mat;
	mGunMat =
		Matrix4::Scale(0.2f)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mat.GetPosition() - (mat.GetFront().Normalized()*2.3f) + Vector3(0, 2, 0));
}

PlayerGun::~PlayerGun()
{
}

void PlayerGun::Update()
{
	if (mIsDrawFlag) {
		mAlpha += 5.0f*Time::GetInstance().deltaTime();
	}
	else
	{
		mAlpha -= 5.0f*Time::GetInstance().deltaTime();
	}
	mAlpha = Math::Clamp(mAlpha, 0.0f, 1.0f);
	Matrix4 mat = mPlayer->GetParameter().mat;

	//mat = Matrix4::ToMatrix4(MV1GetFrameLocalWorldMatrix(Model::GetInstance().GetHandle(MODEL_ID::PLAYER1_MODEL), 11));
	mGunMat =
		Matrix4::Scale(0.2f)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(mPlayer->GetParameter().mat.GetRotateDegree().y - 180.0f)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mat.GetPosition() - (mat.GetFront().Normalized()*2.3f) + Vector3(0, 2, 0));
}

void PlayerGun::Draw() const
{
	Model::GetInstance().Draw(mId, mGunMat, mAlpha);
}

void PlayerGun::OnCollide(Actor & other, CollisionParameter colpara)
{
}

void PlayerGun::SetMat(const Matrix4 & mat)
{
	parameter.mat = mat;
}

void PlayerGun::DrawGun(bool flag)
{
	mIsDrawFlag = flag;
}
