#include "PlayerAttackManager.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

#include "../../PlayerBullet/TargetRay.h"
#include "../../../UIactor/AttackGauge/AttackGauge.h"

//����̃I�[�o�[�q�[�g�l
const float OverHertMachine = 2.0f;
const float OverHertSniper = 50.0f;
const float OverHertShot = 30.0f;

PlayerAttackManager::PlayerAttackManager(IWorld& world, Actor& player) :
	Actor(world),
	overHertCount(100.0f),
	machineAttackCount(0.1f),
	isColSniperCount(0.0f),
	coolHertCount(0.0f),
	attackFlag(0.0f),
	shotAttackCount(0.0f),
	initSniperFalg(true)
{
	mSniperState.isColSniperLine = false;
	mSniperState.chargeSniperCount = 100.0f;
	mSniperState.doCharge = false;

	mPlayer = dynamic_cast<Player*>(&player);
	parameter.isDead = false;
	//���������ݒ�
	attackState = PlayerAttackState::SHOT_GUN;
	//���v���C���[�ݒ�
	parameter.playNumber = player.GetParameter().playNumber;
	//�^�[�Q�b�g��ǉ�
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//�I�[�o�[�q�[�g�Q�[�W��ǉ�
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, this));

	//�J�������擾
	mCamera = dynamic_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	////�N�̒e���̏���ݒ�
	//bulletState.playerNumber = mPlayer->GetParameter().playNumber;
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


	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::H))
		attackState = PlayerAttackState::SHOT_GUN;


	//�U�����Ă��Ȃ�
	attackFlag = false;
	//�����ނɂ���Ă̍U��
	if (dynamic_cast<Player*>(mPlayer)->GetPlayerState() != PlayerState::PLAYERRESPAWN)
		PlayerAttack(attackState);

	//�U�����Ă��Ȃ����ɃI�o�[�q�[�g��
	if (!attackFlag)
	{
		coolHertCount += Time::DeltaTime;
		if (coolHertCount >= 2.0f)
			overHertCount += 50.0f*Time::DeltaTime;
		overHertCount = Math::Clamp(overHertCount, 0.0f, 100.0f);
	}
	else
		coolHertCount = 0.0f;

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
		//�^�[�Q�b�g�̈ʒu��30�ɕύX
		mCamera->SetTargetDistance(30.0f);
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		//�^�[�Q�b�g�̈ʒu��100�ɕύX
		mCamera->SetTargetDistance(100.0f);
		SniperGun();
		break;
	}
	case PlayerAttackState::SHOT_GUN:
	{
		//�^�[�Q�b�g�̈ʒu��10�ɕύX
		mCamera->SetTargetDistance(22.0f);
		ShotGun();
		break;
	}
	}
}

void PlayerAttackManager::MachineGun()
{
	if ((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad)))
	{
		//�U�����Ă��܂�
		attackFlag = true;
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (overHertCount < OverHertMachine) {
			overHertFlag = true;
			return;
		}
		//�I�[�o�[�q�[�g���Ă��Ȃ���
		overHertFlag = false;
		machineAttackCount += Time::DeltaTime;
		//0.1�b��1���˂���
		if (machineAttackCount >= 0.1f)
		{
			overHertCount -= OverHertMachine;
			BulletState machine;
			//���_�̈ʒu��ݒ�
			machine.vertexPoint = mCamera->GetTarget();
			//���̈ʒu���炢���甭��
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine));
			machineAttackCount = 0.0f;
		}
	}
}

void PlayerAttackManager::SniperGun()
{
	//�������ςȂ��Ń`���[�W
	if (((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))) &&
		!mSniperState.isColSniperLine)
	{
		//�U�����Ă��܂�
		attackFlag = true;
		//�v���C���[�͍U�����Ă��܂�
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (overHertCount < OverHertSniper) {
			overHertFlag = true;
			return;
		}
		//�����ɗ�����I�[�o�[�q�[�g���Ă��Ȃ�
		overHertFlag = false;
		//�X�i�C�p�[�`���[�W�ł̏������ݒ�
		if (initSniperFalg)
		{
			//�`���[�W�̏����ʂ�10
			mSniperState.chargeSniperCount = 10.0f;
			initSniperFalg = false;
		}
		//�`���[�W����u�Ԃɐ����ő�܂ň�u�����L�т�Ă��܂��h�~
		if (mSniperState.chargeSniperCount >= 12.0f)
			mSniperState.doCharge = true;
		//�`���[�W�ʂ𑝂₷
		mSniperState.chargeSniperCount += 50.0f*Time::DeltaTime;
		//�`���[�W�ʂ���萔�Ɏ��߂�
		mSniperState.chargeSniperCount
			= Math::Clamp(mSniperState.chargeSniperCount, 10.0f, 100.0f);

	}
	//�{�^���𗣂�����Line�ɂ����蔻���t����
	else if (mSniperState.doCharge)
	{
		//�I�[�o�[�q�[�g��������
		overHertCount -= OverHertSniper;
		//�����蔻��t���O
		mSniperState.isColSniperLine = true;
		//�`���[�W�͂������Ă��Ȃ�
		mSniperState.doCharge = false;
	}
	//������������0.1�b��ɂ����蔻�薳����
	if (mSniperState.isColSniperLine)
	{
		isColSniperCount += Time::DeltaTime;
		if (isColSniperCount >= 0.1f)
		{
			//�ŏ��̏�Ԃɖ߂�
			isColSniperCount = 0.0f;
			mSniperState.isColSniperLine = false;
			mSniperState.chargeSniperCount = 100.0f;
			initSniperFalg = true;
		}
	}

}

void PlayerAttackManager::ShotGun()
{
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))
	{
		//�U�����Ă��܂�
		attackFlag = true;
		//�v���C���[�͍U�����Ă��܂�
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		shotAttackCount += Time::DeltaTime;
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (overHertCount < OverHertShot) {
			overHertFlag = true;
			return;
		}
		if (shotAttackCount >= 2.0f)
		{
			for (int i = 0; i < 10; i++)
			{
				BulletState shot;
				//���_�̈ʒu��ݒ�
				shot.vertexPoint = mCamera->GetTarget();
				//���̈ʒu���炢���甭��
				shot.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
				shot.playerNumber = parameter.playNumber;
				world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR,
					std::make_shared<PlayerBullet>(world, shot, 2.5f));
				shotAttackCount = 0.0f;
			}
			overHertCount -= OverHertShot;
		}
	}
	else
	{
		shotAttackCount += Time::DeltaTime;
	}

}
