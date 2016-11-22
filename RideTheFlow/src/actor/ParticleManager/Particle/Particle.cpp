#include "Particle.h"
#include "../../Collision.h"
#include "../../../time/Time.h"
#include "../../../graphic/Model.h"
Particle::Particle(IWorld & world, Vector3 position,Vector3 vec, Vector4 color):
	Actor(world),
	mPosition(position),
	mVec(vec),
	mDeadTime(0.0f),
	mAlpha(1.0f),
	mColor(color)
{
	parameter.isDead = false;
	parameter.mat =
		Matrix4::Scale(0.3f)*
		Matrix4::Translate(mPosition);
}

Particle::~Particle()
{
}

void Particle::Update()
{
	mDeadTime += Time::DeltaTime;
	mPosition += mVec*Time::DeltaTime;

	Deceleration(mVec.x);
	Deceleration(mVec.y);
	Deceleration(mVec.z);
	
	parameter.mat = 
		Matrix4::Scale(0.3f)*
		Matrix4::Translate(mPosition);

	if (mDeadTime >= 1.0f) {
		mAlpha -= Time::DeltaTime;
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
	//Œ¸‘¬ˆ—
	if (pos > 0.2f || pos<-0.2f)
	{
		if (pos < 0.0f)
		{
			pos += Time::DeltaTime;
		}
		if (pos > 0.0f)
		{
			pos -= Time::DeltaTime;
		}
	}
	else
	{
		pos = 0;
	}

}
