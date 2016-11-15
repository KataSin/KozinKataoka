#pragma once
#include "../math/Matrix4.h"
#include "../actor/ID.h"
#include <map>
#include "../actor/Actor.h"
struct AnimationState {
	//インデックス番号
	int index;
	//アニメーション終了時間
	float animEndTime;
	//アニメーション時間
	float animTimer = 0.0f;
	//再生しているか
	bool animetionFlag = true;
};
class AnimationClass
{
public:
	//コンストラクタ
	AnimationClass(Actor* actor, ANIMATION startAnim, MODEL_ID model);
	~AnimationClass();
	//更新
	void update();
	//描画
	void draw();
	//アニメーションの変更
	void changeAnim(ANIMATION anim);
	//アニメーションアタッチ
	void AttachAnim(ANIMATION anim);
	//アニメーションデタッチ
	void DetachAnim(ANIMATION anim);
	//ブレンド
	void AnimeBlend();

private:
	//アニメーションさせるMODELID
	int mModel;
	//現在のアニメーション
	ANIMATION mCurAnimation;
	//前回のアニメーション
	ANIMATION mPreAnimation;
	//アタッチ情報
	std::map<ANIMATION, AnimationState> attachAnimes;
	//アクター情報
	Actor* mActor;
	//ブレンド時間
	float blendTime;
	//ブレンドしています
	bool blendFlag;


	int test;
	float testTimer;

	int indexa;
	int indexRun;
	int indexIdle;
};

