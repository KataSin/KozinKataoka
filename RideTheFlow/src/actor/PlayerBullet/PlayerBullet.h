#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class Player;

struct BulletState
{
	//プレイヤー番号
	PLAYER_NUMBER playerNumber;
	//頂点の座標
	Vector3 vertexPoint;
	//弾が出現する位置
	Vector3 position;
};


class PlayerBullet :public Actor, public std::enable_shared_from_this<PlayerBullet>
{
public:
	PlayerBullet(IWorld& world, BulletState state);
	~PlayerBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//弾の情報
	BulletState mBulletState;
	//ベクトル
	Vector3 vec;
	//ベクトルY
	float vecY;
	//位置
	Vector3 mPosition;
	//出現する位置
	Vector3 startPos;
	//頂点の位置
	Vector3 mVertexPoint;
	//距離
	Vector3 distance;
	//時間
	float time;
	//ランダム座標
	Vector3 randVec;

	float coppyPosY;
};