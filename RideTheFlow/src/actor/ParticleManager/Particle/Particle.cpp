#include "Particle.h"
#include "../../Collision.h"
#include "../../../time/Time.h"
#include "../../../graphic/Model.h"
#include "../../../game/Random.h"
Particle::Particle(IWorld & world, Vector3 position,Vector3 vec, Vector4 color):
	Actor(world),
	mPosition(position),
	mVec(vec),
	mDeadTime(0.0f),
	mAlpha(1.0f),
	mColor(color),
	mRotate(Vector3::Zero)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(0.3f)*
		Matrix4::Translate(mPosition);

	mRotateVelo = Vector3(Random::GetInstance().Range(-50, 50),
		Random::GetInstance().Range(-50, 50), 
		Random::GetInstance().Range(-50, 50));
}

Particle::~Particle()
{
}

void Particle::Update()
{
	mDeadTime += Time::GetInstance().deltaTime();
	mPosition += mVec*Time::GetInstance().deltaTime();

	Deceleration(mVec.x);
	Deceleration(mVec.y);
	Deceleration(mVec.z);
	
	mRotate += mRotateVelo*Time::GetInstance().deltaTime();

	parameter.mat =
		Matrix4::Scale(0.3f)*
		Matrix4::RotateX(mRotate.x)*
		Matrix4::RotateY(mRotate.y)*
		Matrix4::RotateZ(mRotate.z)*
		Matrix4::Translate(mPosition);

	if (mDeadTime >= 1.0f) {
		mAlpha -= Time::GetInstance().deltaTime();
	}

	if (mAlpha<=0.0f) {
		parameter.isDead = true;
	}
}

void Particle::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::PARTICLE_MODEL, parameter.mat,mAlpha,mColor);
}

void Particle::OnCollide(Actor & other, CollisionParameter colpara)
{
}

void Particle::Deceleration(float & pos)
{
	//��������
	if (pos > 0.2f || pos<-0.2f)
	{
		if (pos < 0.0f)
		{
			pos += Time::GetInstance().deltaTime();
		}
		if (pos > 0.0f)
		{
			pos -= Time::GetInstance().deltaTime();
		}
	}
	else
	{
		pos = 0;
	}

}
