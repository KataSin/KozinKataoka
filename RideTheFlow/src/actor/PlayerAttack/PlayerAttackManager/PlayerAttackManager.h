#pragma once
#include "../../Actor.h"
#include "../../Player.h"
class CameraActor;
class PlayerGun;
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
	float GetOverHertCount()
	{
		return overHertCount;
	}
	//�I�[�o�[�q�[�g���Ă��邩
	bool GetOverHertFlag()
	{
		return overHertFlag;
	}
	//�U�����Ă��邩�H
	bool GetIsAttack()
	{
		return attackFlag;
	}
private:
	void PlayerAttack(PlayerAttackState state);
	void PlayerNumSet(PLAYER_NUMBER num);
	void MachineGun();
	void SniperGun();
	void ShotGun();
	//�p�[�e�B�N���Z�b�g
	void ParticleSet();
	////�p�[�e�B�N���A�b�v�f�[�g
	//void ParticleUpdate();
	//�p�[�e�B�N���ǉ�
	void AddParticle();
private:
	//�J�����A�N�^�[
	CameraActor* mCamera;
	//�v���C���[
	Player* mPlayer;
	//����A�N�^�[
	ActorPtr mGunPlayer;
	//����̃}�g���N�X
	Matrix4 mGunMat;
	//�p�b�h�̐���
	int pad;
	//�v���C���[����int�^
	int attacStateInt;
	//�������Ă��镐��
	PlayerAttackState attackState;
	//�}�V���K���A���U���J�E���g
	float machineAttackCount;
	//�I�[�o�[�q�[�g�J�E���g
	float overHertCount;
	//�I�[�o�[�q�[�g�t���O
	bool overHertFlag;
	//�X�i�C�p�[�̒e���
	SniperState mSniperState;
	//�X�i�C�p�[�̂����蔻��̃J�E���g
	float isColSniperCount;
	//�X�i�C�p�[�̃t���O
	bool initSniperFalg;
	//�V���b�g�K���A���U���J�E���g
	float shotAttackCount;
	//�U�����Ă��邩�H
	bool attackFlag;
	//�I�[�o�[�q�[�g��ߎn�߂鎞��
	float coolHertCount;
	//ui�̏ꏊ
	Vector2 uiPos;
	//�I�[�o�[�q�[�g�̍��W
	Vector2 mOverHertUiPos;
	//�F���
	Vector4 mColor;

	//�p�[�e�B�N��
	ActorPtr mAttackParticle;
	ParticleEffectSystem::ParticleSetting mAttackParticleSet;

};