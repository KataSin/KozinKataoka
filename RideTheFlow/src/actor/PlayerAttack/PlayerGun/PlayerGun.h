#pragma once
#include "../../Actor.h"
#include <memory>

class PlayerGun :public Actor
{
public:
	//プレイヤーナンバー版
	PlayerGun(IWorld & word, Actor& player);
	~PlayerGun();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	void SetMat(const Matrix4& mat);
	void DrawGun(bool flag);

private:
	//プレイヤーアクター
	Actor* mPlayer;
	//武器モデるのmatrix
	Matrix4 mGunMat;
	//武器モデルのID
	MODEL_ID mId;

	//モデルα値
	float mAlpha;
	//表示させるか
	bool mIsDrawFlag;
};