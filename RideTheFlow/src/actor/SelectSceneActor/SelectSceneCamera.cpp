#include "SelectSceneCamera.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../Collision.h"

#include "../../camera/Camera.h"
SelectSceneCamera::SelectSceneCamera(IWorld & word, const Vector3 & position, const Vector3 & target):
	Actor(world),
	mPosition(position),
	mTarget(target)
{
}

SelectSceneCamera::~SelectSceneCamera()
{
}

void SelectSceneCamera::Update()
{
	//ÉJÉÅÉâê›íË
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(mTarget);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
}

void SelectSceneCamera::Draw() const
{
}

void SelectSceneCamera::OnCollide(Actor & other, CollisionParameter colpara)
{
}
