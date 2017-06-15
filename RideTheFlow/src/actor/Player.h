#pragma once
#include "Actor.h"
#include "ActorPtr.h"
#include <memory>
#include "PlayerBullet\PlayerBullet.h"
#include "CameraActor.h"
#include "ID.h"
#include "../graphic/AnimetionClass.h"
#include "../ParticleEffectSystem/ParticleEffectSystem.h"
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
	void SetPlayerState(PlayerState state) {
		playerState = state;
	}
	PlayerState GetPlayerState();
	PLAYER_NUMBER GetDamagePlayer();
	//�e�̏o���ʒu�擾
	Vector3 GetPlayerGunPos() {
		return parameter.mat.GetPosition()-(parameter.mat.GetFront().Normalized()*4.0f) + Vector3(0.0f, 2.7f, 0.0f);
	}
	void SetRotateY(float AngleY)
	{
		angleY = AngleY;
	}
	Vector3 GetPlayerVelo();
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
	PlayerAttackState attackState;
	//1�t���[���O�̃|�W�V����
	Vector3 coppyPos;
	Vector3 vecPos;

	//�J����
	CameraActor* cameraActor;
	Matrix4 cameraMat;
	Vector3 cameraPos;
	Vector3 mPosition;
	Vector3 mRotate;

	//�v���C���[�̏��
	PlayerState playerState;
	Matrix4 playerModelMat;
	Vector3 mVelocity;
	Vector3 mPlayerVelocity;
	Vector3 mCurPlayerPos;
	float angleY;
	bool lowStateFlag;
	float playerSpeed;
	//�d�̓t���O
	bool gravityFlag;

	//�v���C���[�W�����v
	bool jumpFlag;
	float jumpCount;
	//�U���󂯂����̃m�b�N�o�b�N�֌W
	bool isDamageMachine;
	bool isDamageSniper;
	bool isDamageShot;
	Vector3 knockBackVelo;

	//���X�|�[���֌W
	float respawnCount;
	bool respawnFlag;
	Vector3 respawnPoint;
	bool dropDownFlag;
	//���O�Ɏ󂯂��_���[�W
	PLAYER_NUMBER damagePlayerNumber;
	//���O�ɍU�����ꂽ�v���C���[�̃|�W�V����
	Vector3 damagePlayerPos;
	//�X�i�C�p�[�ɑ΂��Ă̖��G�֌W
	float sniperCount;
	bool sniperFlag;


	//���f��ID
	MODEL_ID mModelId;
	//pad���
	int pad;
	//�_���[�WUI�̍��W
	Vector2 uiDamagePos;
	//�_���[�W�o�b�NUI�̍��W
	Vector2 uiDamageBackPos;
	//�A�j���[�V�����N���X
	AnimationClass* animeClass;
	//�p�b�h�̃x�N�g��
	Vector2 padVec;

	//�v���C���[�p�[�e�B�N���V�X�e�����
	ActorPtr mDashParticle;
	ParticleEffectSystem::ParticleSetting mDashParticleSet;

};