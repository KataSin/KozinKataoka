#pragma once
#include "../../Actor.h"
#include "../../PlayerBullet/PlayerBullet.h"
#include "../../CameraActor.h"

#include "../../Player.h"
class PlayerAttackManager :public Actor
{
public:
	PlayerAttackManager(IWorld& world, Actor& player);
	~PlayerAttackManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
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
	//�e�ɓn�����
	BulletState bulletState;
};