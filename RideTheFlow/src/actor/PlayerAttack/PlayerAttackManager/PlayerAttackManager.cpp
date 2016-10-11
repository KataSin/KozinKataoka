#include "PlayerAttackManager.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

#include "../../PlayerBullet/TargetRay.h"
#include "../SniperGunLine/SniperGunLine.h"
PlayerAttackManager::PlayerAttackManager(IWorld& world, Actor& player) :
	Actor(world),
	overHertCount(0.0f),
	isColSniperCount(0.0f),
	initSniperFalg(true)
{
	mSniperState.isColSniperLine = false;
	mSniperState.chargeSniperCount = 100.0f;
	mSniperState.doCharge = false;

	mPlayer = &player;
	parameter.isDead = false;
	//���������ݒ�
	attackState = PlayerAttackState::MACHINE_GUN;
	//���v���C���[�ݒ�
	parameter.playNumber = player.GetParameter().playNumber;
	//�^�[�Q�b�g��ǉ�
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//world.Add(ACTOR_ID::SNIPER_LINE_ACTOR, std::make_shared<SniperGunLine>(world, *this));

	//�J�������擾
	mCamera = dynamic_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	//�N�̒e���̏���ݒ�
	bulletState.playerNumber = mPlayer->GetParameter().playNumber;
	//�p�b�h�̃v���C���[�ݒ�
	switch (mPlayer->GetParameter().playNumber)
	{
	case PLAYER_NULL:
		break;
	case PLAYER_1:
		pad = PADNUM::PAD1;
		break;
	case PLAYER_2:
		pad = PADNUM::PAD2;
		break;
	case PLAYER_3:
		pad = PADNUM::PAD3;
		break;
	case PLAYER_4:
		pad = PADNUM::PAD4;
		break;
	}
}

PlayerAttackManager::~PlayerAttackManager()
{

}

void PlayerAttackManager::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J))
		attackState = PlayerAttackState::MACHINE_GUN;

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::K))
		attackState = PlayerAttackState::SNIPER_GUN;

	//�����ނɂ���Ă̍U��
	if (dynamic_cast<Player*>(mPlayer)->GetPlayerState() != PlayerState::PLAYERRESPAWN)
		PlayerAttack(attackState);
}

void PlayerAttackManager::Draw() const
{
}

void PlayerAttackManager::OnCollide(Actor & other, CollisionParameter colpara)
{
}

void PlayerAttackManager::PlayerAttack(PlayerAttackState state)
{
	switch (state)
	{
	case PlayerAttackState::MACHINE_GUN:
	{
		mCamera->SetTargetDistance(30.0f);
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		mCamera->SetTargetDistance(100.0f);
		SniperGun();
		break;
	}
	}
}

void PlayerAttackManager::MachineGun()
{
	if ((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad)) &&
		overHertCount < 100.0f)
	{
		overHertCount += Time::DeltaTime;
		if (overHertCount >= 0.1f)
		{
			//overHertCount += 2.0f;
			//���_�̈ʒu��ݒ�
			bulletState.vertexPoint = mCamera->GetTarget();
			//���̈ʒu���炢���甭��
			bulletState.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, bulletState));
			overHertCount += 2.0f;
		}
	}
	else
	{
		overHertCount = 2.0f;
	}

	overHertCount = Math::Clamp(overHertCount, 0.0f, 100.0f);
}

void PlayerAttackManager::SniperGun()
{
	//�������ςȂ��Ń`���[�W
	if (((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))) &&
		!mSniperState.isColSniperLine)
	{
		if (initSniperFalg)
		{
			mSniperState.chargeSniperCount = 10.0f;
			initSniperFalg = false;
		}
		//�`���[�W����u�Ԃɐ����ő�܂ň�u�����L�т�Ă��܂��h�~
		if(mSniperState.chargeSniperCount>=12.0f)
			mSniperState.doCharge = true;
		mSniperState.chargeSniperCount += 50.0f*Time::DeltaTime;
		mSniperState.chargeSniperCount
			= Math::Clamp(mSniperState.chargeSniperCount, 10.0f, 100.0f);

	}
	//��������Line�ɂ����蔻���t����
	else if (mSniperState.doCharge)
	{
		mSniperState.isColSniperLine = true;
		mSniperState.doCharge = false;
	}
	//������������0.1�b��ɂ����蔻�薳����
	if (mSniperState.isColSniperLine)
	{
		isColSniperCount += Time::DeltaTime;
		if (isColSniperCount >= 0.1f)
		{
			isColSniperCount = 0.0f;
			mSniperState.isColSniperLine = false;
			mSniperState.chargeSniperCount = 100.0f;
			initSniperFalg = true;
		}
	}

}
