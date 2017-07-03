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
	playerNum(PLAYER_NUMBER::PLAYER_NULL),
	mPosition(position),
	plateClor(0, 0, 0, 1),
	clor(0.0f),
	respawnCount(0.0f),
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
	parameter.playNumber = playerNum;
	//あたり判定(死んだら判定しない)
	if (!mIsDead)
	{
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_BULLET_ACTOR, COL_ID::PLATE_BULLET_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLATE_PLAYER_COL);
	}
	//当てたプレイヤーによって色を変える
	switch (playerNum)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		plateClor = Vector4(0.0f, 0.0f, clor, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		plateClor = Vector4(clor, 0.0f, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_3:
	{
		plateClor = Vector4(0.0f, clor, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_4:
	{
		plateClor = Vector4(clor, clor, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_NULL:
	{
		plateClor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	}

	//死んだらしスポーン状態へ
	if (parameter.HP <= 0&&!mIsDead)
	{
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleManager>
			(world, parameter.mat.GetPosition(),
				Vector3(4,0,4),
				plateClor,
				5,
				Vector3(5,5,5),
				Vector3(-5,0,-5),
				Vector3(10,0,10)));
		Sound::GetInstance().PlaySE(SE_ID::PLATE_BREAK_SE,DX_PLAYTYPE_BACK);
		mIsDead = true;
	}
	if(mIsDead)
		respawnCount += Time::GetInstance().deltaTime();
	//復活したら初期状態に戻る
	if (respawnCount >= RespawnTime)
	{
		playerNum = PLAYER_NUMBER::PLAYER_NULL;
		clor = 0.0f;
		parameter.HP = 5;
		respawnCount = 0.0f;
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
	Model::GetInstance().Draw(MODEL_ID::DEFAULT_PLATE_MODEL, parameter.mat, 1.0f, plateClor);
}

void DefaultPlate::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_BULLET_COL)
	{
		playerNum = other.GetParameter().playNumber;
		parameter.HP-=1;
		clor += 1.0f / 2.0f;
	}
}
