#include "RunStage.h"
#include "../../graphic/Model.h"
RunStage::RunStage(IWorld & world):
	Actor(world)
{
	parameter.isDead = false;
	mSkyMat = Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);
	mPos1 =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(180)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(Vector3(0,-10,-100));
}

RunStage::~RunStage()
{
}

void RunStage::Update()
{
}

void RunStage::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, mPos1);
	//Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, mPos2);
	//ステージの描写
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkyMat);
}

void RunStage::OnCollide(Actor & other, CollisionParameter colpara)
{
}
