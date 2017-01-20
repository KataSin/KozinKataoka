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
	//補間用
	Vector2 mCurPosition;
	Vector2 mToPositon;
	float mLeapTime;
	//角度補間
	float mAngle;
	float mCurAngle;
	float mToAngle;
	//角度を足す
	float mPlusAngle;
	float mTime;
	float mAlpha;
	bool mDownFlag;
	//テクスチャハンドル
	int mHandle;
};