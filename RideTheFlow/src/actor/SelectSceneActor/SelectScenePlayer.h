#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>
class AnimationClass;

class SelectScenePlayer :public Actor
{
public:
	SelectScenePlayer(IWorld& word, const Vector3& position, const MODEL_ID& player);
	~SelectScenePlayer();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	//プレイヤー戻るかどうかフラグ
	void SetBackFlag(bool flag);
private:
	Vector3 mPosition;
	PLAYER_NUMBER mPlayerNum;
	MODEL_ID mModelId;
	std::shared_ptr<AnimationClass> mAnim;
	//補間関係
	Vector3 mStartPos;
	Vector3 mEndPos;
	float mLerpCount;

	//後退するかどうか
	bool mIsBack;
};