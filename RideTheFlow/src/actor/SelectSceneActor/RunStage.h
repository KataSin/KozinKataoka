#pragma once
#include "../Actor.h"
#include "../Collision.h"
#include <vector>

class RunStage :public Actor
{
	struct StageState
	{
		//ステージマトリクス
		Matrix4 mat;
		//ステージの座標
		Vector3 position;
		//応援マトリクス
		std::vector<Matrix4> suports;
	};

public:
	RunStage(IWorld& world);
	~RunStage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//ステージ情報
	std::vector<StageState> mStages;
	//スカイドームマトリックス
	Matrix4 mSkyMat;
	//モデルのスケール
	float mScale;
};