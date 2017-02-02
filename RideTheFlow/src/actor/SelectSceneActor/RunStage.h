#pragma once
#include "../Actor.h"
#include "../Collision.h"

class RunStage :public Actor
{
public:
	RunStage(IWorld& world);
	~RunStage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//モデルのポジション
	Matrix4 mPos1;
	Matrix4 mPos2;
	Matrix4 mPos3;
	//スカイドームマトリックス
	Matrix4 mSkyMat;
	//モデルのスケール
	float mScale;
};