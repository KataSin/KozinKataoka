#pragma once
#include "../Actor.h"

class Pool :public Actor
{
public:
	Pool(IWorld& world, Vector3& pos1,Vector3& pos2);
	~Pool();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//ポールの座標
	Vector3 mPos1;
	Vector3 mPos2;
	//lineのポジション
	Vector3 mLinePosition;
	//出現タイマー
	float mTimer;

};