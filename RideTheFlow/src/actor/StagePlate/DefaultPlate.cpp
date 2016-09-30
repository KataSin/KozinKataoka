#include "DefaultPlate.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"


const float RespawnTime = 10.0f;
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
	parameter.radius = 2.0f;
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

	//���񂾂炵�X�|�[����Ԃ�
	if (parameter.HP <= 0)
	{
		mIsDead = true;
		respawnCount += Time::DeltaTime;
	}
	//���������珉����Ԃɖ߂�
	if (respawnCount >= RespawnTime)
	{
		playerNum = PLAYER_NUMBER::PLAYER_NULL;
		clor = 0.0f;
		parameter.HP = 5;
		respawnCount = 0.0f;
		mIsDead = false;
	}

	//�����蔻��(���񂾂画�肵�Ȃ�)
	if (!mIsDead)
	{
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_BULLET_ACTOR, COL_ID::PLATE_BULLET_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLATE_PLAYER_COL);
	}
	//���Ă��v���C���[�ɂ���ĐF��ς���
	switch (playerNum)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		plateClor = Vector4(clor, 0.0f, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		plateClor = Vector4(0.0f, clor, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_3:
	{
		plateClor = Vector4(0.0f, 0.0f, clor, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_4:
	{
		plateClor = Vector4(0.0f, clor, clor, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_NULL:
	{
		plateClor = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
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
	//���񂾂�`�ʂ��Ȃ�
	if(!mIsDead)
	Model::GetInstance().Draw(MODEL_ID::DEFAULT_PLATE_MODEL, parameter.mat, 1.0f, plateClor);
}

void DefaultPlate::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_BULLET_COL)
	{
		playerNum = other.GetParameter().playNumber;
		parameter.HP--;
		//�f�b�h�e��������ꔭ�łԂ�����
		if (other.GetParameter().id == ACTOR_ID::DEAD_BULLET_ACTOR)
			parameter.HP = 0;
		clor += 1.0f / 2.0f;
	}
}
