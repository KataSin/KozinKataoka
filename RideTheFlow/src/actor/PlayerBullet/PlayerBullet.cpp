#include "PlayerBullet.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../Time/Time.h"
#include "../../graphic/Model.h"


PlayerBullet::PlayerBullet(IWorld & world, BulletState state,const Vector4& color ,float rand) :
	Actor(world),
	mBulletState(state),
	mDistance(Vector3::Zero),
	mVec(Vector3::Zero),
	mRotate(Vector3::Zero),
	mVecY(0.0f),
	mTime(0.0f)
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
	mRandVec = Vector3(
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
	mStartPos = state.position;
	//���������߂�v�Z
	mDistance = (mVertexPoint + mRandVec - mStartPos);
	mCoppyPosY = mStartPos.y;
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
	mTime += Time::GetInstance().deltaTime();
	//���_���o���ʒu��������������(���_�Əo���ʒu�̈����Z���}�C�i�X�ɂȂ蕽�����ŋ��߂��Ȃ��Ȃ邽��)
	if (mCoppyPosY <= mVertexPoint.y)
	{
		//�ō����x�����Ƃɏ����x�����߂�(���������グ)
		float InitializeVec = Math::Sqrt((mVertexPoint.y - mCoppyPosY) * 2.0f * 9.8f);
		//�����x�����ɒ��_�ɒB���鎞�Ԃ����߂�
		float vertexTime = InitializeVec / 9.8f;
		//�����ƒ��_�ɒB���鎞�Ԃ����������̂�1�t���[���ɓ���x��z���̈ړ��ʂ����߂�
		mVec = Vector3(
			mDistance.x / vertexTime  *speed* Time::GetInstance().deltaTime(),
			0.0f,
			mDistance.z / vertexTime *speed* Time::GetInstance().deltaTime());
		//y���̈ʒu�����߂�
		mPosition.y = InitializeVec*mTime*speed - 9.8f / 2.0f * pow(mTime*speed, 2) + mCoppyPosY;
		//�ړ��ʂ𑫂�
		mPosition += mVec;
	}
	//�Ⴉ������(�����x�����߂��Ȃ�����)
	else
	{
		//�x��(�o���Ȃ�)
		mVecY -= 10.0f*Time::GetInstance().deltaTime();
		Vector3 mVec = mDistance + Vector3(0.0f, mVecY, 0.0f);
		mPosition += mVec*speed*1.5f*Time::GetInstance().deltaTime();
	}
	mRotate += mRandRotate*Time::GetInstance().deltaTime();

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
	SetLightEnable(false);
	Model::GetInstance().Draw(MODEL_ID::PLAYER_BULLET_MODEL, parameter.mat,1.0f,mColor);
	SetLightEnable(true);

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
