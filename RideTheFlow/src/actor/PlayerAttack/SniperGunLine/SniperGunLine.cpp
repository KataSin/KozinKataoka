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
	//�e�ϊ��n
	//mManager = dynamic_cast<PlayerAttackManager*>(&manager);
	//mPlayer  = dynamic_cast<Player*>(world.GetPlayer(manager.GetParameter().playNumber).get());
	//mCamera  = dynamic_cast<CameraActor*>(world.GetCamera(manager.GetParameter().playNumber).get());
}

SniperGunLine::~SniperGunLine()
{
}

void SniperGunLine::Update()
{
	////�e�̈ʒu����X�i�C�p�[�^�[�Q�b�g�̈ʒu�̃x�N�g�����v�Z
	//Vector3 vec = (mCamera->GetTarget() - mPlayer->GetPlayerGunPos()).Normalized();
	////�ǂ̂��炢Line���L�т邩��Manager�̃`���[�W�J�E���g���g���Čv�Z
	//endPos = mPlayer->GetPlayerGunPos() + vec*mManager->GetChargeCount().chargeSniperCount;
}

void SniperGunLine::Draw() const
{
	//DrawLine3D(Vector3::ToVECTOR(mPlayer->GetPlayerGunPos()), Vector3::ToVECTOR(endPos), 1);
}

void SniperGunLine::OnCollide(Actor & other, CollisionParameter colpara)
{

}
