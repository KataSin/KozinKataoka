#include "TargetRay.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../../UIactor/Target/Target.h"
TargetRay::TargetRay(IWorld & world, Player& player) :
	Actor(world),
	mPlayer(&player),
	mColPos(Vector3::Zero),
	isCol(false)
{
	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = player.GetParameter().playNumber;
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
	switch (attackState)
	{
	case PlayerAttackState::MACHINE_GUN:

	}
	if (isCol)
	{
		parameter.mat = Matrix4::Translate(mColPos);
	}
	else
	{
		parameter.mat = Matrix4::Translate(mPlayer->GetBulletTarget());
	}
	//ÉtÉâÉOèâä˙âª
	isCol = false;
}

void TargetRay::Draw() const
{
	//Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, parameter.mat);
}


void TargetRay::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_GUNRAY_COL)
	{
		mColPos = colpara.colPos;
		isCol = true;
	}
}
