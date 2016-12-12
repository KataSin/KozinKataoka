#include "StageLine.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"
#include "../../../graphic/Model.h"
#include "../../Collision.h"
StageLine::StageLine(IWorld & world, Matrix4& mat) :
	Actor(world),
	mAlpha(1.0f),
	mAlphaTimer(0.0f),
	mDeadTimer(0.0f),
	mPosition(mat.GetPosition())
{
	parameter.mat = mat;
	mRotateY = mat.GetRotate().y;
	parameter.isDead = false;
}

StageLine::~StageLine()
{
}

void StageLine::Update()
{
	mPosition.y += 4.0f * Time::DeltaTime;
	mAlphaTimer += Time::DeltaTime;
	if (mAlphaTimer >= 1.8f) {
		mAlpha -= 1.0f*Time::DeltaTime;
		//“§–¾‚É‚È‚Á‚½‚çŽ€‚Ê
		if (mAlpha <= 0.0f)
			parameter.isDead = true;
	}
	parameter.mat.SetPosition(mPosition);
}

void StageLine::Draw() const
{
	//ƒ‰ƒCƒg‚Ì‰e‹¿‚ðŽó‚¯‚È‚¢
	SetLightEnable(false);
	Model::GetInstance().Draw(MODEL_ID::LINE_MODEL, parameter.mat, mAlpha, Vector4(255, 0, 0, 1));
	SetLightEnable(true);
}

void StageLine::OnCollide(Actor & other, CollisionParameter colpara)
{
}
