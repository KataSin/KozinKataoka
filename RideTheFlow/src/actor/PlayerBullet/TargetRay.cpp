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
TargetRay::TargetRay(IWorld & world, Actor& target) :
	Actor(world),
	mTarget(&target),
	mColPos(Vector3::Zero),
	isCol(false)
{
	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = target.GetParameter().playNumber;
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
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_GUNRAY_COL);

	if (isCol)
	{
		parameter.mat = Matrix4::Translate(mColPos);
	}
	else
	{
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		parameter.mat = Matrix4::Translate(camera->GetTarget());
	}

	//ÉtÉâÉOèâä˙âª
	isCol = false;
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
}

void TargetRay::MachineGun()
{

}

void TargetRay::SniperGun()
{
}
