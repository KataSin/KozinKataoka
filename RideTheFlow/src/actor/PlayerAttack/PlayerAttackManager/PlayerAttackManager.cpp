#include "PlayerAttackManager.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"

#include "../../PlayerBullet/TargetRay.h"
#include "../../../UIactor/AttackGauge/AttackGauge.h"

//武器のオーバーヒート値
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
	//初期武器を設定
	attackState = PlayerAttackState::SHOT_GUN;
	//何プレイヤー設定
	parameter.playNumber = player.GetParameter().playNumber;
	//ターゲットを追加
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//オーバーヒートゲージを追加
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, this));

	//カメラも取得
	mCamera = dynamic_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	////誰の弾かの情報を設定
	//bulletState.playerNumber = mPlayer->GetParameter().playNumber;
	//パッドのプレイヤー設定
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


	//攻撃していない
	attackFlag = false;
	//武器種類によっての攻撃
	if (dynamic_cast<Player*>(mPlayer)->GetPlayerState() != PlayerState::PLAYERRESPAWN)
		PlayerAttack(attackState);

	//攻撃していない時にオバーヒート回復
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
		//ターゲットの位置を30に変更
		mCamera->SetTargetDistance(30.0f);
		MachineGun();
		break;
	}
	case PlayerAttackState::SNIPER_GUN:
	{
		//ターゲットの位置を100に変更
		mCamera->SetTargetDistance(100.0f);
		SniperGun();
		break;
	}
	case PlayerAttackState::SHOT_GUN:
	{
		//ターゲットの位置を10に変更
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
		//攻撃しています
		attackFlag = true;
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (overHertCount < OverHertMachine) {
			overHertFlag = true;
			return;
		}
		//オーバーヒートしていないよ
		overHertFlag = false;
		machineAttackCount += Time::DeltaTime;
		//0.1秒に1個発射する
		if (machineAttackCount >= 0.1f)
		{
			overHertCount -= OverHertMachine;
			BulletState machine;
			//頂点の位置を設定
			machine.vertexPoint = mCamera->GetTarget();
			//腰の位置ぐらいから発射
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine));
			machineAttackCount = 0.0f;
		}
	}
}

void PlayerAttackManager::SniperGun()
{
	//押しっぱなしでチャージ
	if (((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))) &&
		!mSniperState.isColSniperLine)
	{
		//攻撃しています
		attackFlag = true;
		//プレイヤーは攻撃しています
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (overHertCount < OverHertSniper) {
			overHertFlag = true;
			return;
		}
		//ここに来たらオーバーヒートしていない
		overHertFlag = false;
		//スナイパーチャージでの初期化設定
		if (initSniperFalg)
		{
			//チャージの初期量は10
			mSniperState.chargeSniperCount = 10.0f;
			initSniperFalg = false;
		}
		//チャージする瞬間に線が最大まで一瞬だけ伸びるてしまう防止
		if (mSniperState.chargeSniperCount >= 12.0f)
			mSniperState.doCharge = true;
		//チャージ量を増やす
		mSniperState.chargeSniperCount += 50.0f*Time::DeltaTime;
		//チャージ量を一定数に収める
		mSniperState.chargeSniperCount
			= Math::Clamp(mSniperState.chargeSniperCount, 10.0f, 100.0f);

	}
	//ボタンを離したらLineにあたり判定を付ける
	else if (mSniperState.doCharge)
	{
		//オーバーヒート数を引く
		overHertCount -= OverHertSniper;
		//あたり判定フラグ
		mSniperState.isColSniperLine = true;
		//チャージはもうしていない
		mSniperState.doCharge = false;
	}
	//離した時から0.1秒後にあたり判定無効化
	if (mSniperState.isColSniperLine)
	{
		isColSniperCount += Time::DeltaTime;
		if (isColSniperCount >= 0.1f)
		{
			//最初の状態に戻す
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
		//攻撃しています
		attackFlag = true;
		//プレイヤーは攻撃しています
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		shotAttackCount += Time::DeltaTime;
		//オーバーヒートで弾が出せないよ
		if (overHertCount < OverHertShot) {
			overHertFlag = true;
			return;
		}
		if (shotAttackCount >= 2.0f)
		{
			for (int i = 0; i < 10; i++)
			{
				BulletState shot;
				//頂点の位置を設定
				shot.vertexPoint = mCamera->GetTarget();
				//腰の位置ぐらいから発射
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
