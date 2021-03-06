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

	//ランダムで拡散する
	mRandVec = Vector3(
		Random::GetInstance().Range(-rand, rand),
		Random::GetInstance().Range(-rand + 0.5f, rand - 0.5f),
		Random::GetInstance().Range(-rand, rand));

	mRandRotate = Vector3(
		Random::GetInstance().Range(-100, 100),
		Random::GetInstance().Range(-100, 100),
		Random::GetInstance().Range(-100, 100));

	//bulletstateを代入
	mPosition = state.position;
	mVertexPoint = state.vertexPoint;
	mStartPos = state.position;
	//距離を求める計算
	mDistance = (mVertexPoint + mRandVec - mStartPos);
	mCoppyPosY = mStartPos.y;
	//カラーを設定
	mColor = color;
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{
	//あたり判定を設定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYERBULLET_PLAYER_COL);
	//world.SetCollideSelect(shared_from_this(), ACTOR_ID::RESPAWNPOINT_ACTOR, COL_ID::BULLET_RESPAENPOINT_COL);
	float speed = 3.0f;
	//タイム加算
	mTime += Time::GetInstance().deltaTime();
	//頂点が出現位置よりも高かったら(頂点と出現位置の引き算がマイナスになり平方根で求められなくなるため)
	if (mCoppyPosY <= mVertexPoint.y)
	{
		//最高高度をもとに初速度を求める(鉛直投げ上げ)
		float InitializeVec = Math::Sqrt((mVertexPoint.y - mCoppyPosY) * 2.0f * 9.8f);
		//初速度を元に頂点に達する時間を求める
		float vertexTime = InitializeVec / 9.8f;
		//距離と頂点に達する時間が分かったので1フレームに動くx軸z軸の移動量を求める
		mVec = Vector3(
			mDistance.x / vertexTime  *speed* Time::GetInstance().deltaTime(),
			0.0f,
			mDistance.z / vertexTime *speed* Time::GetInstance().deltaTime());
		//y軸の位置を求める
		mPosition.y = InitializeVec*mTime*speed - 9.8f / 2.0f * pow(mTime*speed, 2) + mCoppyPosY;
		//移動量を足す
		mPosition += mVec;
	}
	//低かったら(初速度が求められないため)
	else
	{
		//騙す(バレない)
		mVecY -= 10.0f*Time::GetInstance().deltaTime();
		Vector3 mVec = mDistance + Vector3(0.0f, mVecY, 0.0f);
		mPosition += mVec*speed*1.5f*Time::GetInstance().deltaTime();
	}
	mRotate += mRandRotate*Time::GetInstance().deltaTime();

	//下に行ったら死亡
	if (parameter.mat.GetPosition().y <= -5.0f)
		parameter.isDead = true;
	//マトリクス計算
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
