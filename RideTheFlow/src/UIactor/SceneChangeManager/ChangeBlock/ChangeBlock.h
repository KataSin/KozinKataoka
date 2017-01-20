#pragma once
#include "../../UIActor.h"
struct TexState
{
	Vector2 randPos = Vector2::Zero;
	Vector2 toPos = Vector2::Zero;
	float randAngle = 0.0f;
	int texHandle = 0;
};
class ChangeBlock :public UIActor {
public:
	ChangeBlock(IWorld& world,const TexState& state);
	~ChangeBlock();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

public:
	void BlockDown();
private:
	Vector2 mPosition;
	Vector2 mCenter;
	//��ԗp
	Vector2 mCurPosition;
	Vector2 mToPositon;
	float mLeapTime;
	//�p�x���
	float mAngle;
	float mCurAngle;
	float mToAngle;
	//�p�x�𑫂�
	float mPlusAngle;
	float mTime;
	float mAlpha;
	bool mDownFlag;
	//�e�N�X�`���n���h��
	int mHandle;
};