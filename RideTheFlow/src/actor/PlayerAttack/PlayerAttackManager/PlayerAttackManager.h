#pragma once
#include "../../Actor.h"
#include "../../Player/Player.h"
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
	PlayerAttackState GetState();
	SniperState GetChargeCount();
	float GetOverHertCount();
	//�I�[�o�[�q�[�g���Ă��邩
	bool GetOverHertFlag();
	//�U�����Ă��邩�H
	bool GetIsAttack();
private:
	void PlayerAttack(PlayerAttackState state);
	void PlayerNumSet(PLAYER_NUMBER num);
	void MachineGun();
	void SniperGun();
	void ShotGun();
	//�p�[�e�B�N���Z�b�g
	void ParticleSet();
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
	int mPad;
	//�v���C���[����int�^
	int mAttacStateInt;
	//�������Ă��镐��
	PlayerAttackState mAttackState;
	//�}�V���K���A���U���J�E���g
	float mMachineAttackCount;
	//�I�[�o�[�q�[�g�J�E���g
	float mOverHertCount;
	//�I�[�o�[�q�[�g�t���O
	bool mOverHertFlag;
	//�X�i�C�p�[�̒e���
	SniperState mSniperState;
	//�X�i�C�p�[�̂����蔻��̃J�E���g
	float mIsColSniperCount;
	//�X�i�C�p�[�̃t���O
	bool mInitSniperFalg;
	//�V���b�g�K���A���U���J�E���g
	float mShotAttackCount;
	//�U�����Ă��邩�H
	bool mAttackFlag;
	//�I�[�o�[�q�[�g��ߎn�߂鎞��
	float mCoolHertCount;
	//ui�̏ꏊ
	Vector2 mUiPos;
	//�I�[�o�[�q�[�g�̍��W
	Vector2 mOverHertUiPos;
	//�F���
	Vector4 mColor;

	//�p�[�e�B�N��
	ActorPtr mAttackParticle;
	ParticleEffectSystem::ParticleSetting mAttackParticleSet;

};