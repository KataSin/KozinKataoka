#include "ChangeParticle.h"
#include "../../../graphic/Sprite.h"
#include "../../../time/Time.h"
ChangeParticle::ChangeParticle(IWorld& world, const Vector2& position, const Vector2& vec, float angle,float deadTime,float size):
	UIActor(world),
	mPosition(position),
	mVec(vec),
	mPlusAngle(angle),
	mDeadTime(deadTime),
	mTime(0.0f),
	mAlpha(1.0f),
	mSize(size)
{
	parameter.isDead = false;
	mCenter = Sprite::GetInstance().GetSize(SPRITE_ID::CHANGE_SCENE_PARTICLE_SPRITE) / 2;
}

ChangeParticle::~ChangeParticle()
{
}

void ChangeParticle::Update(PLAYER_NUMBER playerNumber)
{
	mPosition += mVec*Time::DeltaTime;
	mAngle += mPlusAngle*Time::DeltaTime;
	mTime += Time::DeltaTime;
	if (mDeadTime <= mTime) {
		mAlpha -= Time::DeltaTime;
		if (mAlpha <= 0.0f) parameter.isDead = true;
	}
}

void ChangeParticle::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::CHANGE_SCENE_PARTICLE_SPRITE, mPosition,Vector4(255,50,50,0), mCenter, mAlpha,Vector2(mSize), mAngle);
}
