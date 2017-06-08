#pragma once
#include "../UIActor.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../UIactor/UIActorPtr.h"
#include <vector>
class SceneChangeManager :public UIActor {

public:
	SceneChangeManager(IWorld& world);
	~SceneChangeManager();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
	//�u���b�N�𖄂߂�(true:�u���b�N�Ŗ��߂�,false:�u���b�N���͂�������)
	void ChangeJudge(bool flag);
	float GetTime();
	//���S�Ƀu���b�N�������͂��Ă��邩
	bool GetNoBlockFlag();
	//���S�Ƀu���b�N���������܂��Ă��邩
	bool GetYesBlockFlag();
	//�摜����
	void SpriteSet(const SPRITE_ID& id);
private:
	//�u���b�N����
	std::vector<UIActorPtr> mBlocks;
	//�^�C��
	float mTime;
	//�^�C����1�b�ɂɂȂ��Ă���̃J�E���g
	float mTimeCount;
	//���߂邩�t���O
	bool mFlag;
	//���݂�SpriteID
	SPRITE_ID mNowId;
};