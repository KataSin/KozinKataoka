#include "AnimetionClass.h"
#include "../time/Time.h"
#include "Anime.h"
#include "Model.h"
#include "../math/Math.h"
#include "../input/Keyboard.h"
AnimationClass::AnimationClass(Actor* actor, ANIMATION startAnim, MODEL_ID model) :
	mModel(MV1DuplicateModel(Model::GetInstance().GetHandle(model))),
	mActor(actor),
	blendTime(0.0f),
	blendFlag(false)
{
	AttachAnim(startAnim);
	mCurAnimation = startAnim;
	mPreAnimation = ANIMATION::NULL_ANIM;
	MV1SetTextureAddressMode(mModel, 0, 0.1f, 0.1f);
	MV1SetTextureGraphHandle(mModel,0,Sprite::GetInstance().
		GetIndex(SPRITE_ID::PLAYER4_MODEL_SPRITE) , FALSE);
}

AnimationClass::~AnimationClass()
{
	//delete mActor;
}

void AnimationClass::update()
{
	AnimeBlend();
	//全てのアニメーションの時間を進める
	for (auto& itr = attachAnimes.begin(); itr != attachAnimes.end(); ++itr) {
		if (itr->second.animetionFlag)
		{
			itr->second.animTimer += 20 * Time::DeltaTime;
			MV1SetAttachAnimTime(mModel, itr->second.index, itr->second.animTimer);
			if (itr->second.animEndTime <= itr->second.animTimer)
			{
				itr->second.animTimer = 0.0f;
			}
		}
	}
}

void AnimationClass::draw()
{
	Model::GetInstance().Draw(mModel, mActor->GetParameter().mat);
}

void AnimationClass::changeAnim(ANIMATION anim)
{
	if (anim == mCurAnimation||blendFlag) return;
	mPreAnimation = mCurAnimation;
	mCurAnimation = anim;
	AttachAnim(mCurAnimation);
	attachAnimes[mPreAnimation].animetionFlag = false;
	blendFlag = true;
	blendTime = 0.0f;
	AnimeBlend();
}

void AnimationClass::AttachAnim(ANIMATION anim)
{
	attachAnimes[anim].index = MV1AttachAnim(mModel, anim);
	attachAnimes[anim].animEndTime = MV1GetAttachAnimTotalTime(mModel, attachAnimes[anim].index);
	mCurAnimation = anim;
}

void AnimationClass::DetachAnim(ANIMATION anim)
{
	MV1DetachAnim(mModel, attachAnimes[anim].index);
	attachAnimes.erase(anim);
}


void AnimationClass::AnimeBlend()
{
	if (!blendFlag) return;
	MV1SetAttachAnimBlendRate(mModel, attachAnimes[mPreAnimation].index, 1.0f - blendTime);
	MV1SetAttachAnimBlendRate(mModel, attachAnimes[mCurAnimation].index, blendTime);
	blendTime += 10.0f*Time::DeltaTime;
	blendTime = Math::Clamp(blendTime, 0.0f, 1.0f);
	if (blendTime >= 1.0f) {
		blendFlag = false;
		DetachAnim(mPreAnimation);
	}

}