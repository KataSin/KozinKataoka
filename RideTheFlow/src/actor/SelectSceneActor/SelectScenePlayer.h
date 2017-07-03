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
	//�v���C���[�߂邩�ǂ����t���O
	void SetBackFlag(bool flag);
private:
	Vector3 mPosition;
	PLAYER_NUMBER mPlayerNum;
	MODEL_ID mModelId;
	std::shared_ptr<AnimationClass> mAnim;
	//��Ԋ֌W
	Vector3 mStartPos;
	Vector3 mEndPos;
	float mLerpCount;

	//��ނ��邩�ǂ���
	bool mIsBack;
};