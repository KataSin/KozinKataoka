#pragma once
#include "../Actor.h"
#include <memory>
class AnimationClass;

class AnimActor :public Actor
{
public:
	//プレイヤーナンバー版
	AnimActor(IWorld& word, const Vector3& position, const PLAYER_NUMBER& player,ANIMATION anim);
	//モデルID版
	AnimActor(IWorld& word, const Matrix4& mat, const MODEL_ID& modelId, ANIMATION anim);

	~AnimActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	MODEL_ID mModelId;
	std::shared_ptr<AnimationClass> mAnim;
};