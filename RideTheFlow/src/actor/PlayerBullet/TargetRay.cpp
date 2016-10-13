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
	mColPos(Vector3::Zero),
	isCol(false),
	mColSniperPos(Vector3::Zero),
	isSniperCol(false)
{
	//変換
	mManager = dynamic_cast<PlayerAttackManager*>(&manager);

	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = manager.GetParameter().playNumber;
	parameter.id = ACTOR_ID::PLAYER_BULLET_ACTOR;
	parameter.radius = 0.5f;
	//UIを追加
	world.UIAdd(UI_ID::TARGET_UI, std::make_shared<Target>(world, this));
}

TargetRay::~TargetRay()
{
}

void TargetRay::Update()
{
	attackState = dynamic_cast<PlayerAttackManager*>(mManager)->GetState();

	//武器ごとのlineとステージとのあたり判定
	if (attackState == PlayerAttackState::MACHINE_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_GUNRAY_COL);
	else if (attackState == PlayerAttackState::SNIPER_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::SNIPERLINE_PLATE_COL);

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_GUNLINE_COL);

	//スナイパーlineとプレイヤーのあたり判定（ボタンを離した瞬間だけ）
	if (mManager->GetChargeCount().isColSniperLine)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_SNIPERLINE_COL);

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

	//フラグ初期化
	isCol = false;
	isSniperCol = false;
}

void TargetRay::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, parameter.mat);
	Player* player;
	player = dynamic_cast<Player*>(world.GetPlayer(mManager->GetParameter().playNumber).get());
	DrawLine3D(Vector3::ToVECTOR(player->GetPlayerGunPos()),
		Vector3::ToVECTOR(parameter.mat.GetPosition()), 1);

	if (mManager->GetChargeCount().doCharge)
		DrawLine3D(Vector3::ToVECTOR(player->GetPlayerGunPos()),
			Vector3::ToVECTOR(parameter.mat.GetPosition()), 1);
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
	if (colpara.colID == COL_ID::PLAYER_GUNLINE_COL)
	{
		mColPos = colpara.colPos;
		mColSniperPos = colpara.colPos;
		isCol = true;
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
		parameter.mat = Matrix4::Translate(GetSniperLine().endPos);
	}
}
