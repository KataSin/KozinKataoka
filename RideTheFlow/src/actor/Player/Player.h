#pragma once
#include "../Actor.h"
#include "../ActorPtr.h"
#include <memory>
#include "../PlayerBullet\PlayerBullet.h"

#include "../ID.h"
#include "../../graphic/AnimetionClass.h"
#include "../../ParticleEffectSystem/ParticleEffectSystem.h"
enum PlayerState
{
	PLAYERSTOP,
	PLAYERWALK,
	PLAYERDASH,
	PLAYERJUMP,
	PLAYERATTACK,
	PLAYERSNIPERATTACK,
	PLAYERATTACKCHARGE,
	PLAYERDAMAGE,
	PLAYERRESPAWN
};
enum PlayerAttackState
{
	MACHINE_GUN,
	SNIPER_GUN,
	SHOT_GUN
};
//��
class CameraActor;

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world,Vector3 position,float rotateY,PLAYER_NUMBER player);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

public:
	void SetPlayerState(PlayerState state);
	PlayerState GetPlayerState();
	PLAYER_NUMBER GetDamagePlayer();
	//�e�̏o���ʒu�擾
	Vector3 GetPlayerGunPos();
	void SetRotateY(float AngleY);
public:
	//�J���[
	Vector4 mColor;
private:
	void RotateMovePlayer();
	//��������
	void Deceleration(Vector3& pos);
	//�v���C���[�ʂ̐ݒ�
	void PlayerNumSet(PLAYER_NUMBER num);
	//�v���C���[�A�j���[�V����
	void PlayerAnimetion(PlayerState state);
	//�p�[�e�B�N�����ݒ�
	void ParticleSetting();
	//�p�[�e�B�N��update
	void ParticleUpdate();
//�v���C���[�̍s���n
private:
	void Move();
	void AttackMove();
	void Jump();
	void Respawn();
private:
	//�v���C���[���
	PlayerAttackState mAttackState;
	//1�t���[���O�̃|�W�V����
	Vector3 mCoppyPos;
	Vector3 mVecPos;

	//�J����
	CameraActor* mCameraActor;
	Matrix4 mCameraMat;
	Vector3 mCameraPos;
	Vector3 mPosition;
	Vector3 mRotate;

	//�v���C���[�n
	PlayerState mPlayerState;
	Vector3 mVelocity;
	Vector3 mPlayerVelocity;
	Vector3 mCurPlayerPos;
	float mAngleY;
	bool mLowStateFlag;
	float mPlayerSpeed;
	//�d�̓t���O
	bool mGravityFlag;
	//�v���C���[�W�����v
	bool mJumpFlag;
	float mJumpCount;
	//�U���󂯂����̃m�b�N�o�b�N�֌W
	bool mIsDamageMachine;
	bool mIsDamageSniper;
	bool mIsDamageShot;
	Vector3 mKnockBackVelo;

	//���X�|�[���֌W
	float mRespawnCount;
	Vector3 mRespawnPoint;
	bool mDropDownFlag;
	//���O�Ɏ󂯂��_���[�W
	PLAYER_NUMBER mDamagePlayerNumber;
	//���O�ɍU�����ꂽ�v���C���[�̃|�W�V����
	Vector3 mDamagePlayerPos;
	//�X�i�C�p�[�ɑ΂��Ă̖��G�֌W
	float mSniperCount;
	bool mSniperFlag;


	//���f��ID
	MODEL_ID mModelId;
	//pad���
	int mPad;
	//�_���[�WUI�̍��W
	Vector2 mUiDamagePos;
	//�_���[�W�o�b�NUI�̍��W
	Vector2 mUiDamageBackPos;
	//�A�j���[�V�����N���X
	std::shared_ptr<AnimationClass> mAnim;
	//�p�b�h�̃x�N�g��
	Vector2 mPadVec;

	//�v���C���[�p�[�e�B�N���V�X�e�����
	ActorPtr mDashParticle;
	ParticleEffectSystem::ParticleSetting mDashParticleSet;

};