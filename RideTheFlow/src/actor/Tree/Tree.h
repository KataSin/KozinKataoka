#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class Tree :public Actor, public std::enable_shared_from_this<Tree>
{
public:
	Tree(IWorld& world, Vector3 position);
	~Tree();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	bool GetDownFlag()
	{
		return downFlag;
	}
private:
	//位置
	Vector3 mPosition;
	//倒れるベクトル
	Vector3 mVec;
	//回転
	Vector3 mRotate;
	//α値
	float alpha;
	//弾が当たった位置
	Vector3 isColPos;
	//倒れるマトリクス
	Matrix4 downMat;
	//補完用保管マトリクス
	Matrix4 downSeveMat;
	//保管用カウント
	float count;
	//倒れるフラグ
	bool downFlag;
	//倒れる速度
	float downVelo;
};