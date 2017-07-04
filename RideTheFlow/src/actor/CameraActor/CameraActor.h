#pragma once
#include "../Actor.h"
#include "../Collision.h"
#include <memory>
#include <vector>

//�J�������x
const float CameraSpeed = 100.0f;
//�J�����ƃv���C���[�̋���
const float CameraDis = 30.0f;

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
	void SetCameraPoint(const Vector2& center, const Vector2& areaMin, const Vector2& areaMax);

public:
	//�J�����̏�Ԃ��Z�b�g����
	void SetCameraState(CameraState state);
	//�e��ł^�[�Q�b�g�̈ʒu���擾
	Vector3 GetTarget();
	//�^�[�Q�b�g�̉�����ݒ�
	void SetTargetDistance(float dis);
	//�\���ʒu�ݒ�
	void SetCamera(int num);
	//�����_�ƃJ������Line���擾
	Line GetCameraLine();
private: 
	//�J�����̕ʂ̃}�g���N�X
	Matrix4 mCameraMat;
	Vector3 mPosition;
	//�J�����X�^�e
	CameraState mCameraState;
	//�����_
	Vector3 mTargetPos;
	//�o�l�J����
	Vector3 mRestPos;
	Vector3 mVelocity;

	//�J�����̊p�x
	float mRotateLeft;
	float mRotateUp;

	//�L���J����
	float mKillRotateY;
	//�v���C���[���
	Player* mPlayer;
	Matrix4 mPlayerMat;
	//�p�b�h�̏��
	int mPad;
	//�J�����̓��������֌W
	Vector3 mIsColPos;
	std::vector<Vector3>mIsColVectorPos;
	bool mIsColFlag;
	//�^�[�Q�b�g�ƃv���C���[�̋���
	float mDis;
};