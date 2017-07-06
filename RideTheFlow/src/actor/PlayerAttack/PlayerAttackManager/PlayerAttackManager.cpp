#include "PlayerAttackManager.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"
#include "../../../sound/Sound.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

#include "../PlayerGun/PlayerGun.h"
#include "../../PlayerBullet/TargetRay.h"
#include "../../../UIactor/AttackGauge/AttackGauge.h"
#include "../../../UIactor/GunUI/GunUI.h"
#include "../../../UIactor/OverHertUI/OverHertUI.h"
#include "../../PlayerBullet/PlayerBullet.h"

#include "../PlayerGun/PlayerGun.h"
//����̃I�[�o�[�q�[�g�l
const float OverHertMachine = 3.0f;
const float OverHertSniper = 30.0f;
const float OverHertShot = 15.0f;

PlayerAttackManager::PlayerAttackManager(IWorld& world, Actor& player) :
	Actor(world),
	mOverHertCount(100.0f),
	mMachineAttackCount(0.1f),
	mIsColSniperCount(0.0f),
	mCoolHertCount(0.0f),
	mAttackFlag(0.0f),
	mShotAttackCount(3.0f),
	mInitSniperFalg(true),
	mOverHertFlag(false)
{


	mPlayer = dynamic_cast<Player*>(&player);

	PlayerNumSet(mPlayer->GetParameter().playNumber);
	parameter.isDead = false;
	//���������ݒ�
	mAttackState = PlayerAttackState::MACHINE_GUN;
	mAttacStateInt = (int)PlayerAttackState::MACHINE_GUN;
	//���v���C���[�ݒ�
	parameter.playNumber = player.GetParameter().playNumber;
	//���탂�f����ǉ�
	mGunPlayer = std::make_shared<PlayerGun>(world, player);
	world.Add(ACTOR_ID::GUN_ACTOR, mGunPlayer);
	//�^�[�Q�b�g��ǉ�
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//�I�[�o�[�q�[�g�Q�[�W��ǉ�
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, mUiPos, *this));
	//����UI�ǉ�
	world.UIAdd(UI_ID::GUN_UI, std::make_shared<GunUI>(world, mUiPos, *this));
	//�I�[�o�[�q�[�gUI�ǉ�
	world.UIAdd(UI_ID::OVER_HERT_UI, std::make_shared<OverHertUI>(world, mOverHertUiPos, *this));
	//�J�������擾
	mCamera = static_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	//�p�b�h�ݒ�
	mPad = world.GetPadNum()[(int)(parameter.playNumber - 1)];
	//�J���[��ݒ�
	mColor = mPlayer->mColor;
	//�p�[�e�B�N���ݒ�
	ParticleSet();
	mAttackParticle = std::make_shared<ParticleEffectSystem>(world, mAttackParticleSet);
	world.Add(ACTOR_ID::PARTICLE_ACTOR, mAttackParticle);

	//�X�i�C�p�[������
	mIsColSniperCount = 0.0f;
	mSniperState.isColSniperLine = false;
	mSniperState.chargeSniperCount = 100.0f;
	mInitSniperFalg = true;
}

PlayerAttackManager::~PlayerAttackManager()
{

}

void PlayerAttackManager::Update()
{
	if (!world.GetInputPlayer())return;
	//�����ނɂ���Ă̍U��
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN) {
		return;
	}
	//�J���[��ݒ�
	mColor = mPlayer->mColor;
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5, mPad) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J))
	{
		mAttacStateInt++;
		Sound::GetInstance().PlaySE(SE_ID::GUN_CHANGE_SE, DX_PLAYTYPE_BACK);
		mAttackState = (PlayerAttackState)(mAttacStateInt % 3);
	}

	//�U�����Ă��Ȃ�
	mAttackFlag = false;
	mOverHertFlag = false;
	PlayerAttack(mAttackState);

	//���f���\�����邩
	static_cast<PlayerGun*>(mGunPlayer.get())->DrawGun(mAttackFlag);

	//�U�����Ă��Ȃ����ɃI�o�[�q�[�g��
	if (!mAttackFlag)
	{
		mCoolHertCount += Time::GetInstance().deltaTime();
		if (mCoolHertCount >= 1.0f)
			mOverHertCount += 80.0f*Time::GetInstance().deltaTime();
		mOverHertCount = Math::Clamp(mOverHertCount, 0.0f, 100.0f);
	}
	else
		mCoolHertCount = 0.0f;

}

void PlayerAttackManager::Draw() const
{
}

void PlayerAttackManager::OnCollide(Actor & other, CollisionParameter colpara)
{
}

PlayerAttackState PlayerAttackManager::GetState()
{
	return mAttackState;
}

SniperState PlayerAttackManager::GetChargeCount()
{
	return mSniperState;
}

float PlayerAttackManager::GetOverHertCount()
{
	return mOverHertCount;
}

bool PlayerAttackManager::GetOverHertFlag()
{
	return mOverHertFlag;
}

bool PlayerAttackManager::GetIsAttack()
{
	return mAttackFlag;
}

void PlayerAttackManager::PlayerAttack(PlayerAttackState state)
{
	switch (state)
	{
	case PlayerAttackState::MACHINE_GUN:
	{
		//�^�[�Q�b�g�̈ʒu��30�ɕύX
		mCamera->SetTargetDistance(50.0f);
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		//�^�[�Q�b�g�̈ʒu��100�ɕύX
		mCamera->SetTargetDistance(200.0f);
		SniperGun();
		break;
	}
	case PlayerAttackState::SHOT_GUN:
	{
		//�^�[�Q�b�g�̈ʒu��30�ɕύX
		mCamera->SetTargetDistance(40.0f);
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
			mUiPos = Vector2(10, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 - 80);
			break;
		}
		case PLAYER_2: {
			mUiPos = Vector2(10, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 4 - 80);
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
			mUiPos = Vector2(10, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 - 80);
			break;
		}
		case PLAYER_2: {
			mUiPos = Vector2(WINDOW_WIDTH - 55, WINDOW_HEIGHT / 2 - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT / 4 - 80);
			break;
		}
		case PLAYER_3: {
			mUiPos = Vector2(10, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT * 3 / 4 - 80);
			break;
		}
		case PLAYER_4: {
			mUiPos = Vector2(WINDOW_WIDTH - 55, WINDOW_HEIGHT - 125);
			mOverHertUiPos = Vector2(WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 3 / 4 - 80);
			break;
		}
		}
	}
}

void PlayerAttackManager::MachineGun()
{

	if ((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, mPad)))
	{
		//�U�����Ă��܂�
		mAttackFlag = true;
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (mOverHertCount < OverHertMachine) {
			mOverHertFlag = true;
			return;
		}
		//�I�[�o�[�q�[�g���Ă��Ȃ���
		mOverHertFlag = false;
		mMachineAttackCount += Time::GetInstance().deltaTime();
		//0.1�b��1���˂���
		if (mMachineAttackCount >= 0.1f)
		{
			Sound::GetInstance().PlaySE(SE_ID::MACHINEATTACK_SE, DX_PLAYTYPE_BACK);
			AddParticle();
			mOverHertCount -= OverHertMachine;
			BulletState machine;
			//���_�̈ʒu��ݒ�
			machine.vertexPoint = mCamera->GetTarget();
			//���̈ʒu���炢���甭��
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine, mColor));
			mMachineAttackCount = 0.0f;
		}
	}
}

void PlayerAttackManager::SniperGun()
{
	//�������ςȂ��Ń`���[�W
	if (((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, mPad))) &&
		!mSniperState.isColSniperLine)
	{
		//�U�����Ă��܂�
		mAttackFlag = true;
		//�v���C���[�͍U�����Ă��܂�
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (mOverHertCount < OverHertSniper) {
			mOverHertFlag = true;
			return;
		}
		//�����ɗ�����I�[�o�[�q�[�g���Ă��Ȃ�
		mOverHertFlag = false;
		//�X�i�C�p�[�`���[�W�ł̏������ݒ�
		if (mInitSniperFalg)
		{
			//�`���[�W�̏����ʂ�10
			mSniperState.chargeSniperCount = 10.0f;
			Sound::GetInstance().PlaySE(SE_ID::SNIPER_CHARGE_SE, DX_PLAYTYPE_BACK);
			mInitSniperFalg = false;
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
		mOverHertCount -= OverHertSniper;
		//�����蔻��t���O
		mSniperState.isColSniperLine = true;
		//�`���[�W�͂������Ă��Ȃ�
		mSniperState.doCharge = false;
		Sound::GetInstance().StopSE(SE_ID::SNIPER_CHARGE_SE);
		Sound::GetInstance().PlaySE(SE_ID::SNIPER_ATTACK_SE, DX_PLAYTYPE_BACK);
	}
	//������������0.1�b��ɂ����蔻�薳����
	if (mSniperState.isColSniperLine)
	{
		mIsColSniperCount += Time::GetInstance().deltaTime();
		if (mIsColSniperCount >= 0.2f)
		{
			//�ŏ��̏�Ԃɖ߂�
			mIsColSniperCount = 0.0f;
			mSniperState.isColSniperLine = false;
			mSniperState.chargeSniperCount = 100.0f;
			mInitSniperFalg = true;

		}
	}

}

void PlayerAttackManager::ShotGun()
{
	mShotAttackCount += Time::GetInstance().deltaTime();
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, mPad))
	{
		//�U�����Ă��܂�
		mAttackFlag = true;
		//�v���C���[�͍U�����Ă��܂�
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//�I�[�o�[�q�[�g�Œe���o���Ȃ���
		if (mOverHertCount < OverHertShot) {
			mOverHertFlag = true;
			return;
		}
		mOverHertFlag = false;
		if (mShotAttackCount >= 1.0f)
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
				mShotAttackCount = 0.0f;
				if (i == 1) {
					Sound::GetInstance().PlaySE(SE_ID::SHOT_ATTACK_SE, DX_PLAYTYPE_BACK);
					mOverHertCount -= 30.0f;
				}
					
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

	mAttackParticleSet.position = mPlayer->GetPlayerGunPos();
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
	mAttackParticleSet.position = mPlayer->GetPlayerGunPos();
	mAttackParticleSet.isParticle = true;
	static_cast<ParticleEffectSystem*>(mAttackParticle.get())->SetParticle(mAttackParticleSet);

}
