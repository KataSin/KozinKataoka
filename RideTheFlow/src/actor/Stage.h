#pragma once
#include "Actor.h"
#include "../math/Vector3.h"

class Stage :public Actor
{
public:
	struct KankyakuState
	{
		Matrix4 mat;
		MODEL_ID modelId;
		ANIMATION animId;
	};
public:
	Stage(IWorld& world);
	~Stage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	void SetKankyaku();
private:
	int PixelShaderHandle;
	int VertexShaderHandle;
	Vector3 mStagePos;
	Matrix4 skyMat;
	//ŠÏ‹qî•ñ
	std::vector<KankyakuState> mKankyakuMats;
};