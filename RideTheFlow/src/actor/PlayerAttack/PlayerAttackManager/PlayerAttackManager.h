#pragma once
#include "../../Actor.h"
#include "../../PlayerBullet/PlayerBullet.h"
#include "../../CameraActor.h"

#include "../../Player.h"

struct SniperState
{
	//�`���[�W��
	float chargeSniperCount;
	//�����邩�ǂ���
	bool isColSniperLine;
	//�`���[�W���Ă��邩
	bool doCharge;
};

class PlayerAttackManager :public Actor
{
public:
	PlayerAttackManager(IWorld& world, Actor& player);
	~PlayerAttackManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	PlayerAttackState GetState()
	{
		return attackState;
	}
	SniperState GetChargeCount()
	{
		return mSniperState;
	}
private:
	void PlayerAttack(PlayerAttackState state);
	void MachineGun();
	void SniperGun();
private:
	//�J�����A�N�^�[
	CameraActor* mCamera;
	//�v���C���[
	Actor* mPlayer;
	//�p�b�h�̐���
	int pad;
	//�������Ă��镐��
	PlayerAttackState attackState;
	//�I�[�o�[�q�[�g�J�E���g
	float overHertCount;
	//�X�i�C�p�[�̒e���
	SniperState mSniperState;
	//�X�i�C�p�[�̂����蔻��̃J�E���g
	float isColSniperCount;
	//�e�ɓn�����
	BulletState bulletState;
	//�X�i�C�p�[�̃t���O
	bool initSniperFalg;
};