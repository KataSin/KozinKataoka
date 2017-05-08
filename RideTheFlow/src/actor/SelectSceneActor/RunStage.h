#pragma once
#include "../Actor.h"
#include "../Collision.h"
#include <vector>

class RunStage :public Actor
{
	struct StageState
	{
		//�X�e�[�W�}�g���N�X
		Matrix4 mat;
		//�X�e�[�W�̍��W
		Vector3 position;
		//�����}�g���N�X
		std::vector<Matrix4> suports;
	};

public:
	RunStage(IWorld& world);
	~RunStage();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//�X�e�[�W���
	std::vector<StageState> mStages;
	//�X�J�C�h�[���}�g���b�N�X
	Matrix4 mSkyMat;
	//���f���̃X�P�[��
	float mScale;
};