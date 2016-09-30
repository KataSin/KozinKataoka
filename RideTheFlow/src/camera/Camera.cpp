#include "Camera.h"
#include <Dxlib.h>
#include "../math/Math.h"
#include "../math/Matrix4.h"
#include "../input/Keyboard.h"

// �J�����̍X�V����
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(VGet(Position.Get().x, Position.Get().y, Position.Get().z),
		VGet(Target.Get().x, Target.Get().y, Target.Get().z),
		VGet(Up.Get().x, Up.Get().y, Up.Get().z));
}

// �J�����̕`�拗����ݒ肷��i��O�����A�������j
void Camera::SetRange(float Near, float Far)
{
	SetCameraNearFar(Near, Far);
}

// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
void Camera::SetRotation(Vector3 rotate)
{
	SetCameraPositionAndAngle(VGet(Position.Get().x, Position.Get().y, Position.Get().z), rotate.x, rotate.y, rotate.z);
}

// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
int Camera::IsCheckView(Vector3 position)
{
	return CheckCameraViewClip(VGet(position.x, position.y, position.z));
}

void Camera::SetViewAngle(float degree)
{
	SetupCamera_Perspective(Math::Radian(degree));
}

void Camera::Draw()
{
}
