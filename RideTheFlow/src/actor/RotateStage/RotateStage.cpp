#include "RotateStage.h"
#include "../Collision.h"
#include "../../graphic/Model.h"
#include "../../time/Time.h"
#include "../../camera/Camera.h"
RotateStage::RotateStage(IWorld & world, const Vector3 & position):
	Actor(world),
	mPosition(position),
	mRotateY(0.0f)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(position);
	mSkymat= Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(position);

}

RotateStage::~RotateStage()
{
}

void RotateStage::Update()
{
	mRotateY += 50.0f*Time::GetInstance().deltaTime();
	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(mPosition);
	mSkymat = Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(mRotateY)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(mPosition);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0,150,200));
	Camera::GetInstance().Target.Set(Vector3(0,50,0));
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
}

void RotateStage::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::STAGE01_MODEL, parameter.mat);
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkymat);
}

void RotateStage::OnCollide(Actor & other, CollisionParameter colpara)
{
}
