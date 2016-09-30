#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class Tree :public Actor, public std::enable_shared_from_this<Tree>
{
public:
	Tree(IWorld& world, Vector3 position);
	~Tree();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	bool GetDownFlag()
	{
		return downFlag;
	}
private:
	//�ʒu
	Vector3 mPosition;
	//�|���x�N�g��
	Vector3 mVec;
	//��]
	Vector3 mRotate;
	//���l
	float alpha;
	//�e�����������ʒu
	Vector3 isColPos;
	//�|���}�g���N�X
	Matrix4 downMat;
	//�⊮�p�ۊǃ}�g���N�X
	Matrix4 downSeveMat;
	//�ۊǗp�J�E���g
	float count;
	//�|���t���O
	bool downFlag;
	//�|��鑬�x
	float downVelo;
};