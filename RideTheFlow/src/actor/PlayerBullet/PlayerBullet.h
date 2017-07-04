#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class Player;

struct BulletState
{
	//�v���C���[�ԍ�
	PLAYER_NUMBER playerNumber;
	//���_�̍��W
	Vector3 vertexPoint;
	//�e���o������ʒu
	Vector3 position;
};


class PlayerBullet :public Actor, public std::enable_shared_from_this<PlayerBullet>
{
public:
	PlayerBullet(IWorld& world, BulletState state, const Vector4& color,float rand=1.5f);
	~PlayerBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//�e�̏��
	BulletState mBulletState;
	//�x�N�g��
	Vector3 mVec;
	//�x�N�g��Y
	float mVecY;
	//�ʒu
	Vector3 mPosition;
	//�o������ʒu
	Vector3 mStartPos;
	//���_�̈ʒu
	Vector3 mVertexPoint;
	//����
	Vector3 mDistance;
	//����
	float mTime;
	//�����_�����W
	Vector3 mRandVec;
	//�����_����]
	Vector3 mRandRotate;
	//��]
	Vector3 mRotate;
	//�J���[
	Vector4 mColor;

	float mCoppyPosY;
};