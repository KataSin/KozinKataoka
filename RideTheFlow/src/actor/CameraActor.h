#pragma once
#include "Actor.h"
#include "../camera/Camera.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include <memory>
#include "Collision.h"
#include <vector>
//#include "Player.h"

//�J�������x
const float CameraSpeed = 100.0f;
//�J�����ƃv���C���[�̋���
const float CameraDis = 20.0f;

class Player;

enum CameraState
{
	DEFAULT,
	ATTACKMACHINEGUN,
	ATTACKSNIPERGUN,
	ATTACKSHOTGUN,
	DROP_DOWN_CAMERA,
	KILL_CAMERA,
};

class CameraActor :public Actor, public std::enable_shared_from_this<CameraActor>
{
public:
	CameraActor(IWorld& world, Actor &parent_, float angleY);
	~CameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor & other, CollisionParameter colpara);

private:
	//�o�l�␳
	void SpringCamra(const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass);
private:
	//�J�����̏�Ԋ֐�
	void StateUpdate(CameraState state);
	void Default();
	void KillCmaera();
	void DropDownCamera();

public:
	//�J�����̏�Ԃ��Z�b�g����
	void SetCameraState(CameraState state);
	//�e��ł^�[�Q�b�g�̈ʒu���擾
	Vector3 GetTarget();
	//�^�[�Q�b�g�̉�����ݒ�
	void SetTargetDistance(float dis)
	{
		mDis = dis;
	}
	//�\���ʒu�ݒ�
	void SetCamera();
	//�����_�ƃJ������Line���擾
	Line GetCameraLine()
	{
		Line line;
		line.startPos = target;
		line.endPos = Vector3(0, 0, 1)*CameraDis
			*Matrix4::RotateX(rotateLeft)*Matrix4::RotateY(rotateUp)
			+ playerMat.GetPosition();
		return line;
	}
private: 
	//�J�����̕ʂ̃}�g���N�X
	Matrix4 CameraMat;
	Vector3 mPosition;
	//�J�����X�^�e
	CameraState cameraState;
	//�����_
	Vector3 target;
	//�o�l�J����
	Vector3 restPos;
	Vector3 velocity;

	//�J�����̊p�x
	float rotateLeft;
	float rotateUp;

	//�L���J����
	float killRotateY;
	//�v���C���[���
	Player* mPlayer;
	Matrix4 playerMat;
	//�p�b�h�̏��
	int pad;
	//�J�����̓��������֌W
	Vector3 isColPos;
	std::vector<Vector3>isColVectorPos;
	bool isColFlag;
	//�^�[�Q�b�g�ƃv���C���[�̋���
	float mDis;
};