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
	isSniperCol(false),
	mIsPlayerCol(false)
{
	//�ϊ�
	mManager = dynamic_cast<PlayerAttackManager*>(&manager);

	parameter.mat = Matrix4::Translate(Vector3::Zero);
	parameter.isDead = false;
	parameter.playNumber = manager.GetParameter().playNumber;
	parameter.id = ACTOR_ID::PLAYER_BULLET_ACTOR;
	parameter.radius = 0.5f;
	//UI��ǉ�
	world.UIAdd(UI_ID::TARGET_UI, std::make_shared<Target>(world, manager, *this));
}

TargetRay::~TargetRay()
{
}

void TargetRay::Update()
{
	attackState = dynamic_cast<PlayerAttackManager*>(mManager)->GetState();

	//��ԋ߂����������|�W�V�����ɂ���
	if (isCol) {
		Vector3 playerPos = dynamic_cast<Player*>(world.GetPlayer(mManager->GetParameter().playNumber).get())->GetPlayerGunPos();
		Vector3 colPos = Vector3(999999);
		for (auto& i : mColVectorPos) {
			if (Vector3::Distance(playerPos, i) <= Vector3::Distance(colPos, playerPos))
				colPos = i;
		}
		if (isSniperCol)
			mColSniperPos = colPos;
		else if (isCol)
			mColPos = colPos;
		else if (mIsPlayerCol)
		{
			mColSniperPos = colPos;
			mColPos = colPos;
		}
		mColVectorPos.clear();
	}

	//���킲�Ƃ�line�ƃX�e�[�W�Ƃ̂����蔻��
	if (attackState == PlayerAttackState::MACHINE_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::PLATE_GUNRAY_COL);
	else if (attackState == PlayerAttackState::SNIPER_GUN)
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::SNIPERLINE_PLATE_COL);

	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_GUNLINE_COL);

	//�ǂ̃^�[�Q�b�g�ړ������邩
	switch (attackState)
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

	//�t���O������
	isCol = false;
	isSniperCol = false;
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
		isCol = true;
	}
	if (colpara.colID == COL_ID::SNIPERLINE_PLATE_COL)
	{
		mColSniperPos = colpara.colPos;
		mColVectorPos.push_back(colpara.colPos);
		isCol = true;
		isSniperCol = true;
	}
	if (colpara.colID == COL_ID::PLAYER_GUNLINE_COL)
	{
		mColVectorPos.push_back(colpara.colPos);

		mIsPlayerCol = true;
	}
}
//�}�V���K�����V���b�g�K���p�^�[�Q�b�g�ړ�
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
//�X�i�C�p�[�p�^�[�Q�b�g�ړ�
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
