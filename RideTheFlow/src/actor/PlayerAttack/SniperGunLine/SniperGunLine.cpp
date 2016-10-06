#include "SniperGunLine.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

SniperGunLine::SniperGunLine(IWorld & world, Actor& manager):
	Actor(world)
{
	parameter.isDead = false;
	parameter.playNumber = manager.GetParameter().playNumber;
	//各変換系
	//mManager = dynamic_cast<PlayerAttackManager*>(&manager);
	//mPlayer  = dynamic_cast<Player*>(world.GetPlayer(manager.GetParameter().playNumber).get());
	//mCamera  = dynamic_cast<CameraActor*>(world.GetCamera(manager.GetParameter().playNumber).get());
}

SniperGunLine::~SniperGunLine()
{
}

void SniperGunLine::Update()
{
	////銃の位置からスナイパーターゲットの位置のベクトルを計算
	//Vector3 vec = (mCamera->GetTarget() - mPlayer->GetPlayerGunPos()).Normalized();
	////どのくらいLineが伸びるかをManagerのチャージカウントを使って計算
	//endPos = mPlayer->GetPlayerGunPos() + vec*mManager->GetChargeCount().chargeSniperCount;
}

void SniperGunLine::Draw() const
{
	//DrawLine3D(Vector3::ToVECTOR(mPlayer->GetPlayerGunPos()), Vector3::ToVECTOR(endPos), 1);
}

void SniperGunLine::OnCollide(Actor & other, CollisionParameter colpara)
{

}
