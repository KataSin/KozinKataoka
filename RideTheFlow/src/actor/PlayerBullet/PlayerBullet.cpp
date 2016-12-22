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

	//ランダムで拡散する
	randVec = Vector3(
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
	startPos = state.position;
	//距離を求める計算
	distance = (mVertexPoint + randVec - startPos);
	coppyPosY = startPos.y;
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
	time += Time::DeltaTime;
	//頂点が出現位置よりも高かったら(頂点と出現位置の引き算がマイナスになり平方根で求められなくなるため)
	if (coppyPosY <= mVertexPoint.y)
	{
		//最高高度をもとに初速度を求める(鉛直投げ上げ)
		float InitializeVec = Math::Sqrt((mVertexPoint.y - coppyPosY) * 2.0f * 9.8f);
		//初速度を元に頂点に達する時間を求める
		float vertexTime = InitializeVec / 9.8f;
		//距離と頂点に達する時間が分かったので1フレームに動くx軸z軸の移動量を求める
		vec = Vector3(
			distance.x / vertexTime  *speed* Time::DeltaTime,
			0.0f,
			distance.z / vertexTime *speed* Time::DeltaTime);
		//y軸の位置を求める
		mPosition.y = InitializeVec*time*speed - 9.8f / 2.0f * pow(time*speed, 2) + coppyPosY;
		//移動量を足す
		mPosition += vec;
	}
	//低かったら(初速度が求められないため)
	else
	{
		//騙す(バレない)
		vecY -= 10.0f*Time::DeltaTime;
		Vector3 vec = distance + Vector3(0.0f, vecY, 0.0f);
		mPosition += vec*speed*1.5f*Time::DeltaTime;
	}
	mRotate += mRandRotate*Time::DeltaTime;

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
