#include "CameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include "../math/Quaternion.h"
#include "../math/Math.h"
#include"Player.h"
#include <string>
#include "../input/GamePad.h"

CameraActor::CameraActor(IWorld& world, Actor &parent_) :
	Actor(world),
	mPlayer(dynamic_cast<Player*>(&parent_)),
	cameraState(CameraState::DEFAULT),
    mPosition(Vector3::Zero),
	velocity(Vector3::Zero),
	rotateLeft(0.0f),
	rotateUp(0.0f),
	killRotateY(0.0f)
{
	//�J�����ƃv���C���[�̕R�Â�
	parent = &parent_;
	playerMat = parent->GetParameter().mat;

	target = playerMat.GetPosition() + Vector3(0, 10, 0);

	parameter.playNumber = parent_.GetParameter().playNumber;
	parameter.isDead = false;
	parameter.mat = Matrix4::Scale(0)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);

	//�p�b�h�̐ݒ�
	switch (parameter.playNumber)
	{
	case PLAYER_NULL:
		break;
	case PLAYER_1:
		pad = PADNUM::PAD1;
		break;
	case PLAYER_2:
		pad = PADNUM::PAD2;
		break;
	case PLAYER_3:
		pad = PADNUM::PAD3;
		break;
	case PLAYER_4:
		pad = PADNUM::PAD4;
		break;
	}


	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(target);
	Camera::GetInstance().Up.Set(Vector3::Up);


}
CameraActor::~CameraActor()
{

}
void CameraActor::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::CAMERA_PLATE_COL);

	playerMat = parent->GetParameter().mat;
	mPlayer = dynamic_cast<Player*>(parent);

	StateUpdate(cameraState);


	Vector3 cameraFront = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3::Up).Normalized();
	Vector3 cameraUp = Vector3::Cross(cameraFront, cameraLeft);

	//�J�����̌�������}�g���N�X�𐶐�
	parameter.mat.SetFront(cameraFront);
	parameter.mat.SetLeft(cameraLeft);
	parameter.mat.SetUp(cameraUp);
	//�J�����̏�Q���ɓ����������̕␳�֌W
	if (isColFlag)
	{
		mPosition = isColPos;
	}
	parameter.mat.SetPosition(mPosition);
	isColFlag = false;
}
void CameraActor::Draw() const
{

}

void CameraActor::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (COL_ID::CAMERA_PLATE_COL == colpara.colID)
	{
		isColFlag = true;
		isColPos = colpara.colPos;
	}

}

void CameraActor::SpringCamra(const Vector3 & restPosition,
	float stiffness, float friction, float mass)
{
	// �o�l�̐L�ы���v�Z
	Vector3 stretch = mPosition - restPosition;
	// �o�l�̗͂��v�Z
	Vector3 force = -stiffness * stretch;
	// �����x���v�Z
	Vector3 acceleration = force / mass;
	// �ړ��ʂ��v�Z
	velocity = friction * (velocity + acceleration);
	// ���W�̍X�V
	mPosition += velocity;
}

void CameraActor::StateUpdate(CameraState state)
{
	switch (state)
	{
	case DEFAULT:
		Default();
		break;
	case ATTACK:
		Attack();
		break;
	case ATTACKCHARGE:
		AttackCharge();
		break;
	case KILL_CAMERA:
		KillCmaera();
		break;
	}
}

void CameraActor::Default()
{
	Vector2 vec = GamePad::GetInstance().RightStick(pad);
	rotateUp += vec.x*CameraSpeed*Time::DeltaTime;
	rotateLeft -= vec.y*CameraSpeed*Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	{
		rotateUp += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	{
		rotateUp -= CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
	{
		rotateLeft += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
	{
		rotateLeft -= CameraSpeed*Time::DeltaTime;
	}

	//Z����]����
	rotateLeft = Math::Clamp(rotateLeft, -65.0f, 20.0f);
	target = playerMat.GetPosition() + Vector3(0, 6, 0);
	mPosition = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(rotateLeft)*Matrix4::RotateY(rotateUp)
		+ playerMat.GetPosition();
}

void CameraActor::Attack()
{
	Vector2 vec = GamePad::GetInstance().RightStick(pad);
	rotateUp += vec.x*CameraSpeed*Time::DeltaTime;
	rotateLeft -= vec.y*CameraSpeed*Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	{
		rotateUp += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	{
		rotateUp -= CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
	{
		rotateLeft += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
	{
		rotateLeft -= CameraSpeed*Time::DeltaTime;
	}

	//Z����]����
	rotateLeft = Math::Clamp(rotateLeft, -65.0f, 20.0f);
	target = playerMat.GetPosition() + Vector3(0, 6, 0);
	mPosition = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(-rotateLeft)*Matrix4::RotateY(rotateUp)
		+ playerMat.GetPosition();
}

void CameraActor::AttackCharge()
{

}

void CameraActor::KillCmaera()
{
	//�|���ꂽ����̎擾
	Player* killPlayer;
	PLAYER_NUMBER num;
	num = dynamic_cast<Player*>(parent)->GetDamagePlayer();
	killPlayer = dynamic_cast<Player*>(world.GetPlayer(num).get());

	//�|���ꂽ����̉������邭���
	killRotateY += 70.0f*Time::DeltaTime;
	restPos = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(-30)*Matrix4::RotateY(killRotateY)
		+ killPlayer->GetParameter().mat.GetPosition();
	//�����_���ύX
	target = killPlayer->GetParameter().mat.GetPosition() + Vector3(0, 2, 0);
	SpringCamra(restPos, 1.0f, 0.2f, 1.0f);
}
Vector3 CameraActor::GetTarget()
{
	//�����_�ƃJ�����̃|�W�V�����̃x�N�g��
	Vector3 targetVec = (target - parameter.mat.GetPosition()).Normalized();
	//�����ɋ�������
	Vector3 targetPos = targetVec * 30.0f + parameter.mat.GetPosition();
	//��̕␳
	return targetPos + Vector3(0.0f, 0.5f, 0.0f);
}

void CameraActor::SetCameraState(CameraState state)
{
	cameraState = state;
}
