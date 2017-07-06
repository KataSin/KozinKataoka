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
//武器のオーバーヒート値
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
	//初期武器を設定
	mAttackState = PlayerAttackState::MACHINE_GUN;
	mAttacStateInt = (int)PlayerAttackState::MACHINE_GUN;
	//何プレイヤー設定
	parameter.playNumber = player.GetParameter().playNumber;
	//武器モデルを追加
	mGunPlayer = std::make_shared<PlayerGun>(world, player);
	world.Add(ACTOR_ID::GUN_ACTOR, mGunPlayer);
	//ターゲットを追加
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//オーバーヒートゲージを追加
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, mUiPos, *this));
	//武器UI追加
	world.UIAdd(UI_ID::GUN_UI, std::make_shared<GunUI>(world, mUiPos, *this));
	//オーバーヒートUI追加
	world.UIAdd(UI_ID::OVER_HERT_UI, std::make_shared<OverHertUI>(world, mOverHertUiPos, *this));
	//カメラも取得
	mCamera = static_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	//パッド設定
	mPad = world.GetPadNum()[(int)(parameter.playNumber - 1)];
	//カラーを設定
	mColor = mPlayer->mColor;
	//パーティクル設定
	ParticleSet();
	mAttackParticle = std::make_shared<ParticleEffectSystem>(world, mAttackParticleSet);
	world.Add(ACTOR_ID::PARTICLE_ACTOR, mAttackParticle);

	//スナイパー初期化
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
	//武器種類によっての攻撃
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN) {
		return;
	}
	//カラーを設定
	mColor = mPlayer->mColor;
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5, mPad) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J))
	{
		mAttacStateInt++;
		Sound::GetInstance().PlaySE(SE_ID::GUN_CHANGE_SE, DX_PLAYTYPE_BACK);
		mAttackState = (PlayerAttackState)(mAttacStateInt % 3);
	}

	//攻撃していない
	mAttackFlag = false;
	mOverHertFlag = false;
	PlayerAttack(mAttackState);

	//モデル表示するか
	static_cast<PlayerGun*>(mGunPlayer.get())->DrawGun(mAttackFlag);

	//攻撃していない時にオバーヒート回復
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
		//ターゲットの位置を30に変更
		mCamera->SetTargetDistance(50.0f);
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		//ターゲットの位置を100に変更
		mCamera->SetTargetDistance(200.0f);
		SniperGun();
		break;
	}
	case PlayerAttackState::SHOT_GUN:
	{
		//ターゲットの位置を30に変更
		mCamera->SetTargetDistance(40.0f);
		ShotGun();
		break;
	}
	}
}

void PlayerAttackManager::PlayerNumSet(PLAYER_NUMBER num)
{
	//プレイヤーの人数によって変更
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
	//二人以外は全部同じ
	else
	{
		//パッドのプレイヤー設定
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
		//攻撃しています
		mAttackFlag = true;
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (mOverHertCount < OverHertMachine) {
			mOverHertFlag = true;
			return;
		}
		//オーバーヒートしていないよ
		mOverHertFlag = false;
		mMachineAttackCount += Time::GetInstance().deltaTime();
		//0.1秒に1個発射する
		if (mMachineAttackCount >= 0.1f)
		{
			Sound::GetInstance().PlaySE(SE_ID::MACHINEATTACK_SE, DX_PLAYTYPE_BACK);
			AddParticle();
			mOverHertCount -= OverHertMachine;
			BulletState machine;
			//頂点の位置を設定
			machine.vertexPoint = mCamera->GetTarget();
			//腰の位置ぐらいから発射
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine, mColor));
			mMachineAttackCount = 0.0f;
		}
	}
}

void PlayerAttackManager::SniperGun()
{
	//押しっぱなしでチャージ
	if (((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, mPad))) &&
		!mSniperState.isColSniperLine)
	{
		//攻撃しています
		mAttackFlag = true;
		//プレイヤーは攻撃しています
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (mOverHertCount < OverHertSniper) {
			mOverHertFlag = true;
			return;
		}
		//ここに来たらオーバーヒートしていない
		mOverHertFlag = false;
		//スナイパーチャージでの初期化設定
		if (mInitSniperFalg)
		{
			//チャージの初期量は10
			mSniperState.chargeSniperCount = 10.0f;
			Sound::GetInstance().PlaySE(SE_ID::SNIPER_CHARGE_SE, DX_PLAYTYPE_BACK);
			mInitSniperFalg = false;
		}
		//チャージする瞬間に線が最大まで一瞬だけ伸びるてしまう防止
		if (mSniperState.chargeSniperCount >= 12.0f)
			mSniperState.doCharge = true;
		//チャージ量を増やす
		mSniperState.chargeSniperCount += 50.0f*Time::GetInstance().deltaTime();
		//チャージ量を一定数に収める
		mSniperState.chargeSniperCount
			= Math::Clamp(mSniperState.chargeSniperCount, 10.0f, 100.0f);

	}
	//ボタンを離したらLineにあたり判定を付ける
	else if (mSniperState.doCharge)
	{
		//パーティクルを出現させる
		AddParticle();
		//オーバーヒート数を引く
		mOverHertCount -= OverHertSniper;
		//あたり判定フラグ
		mSniperState.isColSniperLine = true;
		//チャージはもうしていない
		mSniperState.doCharge = false;
		Sound::GetInstance().StopSE(SE_ID::SNIPER_CHARGE_SE);
		Sound::GetInstance().PlaySE(SE_ID::SNIPER_ATTACK_SE, DX_PLAYTYPE_BACK);
	}
	//離した時から0.1秒後にあたり判定無効化
	if (mSniperState.isColSniperLine)
	{
		mIsColSniperCount += Time::GetInstance().deltaTime();
		if (mIsColSniperCount >= 0.2f)
		{
			//最初の状態に戻す
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
		//攻撃しています
		mAttackFlag = true;
		//プレイヤーは攻撃しています
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (mOverHertCount < OverHertShot) {
			mOverHertFlag = true;
			return;
		}
		mOverHertFlag = false;
		if (mShotAttackCount >= 1.0f)
		{
			for (int i = 0; i < 15; i++)
			{
				//パーティクル出現
				AddParticle();
				BulletState shot;
				//頂点の位置を設定
				shot.vertexPoint = mCamera->GetTarget();
				//腰の位置ぐらいから発射
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
	//アタック中パーティクル設定
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
