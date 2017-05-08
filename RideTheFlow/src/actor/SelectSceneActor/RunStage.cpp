#include "RunStage.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
RunStage::RunStage(IWorld & world) :
	Actor(world)
{
	parameter.isDead = false;
	mSkyMat = Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);

	StageState state1;
	state1.position = Vector3(0.0f, -10.0f, -100.0f);
	state1.mat =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(180.0f)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(state1.position);
	StageState state2;
	state2.position = Vector3(126.0f*10.0f, -10.0f, -100.0f);
	state2.mat =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(180.0f)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(state2.position);
	StageState state3;
	state3.position = Vector3(-126.0f*10.0f, -10.0f, -100.0f);
	state3.mat =
		Matrix4::Scale(10)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(180.0f)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(state3.position);



	mStages.push_back(state1);
	mStages.push_back(state2);
	mStages.push_back(state3);


}

RunStage::~RunStage()
{
}

void RunStage::Update()
{
	for (auto & i : mStages) {
		if (i.position.x <= -126.0f*10.0f*2.0f)
			i.position.x = 1260.0f;
		else
			i.position.x -= 300.0*Time::GetInstance().deltaTime();
		i.mat.SetPosition(i.position);
	}
}

void RunStage::Draw() const
{
	for (const auto& i : mStages) {
		Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, i.mat);
	}
	//ステージの描写
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkyMat);
}

void RunStage::OnCollide(Actor & other, CollisionParameter colpara)
{
}
