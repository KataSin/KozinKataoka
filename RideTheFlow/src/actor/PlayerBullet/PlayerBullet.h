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
	PlayerBullet(IWorld& world, BulletState state);
	~PlayerBullet();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//�e�̏��
	BulletState mBulletState;
	//�x�N�g��
	Vector3 vec;
	//�x�N�g��Y
	float vecY;
	//�ʒu
	Vector3 mPosition;
	//�o������ʒu
	Vector3 startPos;
	//���_�̈ʒu
	Vector3 mVertexPoint;
	//����
	Vector3 distance;
	//����
	float time;
	//�����_�����W
	Vector3 randVec;

	float coppyPosY;
};