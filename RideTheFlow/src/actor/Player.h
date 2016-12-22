#pragma once
#include "Actor.h"
#include <memory>
#include "PlayerBullet\PlayerBullet.h"
#include "CameraActor.h"
#include "ID.h"
#include "../graphic/AnimetionClass.h"

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
		return parameter.mat.GetPosition() + Vector3(0.0f, 2.0f, 0.0f);
	}
	void SetRotateY(float AngleY)
	{
		angleY = AngleY;
	}
public:
	//�J���[
	Vector4 mColor;
private:
	void RotateMovePlayer();
	//��������
	void Deceleration(Vector3& pos);
	//�v���C���[�ʂ̐ݒ�
	void PlayerNumSet(PLAYER_NUMBER num);
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

	Vector3 mPosition;
	Vector3 mRotate;

	//�v���C���[�̏��
	PlayerState playerState;
	Matrix4 playerModelMat;
	Vector3 mVelocity;
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

	Vector3 cameraPos;
	//���f��ID
	MODEL_ID mModelId;
	//pad���
	int pad;
	//�_���[�WUI�̍��W
	Vector2 uiDamagePos;
	//�A�j���[�V�����N���X
	AnimationClass* animeClass;


};