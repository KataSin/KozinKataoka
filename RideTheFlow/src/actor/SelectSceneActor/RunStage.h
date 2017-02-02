#pragma once
#include "../Actor.h"
#include "../Collision.h"

class RunStage :public Actor
{
public:
	RunStage(IWorld& world);
	~RunStage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//���f���̃|�W�V����
	Matrix4 mPos1;
	Matrix4 mPos2;
	Matrix4 mPos3;
	//�X�J�C�h�[���}�g���b�N�X
	Matrix4 mSkyMat;
	//���f���̃X�P�[��
	float mScale;
};