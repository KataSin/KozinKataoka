#pragma once
#include "../Actor.h"
#include <memory>
class AnimationClass;

class ResultPlayer :public Actor
{
public:
	ResultPlayer(IWorld& word, const Vector3& position, const PLAYER_NUMBER& player,ANIMATION anim);
	~ResultPlayer();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	MODEL_ID mModelId;
	std::shared_ptr<AnimationClass> mAnim;
};