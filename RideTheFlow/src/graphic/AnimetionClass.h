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
	//ブレンド率
	float animBlend = 0.0f;
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
	void addAnim(ANIMATION anim);
	//アニメーションデタッチ
	void deleteAnim(ANIMATION anim);
	//走っているときのアニメーションブレンド(プレイヤーの速度)
	void runAnimationBlend(Vector3 velocity);
	//現在再生中のモーション
	int getMotion() const;
	//ボーン数を返す
	int getBoneCount() const;
	//終了時間を返す
	int getEndTime() const;

private:
	//アニメーションさせるMODELID
	int mModel;
	//現在のアニメーション
	ANIMATION mAnimation;
	//前回のアニメーション
	ANIMATION mPreAnimation;
	//アニメーションアタッチ番号
	int mAtatti;
	//アタッチ情報
	std::map<ANIMATION, AnimationState> attachAnimes;
	//アクター情報
	Actor* mActor;

	//ブレンドテスト
	float blendNum;
};

