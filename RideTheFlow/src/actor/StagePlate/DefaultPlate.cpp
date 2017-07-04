#include "DefaultPlate.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../ParticleManager/ParticleManager.h"
#include "../../sound/Sound.h"
const float RespawnTime = 30.0f;
const int HP = 3;
DefaultPlate::DefaultPlate(IWorld & world, Vector3 position) :
	Actor(world),
	mPlayerNum(PLAYER_NUMBER::PLAYER_NULL),
	mPosition(position),
	mPlateColor(0, 0, 0, 1),
	mColor(0.0f),
	mRespawnCount(0.0f),
	mIsDead(false)
{
	parameter.isDead = false;
	parameter.HP = HP;
	parameter.radius = 10.0f;
	parameter.playNumber = PLAYER_NUMBER::PLAYER_NULL;
	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(position);
}

DefaultPlate::~DefaultPlate()
{
}

void DefaultPlate::Update()
{
	parameter.playNumber = mPlayerNum;
	//あたり判定(死んだら判定しない)
	if (!mIsDead)
	{
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_BULLET_ACTOR, COL_ID::PLATE_BULLET_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLATE_PLAYER_COL);
	}
	//当てたプレイヤーによって色を変える
	switch (mPlayerNum)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		mPlateColor = Vector4(0.0f, 0.0f, mColor, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		mPlateColor = Vector4(mColor, 0.0f, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_3:
	{
		mPlateColor = Vector4(0.0f, mColor, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_4:
	{
		mPlateColor = Vector4(mColor, mColor, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_NULL:
	{
		mPlateColor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	}

	//死んだらしスポーン状態へ
	if (parameter.HP <= 0&&!mIsDead)
	{
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleManager>
			(world, parameter.mat.GetPosition(),
				Vector3(4,0,4),
				mPlateColor,
				5,
				Vector3(5,5,5),
				Vector3(-5,0,-5),
				Vector3(10,0,10)));
		Sound::GetInstance().PlaySE(SE_ID::PLATE_BREAK_SE,DX_PLAYTYPE_BACK);
		mIsDead = true;
	}
	if(mIsDead)
		mRespawnCount += Time::GetInstance().deltaTime();
	//復活したら初期状態に戻る
	if (mRespawnCount >= RespawnTime)
	{
		mPlayerNum = PLAYER_NUMBER::PLAYER_NULL;
		mColor = 0.0f;
		parameter.HP = 5;
		mRespawnCount = 0.0f;
		mIsDead = false;
	}

	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
}

void DefaultPlate::Draw() const
{
	//DrawSphere3D(Vector3::ToVECTOR(Vector3(parameter.mat.GetPosition())- Vector3(0.0f, parameter.radius, 0.0f)), parameter.radius, 10, 1, 1, TRUE);
	//死んだら描写しない
	if(!mIsDead)
	Model::GetInstance().Draw(MODEL_ID::DEFAULT_PLATE_MODEL, parameter.mat, 1.0f, mPlateColor);
}

void DefaultPlate::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_BULLET_COL)
	{
		mPlayerNum = other.GetParameter().playNumber;
		parameter.HP-=1;
		mColor += 1.0f / 2.0f;
	}
}
