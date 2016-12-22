#include "PlayerBullet.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../Player.h"


PlayerBullet::PlayerBullet(IWorld & world, BulletState state,const Vector4& color ,float rand) :
	Actor(world),
	mBulletState(state),
	distance(Vector3::Zero),
	vec(Vector3::Zero),
	mRotate(Vector3::Zero),
	vecY(0.0f),
	time(0.0f)
{
	parameter.isDead = false;
	parameter.playNumber = state.playerNumber;
	if (rand == 1.5f)
		parameter.id = ACTOR_ID::PLAYER_BULLET_ACTOR;
	else
		parameter.id = ACTOR_ID::PLAYER_BULLET_SHOT_ACTOR;
	parameter.radius = 0.5f;
	parameter.mat =
		Matrix4::Scale(0)*
		Matrix4::RotateX(0),
		Matrix4::RotateY(0),
		Matrix4::RotateZ(0),
		Matrix4::Translate(state.position);

	//�����_���Ŋg�U����
	randVec = Vector3(
		Random::GetInstance().Range(-rand, rand),
		Random::GetInstance().Range(-rand + 0.5f, rand - 0.5f),
		Random::GetInstance().Range(-rand, rand));

	mRandRotate = Vector3(
		Random::GetInstance().Range(-100, 100),
		Random::GetInstance().Range(-100, 100),
		Random::GetInstance().Range(-100, 100));

	//bulletstate����
	mPosition = state.position;
	mVertexPoint = state.vertexPoint;
	startPos = state.position;
	//���������߂�v�Z
	distance = (mVertexPoint + randVec - startPos);
	coppyPosY = startPos.y;
	//�J���[��ݒ�
	mColor = color;
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{
	//�����蔻���ݒ�
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYERBULLET_PLAYER_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::RESPAWNPOINT_ACTOR, COL_ID::BULLET_RESPAENPOINT_COL);
	float speed = 3.0f;
	//�^�C�����Z
	time += Time::DeltaTime;
	//���_���o���ʒu��������������(���_�Əo���ʒu�̈����Z���}�C�i�X�ɂȂ蕽�����ŋ��߂��Ȃ��Ȃ邽��)
	if (coppyPosY <= mVertexPoint.y)
	{
		//�ō����x�����Ƃɏ����x�����߂�(���������グ)
		float InitializeVec = Math::Sqrt((mVertexPoint.y - coppyPosY) * 2.0f * 9.8f);
		//�����x�����ɒ��_�ɒB���鎞�Ԃ����߂�
		float vertexTime = InitializeVec / 9.8f;
		//�����ƒ��_�ɒB���鎞�Ԃ����������̂�1�t���[���ɓ���x��z���̈ړ��ʂ����߂�
		vec = Vector3(
			distance.x / vertexTime  *speed* Time::DeltaTime,
			0.0f,
			distance.z / vertexTime *speed* Time::DeltaTime);
		//y���̈ʒu�����߂�
		mPosition.y = InitializeVec*time*speed - 9.8f / 2.0f * pow(time*speed, 2) + coppyPosY;
		//�ړ��ʂ𑫂�
		mPosition += vec;
	}
	//�Ⴉ������(�����x�����߂��Ȃ�����)
	else
	{
		//�x��(�o���Ȃ�)
		vecY -= 10.0f*Time::DeltaTime;
		Vector3 vec = distance + Vector3(0.0f, vecY, 0.0f);
		mPosition += vec*speed*1.5f*Time::DeltaTime;
	}
	mRotate += mRandRotate*Time::DeltaTime;

	//���ɍs�����玀�S
	if (parameter.mat.GetPosition().y <= -5.0f)
		parameter.isDead = true;
	//�}�g���N�X�v�Z
	parameter.mat =
		Matrix4::Scale(0.1f)*
		Matrix4::RotateX(mRotate.x)*
		Matrix4::RotateY(mRotate.y)*
		Matrix4::RotateZ(mRotate.z)*
		Matrix4::Translate(mPosition);
}

void PlayerBullet::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PLAYER_BULLET_MODEL, parameter.mat,1.0f,mColor);

	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

void PlayerBullet::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_BULLET_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::BULLET_RESPAENPOINT_COL)
	{
		parameter.isDead = true;
	}
	if (colpara.colID == COL_ID::BULLET_TREE_COL)
	{
		parameter.isDead = true;
	}
}
