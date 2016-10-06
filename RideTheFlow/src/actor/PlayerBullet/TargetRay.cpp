#include "TargetRay.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../../UIactor/Target/Target.h"

const float SniperLine = 20.0f;
TargetRay::TargetRay(IWorld & world, Actor& manager) :
	Actor(world),
	mManager(&manager),
	mColPos(Vector3::Zero),
	isCol(false),
	mColSniperPos(Vector3::Zero),
	isSniperCol(false)
{
	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = manager.GetParameter().playNumber;
	parameter.id = ACTOR_ID::PLAYER_BULLET_ACTOR;
	parameter.radius = 0.5f;
	//UIÇí«â¡
	world.UIAdd(UI_ID::TARGET_UI, std::make_shared<Target>(world, this));
}

TargetRay::~TargetRay()
{
}

void TargetRay::Update()
{
	attackState = dynamic_cast<PlayerAttackManager*>(mManager)->GetState();

	if(attackState==PlayerAttackState::MACHINE_GUN)
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_GUNRAY_COL);
	else
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::SNIPERLINE_PLATE_COL);

	switch (attackState)
	{
	case PlayerAttackState::MACHINE_GUN:
	{
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		SniperGun();
		break;
	}
	}

	//ÉtÉâÉOèâä˙âª
	isCol = false;
	isSniperCol = false;
}

void TargetRay::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, parameter.mat);

}


void TargetRay::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_GUNRAY_COL)
	{
		mColPos = colpara.colPos;
		isCol = true;
	}
	if (colpara.colID == COL_ID::SNIPERLINE_PLATE_COL)
	{
		mColSniperPos = colpara.colPos;
		isSniperCol = true;
	}
}

void TargetRay::MachineGun()
{
	if (isCol)
	{
		parameter.mat = Matrix4::Translate(mColPos);
	}
	else
	{
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		parameter.mat = Matrix4::Translate(camera->GetTarget());
	}

}

void TargetRay::SniperGun()
{
	if (isSniperCol)
	{
		parameter.mat = Matrix4::Translate(mColSniperPos);
	}
	else
	{
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		parameter.mat = Matrix4::Translate(camera->GetTarget());
	}
}
