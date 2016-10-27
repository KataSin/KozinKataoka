#include "AnimetionClass.h"
#include "../time/Time.h"
#include "Anime.h"
#include "Model.h"
#include "../math/Math.h"
AnimationClass::AnimationClass(Actor* actor, ANIMATION startAnim, MODEL_ID model) :
	mModel(Model::GetInstance().GetHandle(model)),
	mActor(actor),
	blendNum(0.0f)
{
	addAnim(startAnim);
	mAnimation = startAnim;
	mPreAnimation = startAnim;
	MV1SetAttachAnimBlendRate(mModel, attachAnimes[startAnim].index, 1.0f);
}

AnimationClass::~AnimationClass()
{
	//delete mActor;
}

void AnimationClass::update()
{
	if (mAnimation == ANIMATION::NULL_ANIM) return;

	if (mAnimation != mPreAnimation)
	{
		MV1SetAttachAnimBlendRate(mModel, attachAnimes[mAnimation].index, blendNum);
		MV1SetAttachAnimBlendRate(mModel, attachAnimes[mPreAnimation].index, 1.0f - blendNum);
		blendNum += 2.0f*Time::DeltaTime;
		if (blendNum >= 1.0f) {
			deleteAnim(mPreAnimation);
			mPreAnimation = mAnimation;
			blendNum = 0.0f;
		}
	}
	//全てのアニメーションの時間を進める
	for (auto& itr = attachAnimes.begin(); itr != attachAnimes.end(); ++itr) {
		itr->second.animTimer += 10 * Time::DeltaTime;
		MV1SetAttachAnimTime(mModel, itr->second.index, itr->second.animTimer);
		if (itr->second.animEndTime <= itr->second.animTimer)
			itr->second.animTimer = 0.0f;
	}
}

void AnimationClass::draw()
{
	Model::GetInstance().Draw(MODEL_ID::TEST_PLAYER_MODEL, mActor->GetParameter().mat);
}

void AnimationClass::changeAnim(ANIMATION anim)
{
	if (mAnimation == anim) return;
	if (blendNum == 0.0f)
	{
		addAnim(anim);
		mAnimation = anim;
	}
}
//
void AnimationClass::addAnim(ANIMATION anim)
{
	//アニメーション情報を追加
	attachAnimes[anim].index = MV1AttachAnim(mModel, anim, -1, FALSE);
	attachAnimes[anim].animEndTime = MV1GetAttachAnimTotalTime(mModel, attachAnimes[anim].index);
}

void AnimationClass::deleteAnim(ANIMATION anim)
{
	MV1DetachAnim(mModel, attachAnimes[anim].index);
	attachAnimes.erase(anim);
}

void AnimationClass::runAnimationBlend(Vector3 velocity)
{
	float len = Vector3::Length(velocity);
	float blend = Math::Lerp(0.0f, 1.0f, len / 10.0f);

	//MV1SetAttachAnimBlendRate(mModel, attachAnimes[ANIMATION::PLATER_RUN_ANIM].index, 1.0f - blend);
	//MV1SetAttachAnimBlendRate(mModel, attachAnimes[ANIMATION::PLAYER_IDLE_ANIM].index, blend);
	//Model::GetInstance().Draw(mModel, mActor->GetParameter().mat);
}