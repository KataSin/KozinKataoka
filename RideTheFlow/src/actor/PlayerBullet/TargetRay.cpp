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
	mIsCol(false),
	mColSniperPos(Vector3::Zero),
	mIsSniperCol(false),
	mIsPlayerCol(false)
{
	//変換
	mManager = dynamic_cast<PlayerAttackManager*>(&manager);

	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = manager.GetParameter().playNumber;
	parameter.id = ACTOR_ID::PLAYER_BULLET_ACTOR;
	parameter.radius = 0.5f;
	//UIを追加
	world.UIAdd(UI_ID::TARGET_UI, std::make_shared<Target>(world, manager, *this));
}

TargetRay::~TargetRay()
{
}

void TargetRay::Update()
{
	mAttackState = dynamic_cast<PlayerAttackManager*>(mManager)->GetState();

	//一番近い当たったポジションにする
	if (mIsCol) {
		Vector3 playerPos = dynamic_cast<Player*>(world.GetPlayer(mManager->GetParameter().playNumber).get())->GetPlayerGunPos();
		Vector3 colPos = Vector3(999999);
		for (auto& i : mColVectorPos) {
			if (Vector3::Distance(playerPos, i) <= Vector3::Distance(colPos, playerPos))
				colPos = i;
		}
		if (mIsSniperCol)
			mColSniperPos = colPos;
		else if (mIsCol)
			mColPos = colPos;
		else if (mIsPlayerCol)
		{
			mColSniperPos = colPos;
			mColPos = colPos;
		}
		mColVectorPos.clear();
	}

	//武器ごとのlineとステージとのあたり判定
	if (mAttackState == PlayerAttackState::MACHINE_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_GUNRAY_COL);
	else if (mAttackState == PlayerAttackState::SNIPER_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::SNIPERLINE_PLATE_COL);

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_GUNLINE_COL);

	//どのターゲット移動をするか
	switch (mAttackState)
	{
	case PlayerAttackState::MACHINE_GUN:
	{
		MachineGun();
		break;
	}
	case PlayerAttackState::SHOT_GUN:
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
	mIsCol = false;
	mIsSniperCol = false;
	mIsPlayerCol = false;
}

void TargetRay::Draw() const
{

}


void TargetRay::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_GUNRAY_COL)
	{
		mColVectorPos.push_back(colpara.colPos);
		mIsCol = true;
	}
	if (colpara.colID == COL_ID::SNIPERLINE_PLATE_COL)
	{
		mColSniperPos = colpara.colPos;
		mColVectorPos.push_back(colpara.colPos);
		mIsCol = true;
		mIsSniperCol = true;
	}
	if (colpara.colID == COL_ID::PLAYER_GUNLINE_COL)
	{
		mColVectorPos.push_back(colpara.colPos);

		mIsPlayerCol = true;
	}
}
Line TargetRay::GetLine()
{
	//Lineを生成
	Line line;
	Player* player = dynamic_cast<Player*>(world.GetPlayer(parameter.playNumber).get());
	line.startPos = Vector3(player->GetPlayerGunPos());
	CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
	line.endPos = camera->GetTarget();
	return line;
}
Line TargetRay::GetSniperLine()
{
	Player* player = dynamic_cast<Player*>(world.GetPlayer(parameter.playNumber).get());
	CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
	//銃の位置からスナイパーターゲットの位置のベクトルを計算
	Vector3 vec = (camera->GetTarget() - player->GetPlayerGunPos()).Normalized();
	Line playerGun;
	playerGun.startPos = player->GetPlayerGunPos();
	//どのくらいLineが伸びるかをManagerのチャージカウントを使って計算
	playerGun.endPos = player->GetPlayerGunPos() + vec*mManager->GetChargeCount().chargeSniperCount;
	return playerGun;
}
PlayerAttackState TargetRay::GetState()
{
	return mAttackState;
}
bool TargetRay::colFlag()
{
	return mManager->GetChargeCount().isColSniperLine;
}
bool TargetRay::GetPlayerSniperLineCol()
{
	return mIsPlayerCol;
}
//マシンガン＆ショットガン用ターゲット移動
void TargetRay::MachineGun()
{
	if (mIsCol)
	{
		parameter.mat = Matrix4::Translate(mColPos);
	}
	else
	{
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		parameter.mat = Matrix4::Translate(camera->GetTarget());
	}

}
//スナイパー用ターゲット移動
void TargetRay::SniperGun()
{
	if (mIsSniperCol)
	{
		parameter.mat = Matrix4::Translate(mColSniperPos);
	}
	else
	{
		CameraActor* camera = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
		parameter.mat = Matrix4::Translate(GetSniperLine().endPos);
	}
}
