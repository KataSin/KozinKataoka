#include "PlayerAttackManager.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

#include "../../PlayerBullet/TargetRay.h"
#include "../../../UIactor/AttackGauge/AttackGauge.h"
#include "../../../UIactor/GunUI/GunUI.h"
#include "../../../UIactor/OverHertUI/OverHertUI.h"

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
	shotAttackCount(3.0f),
	initSniperFalg(true),
	overHertFlag(false)
{


	mPlayer = dynamic_cast<Player*>(&player);

	PlayerNumSet(mPlayer->GetParameter().playNumber);
	parameter.isDead = false;
	//���������ݒ�
	attackState = PlayerAttackState::MACHINE_GUN;
	attacStateInt = (int)PlayerAttackState::MACHINE_GUN;
	//���v���C���[�ݒ�
	parameter.playNumber = player.GetParameter().playNumber;
	//�^�[�Q�b�g��ǉ�
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//�I�[�o�[�q�[�g�Q�[�W��ǉ�
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, uiPos, *this));
	//����UI�ǉ�
	world.UIAdd(UI_ID::GUN_UI, std::make_shared<GunUI>(world, uiPos, *this));
	//�I�[�o�[�q�[�gUI�ǉ�
	world.UIAdd(UI_ID::OVER_HERT_UI, std::make_shared<OverHertUI>(world, mOverHertUiPos, *this));
	//�J�������擾
	mCamera = dynamic_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	//�p�b�h�ݒ�
	pad = world.GetPadNum()[(int)(parameter.playNumber - 1)];
	//�J���[��ݒ�
	mColor = mPlayer->mColor;
	//�p�[�e�B�N���ݒ�
	ParticleSet();
	mAttackParticle = std::make_shared<ParticleEffectSystem>(world, mAttackParticleSet);
	world.Add(ACTOR_ID::PARTICLE_ACTOR, mAttackParticle);
	////�N�̒e���̏���ݒ�
	//bulletState.playerNumber = mPlayer->GetParameter().playNumber;
}

PlayerAttackManager::~PlayerAttackManager()
{

}

void PlayerAttackManager::Update()
{
	//�����ނɂ���Ă̍U��
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN) {
		return;
	}
	//�J���[��ݒ�
	mColor = mPlayer->mColor;
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5, pad) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J))
	{
		attacStateInt++;
		attackState = (PlayerAttackState)(attacStateInt % 3);
	}

	//�U�����Ă��Ȃ�
	attackFlag = false;
	overHertFlag = false;
	PlayerAttack(attackState);

	//�U�����Ă��Ȃ����ɃI�o�[�q�[�g��
	if (!attackFlag)
	{
		coolHertCount += Time::GetInstance().deltaTime();
		if (coolHertCount >= 2.0f)
			overHertCount += 80.0f*Time::GetInstance().deltaTime();
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
		mCamera->SetTargetDistance(45.0f);
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
		mCamera->SetTargetDistance(30.0f);
		ShotGun();
		break;
	}
	}
}

void PlayerAttackManager::PlayerNumSet(PLAYER_NUMBER num)
{
	//�v���C���[�̐l���ɂ���ĕύX
	if (world.GetPlayerNum() == 2) {
		switch (num)
		{
		case PLAYER_NULL:
			break;
		case PLAYER_1: {
			uiPos = Vector2(10, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 112);
			break;
		}
		case PLAYER_2: {
			uiPos = Vector2(10, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 4 + 112);
			break;
		}
		}
	}
	//��l�ȊO�͑S������
	else
	{
		//�p�b�h�̃v���C���[�ݒ�
		switch (num)
		{
		case PLAYER_NULL:
			break;
		case PLAYER_1: {
			uiPos = Vector2(10, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 112);
			break;
		}
		case PLAYER_2: {
			uiPos = Vector2(WINDOW_WIDTH - 55, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT / 4 + 112);
			break;
		}
		case PLAYER_3: {
			uiPos = Vector2(10, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT * 3 / 4 + 112);
			break;
		}
		case PLAYER_4: {
			uiPos = Vector2(WINDOW_WIDTH - 55, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 3 / 4 + 112);
			break;
		}
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
		machineAttackCount += Time::GetInstance().deltaTime();
		//0.1�b��1���˂���
		if (machineAttackCount >= 0.1f)
		{
			AddParticle();
			overHertCount -= OverHertMachine;
			BulletState machine;
			//���_�̈ʒu��ݒ�
			machine.vertexPoint = mCamera->GetTarget();
			//���̈ʒu���炢���甭��
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine, mColor));
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
		mSniperState.chargeSniperCount += 50.0f*Time::GetInstance().deltaTime();
		//�`���[�W�ʂ���萔�Ɏ��߂�
		mSniperState.chargeSniperCount
			= Math::Clamp(mSniperState.chargeSniperCount, 10.0f, 100.0f);

	}
	//�{�^���𗣂�����Line�ɂ����蔻���t����
	else if (mSniperState.doCharge)
	{
		//�p�[�e�B�N�����o��������
		AddParticle();
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
		isColSniperCount += Time::GetInstance().deltaTime();
		if (isColSniperCount >= 0.2f)
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
	shotAttackCount += Time::GetInstance().deltaTime();
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))
	{
		//�U�����Ă��܂�
		attackFlag = true;
		//�v���C���[�͍U�����Ă��܂�
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (overHertCount < OverHertShot) {
			overHertFlag = true;
			return;
		}
		overHertFlag = false;
		if (shotAttackCount >= 2.0f)
		{
			for (int i = 0; i < 15; i++)
			{
				//�p�[�e�B�N���o��
				AddParticle();
				BulletState shot;
				//���_�̈ʒu��ݒ�
				shot.vertexPoint = mCamera->GetTarget();
				//���̈ʒu���炢���甭��
				shot.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
				shot.playerNumber = parameter.playNumber;
				world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR,
					std::make_shared<PlayerBullet>(world, shot, mColor, 2.5f));
				shotAttackCount = 0.0f;
				if (i == 1)
					overHertCount -= 30.0f;
			}
		}
	}
}

void PlayerAttackManager::ParticleSet()
{
	//�A�^�b�N���p�[�e�B�N���ݒ�
	mAttackParticleSet.isOneParticle = true;
	mAttackParticleSet.isParticle = false;
	mAttackParticleSet.isParticleNum = 5;
	mAttackParticleSet.IsDeadTime = 0.3f;

	mAttackParticleSet.position = mPlayer->GetPlayerGunPos() - (mPlayer->GetParameter().mat.GetFront()*5.0f);
	mAttackParticleSet.scale = 0.4f;
	mAttackParticleSet.scaleRandom = 0.1f;
	mAttackParticleSet.Vec = Vector3::Up;
	mAttackParticleSet.VecRandom = Vector3(2, 0, 2);
	mAttackParticleSet.InitializeVelocity = Vector3(3, 5, 3);
	mAttackParticleSet.Deceleration = 5.0f;
	mAttackParticleSet.DecelerationTime = 0.2f;
	mAttackParticleSet.MinusAlphaNum = 3.0f;
	mAttackParticleSet.MinusAlphaTime = 0.1f;
	std::vector<SPRITE_ID> ids;
	ids.push_back(SPRITE_ID::KEMURI_1_SPRITE);
	ids.push_back(SPRITE_ID::KEMURI_2_SPRITE);
	ids.push_back(SPRITE_ID::KEMURI_3_SPRITE);
	mAttackParticleSet.texture = ids;
	mAttackParticleSet.color = mColor;
}
void PlayerAttackManager::AddParticle()
{
	mAttackParticleSet.position = (mPlayer->GetPlayerGunPos() - (mPlayer->GetParameter().mat.GetFront()*3.0f)) + Vector3(0, 2, 0);
	mAttackParticleSet.isParticle = true;
	static_cast<ParticleEffectSystem*>(mAttackParticle.get())->SetParticle(mAttackParticleSet);

}
