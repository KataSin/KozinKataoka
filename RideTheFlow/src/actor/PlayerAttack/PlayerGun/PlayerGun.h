#pragma once
#include "../../Actor.h"
#include <memory>

class PlayerGun :public Actor
{
public:
	//�v���C���[�i���o�[��
	PlayerGun(IWorld & word, Actor& player);
	~PlayerGun();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	void SetMat(const Matrix4& mat);
	void DrawGun(bool flag);

private:
	//�v���C���[�A�N�^�[
	Actor* mPlayer;
	//���탂�f���matrix
	Matrix4 mGunMat;
	//���탂�f����ID
	MODEL_ID mId;

	//���f�����l
	float mAlpha;
	//�\�������邩
	bool mIsDrawFlag;
};