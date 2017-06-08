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
	shotAttackCount(3.0f),
	initSniperFalg(true),
	overHertFlag(false)
{


	mPlayer = dynamic_cast<Player*>(&player);

	PlayerNumSet(mPlayer->GetParameter().playNumber);
	parameter.isDead = false;
	//初期武器を設定
	attackState = PlayerAttackState::MACHINE_GUN;
	attacStateInt = (int)PlayerAttackState::MACHINE_GUN;
	//何プレイヤー設定
	parameter.playNumber = player.GetParameter().playNumber;
	//ターゲットを追加
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//オーバーヒートゲージを追加
	world.UIAdd(UI_ID::GAUGE_UI, std::make_shared<AttackGauge>(world, uiPos, *this));
	//武器UI追加
	world.UIAdd(UI_ID::GUN_UI, std::make_shared<GunUI>(world, uiPos, *this));
	//オーバーヒートUI追加
	world.UIAdd(UI_ID::OVER_HERT_UI, std::make_shared<OverHertUI>(world, mOverHertUiPos, *this));
	//カメラも取得
	mCamera = dynamic_cast<CameraActor*>(world.GetCamera(mPlayer->GetParameter().playNumber).get());
	//パッド設定
	pad = world.GetPadNum()[(int)(parameter.playNumber - 1)];
	//カラーを設定
	mColor = mPlayer->mColor;
	//パーティクル設定
	ParticleSet();
	mAttackParticle = std::make_shared<ParticleEffectSystem>(world, mAttackParticleSet);
	world.Add(ACTOR_ID::PARTICLE_ACTOR, mAttackParticle);
	////誰の弾かの情報を設定
	//bulletState.playerNumber = mPlayer->GetParameter().playNumber;
}

PlayerAttackManager::~PlayerAttackManager()
{

}

void PlayerAttackManager::Update()
{
	//武器種類によっての攻撃
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN) {
		return;
	}
	//カラーを設定
	mColor = mPlayer->mColor;
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5, pad) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::J))
	{
		attacStateInt++;
		attackState = (PlayerAttackState)(attacStateInt % 3);
	}

	//攻撃していない
	attackFlag = false;
	overHertFlag = false;
	PlayerAttack(attackState);

	//攻撃していない時にオバーヒート回復
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
		//ターゲットの位置を30に変更
		mCamera->SetTargetDistance(45.0f);
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
		mCamera->SetTargetDistance(30.0f);
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
	//二人以外は全部同じ
	else
	{
		//パッドのプレイヤー設定
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
		machineAttackCount += Time::GetInstance().deltaTime();
		//0.1秒に1個発射する
		if (machineAttackCount >= 0.1f)
		{
			AddParticle();
			overHertCount -= OverHertMachine;
			BulletState machine;
			//頂点の位置を設定
			machine.vertexPoint = mCamera->GetTarget();
			//腰の位置ぐらいから発射
			machine.position = dynamic_cast<Player*>(mPlayer)->GetPlayerGunPos();
			machine.playerNumber = parameter.playNumber;
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, machine, mColor));
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
		overHertCount -= OverHertSniper;
		//あたり判定フラグ
		mSniperState.isColSniperLine = true;
		//チャージはもうしていない
		mSniperState.doCharge = false;
	}
	//離した時から0.1秒後にあたり判定無効化
	if (mSniperState.isColSniperLine)
	{
		isColSniperCount += Time::GetInstance().deltaTime();
		if (isColSniperCount >= 0.2f)
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
	shotAttackCount += Time::GetInstance().deltaTime();
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad))
	{
		//攻撃しています
		attackFlag = true;
		//プレイヤーは攻撃しています
		mPlayer->SetPlayerState(PlayerState::PLAYERATTACK);
		//オーバーヒートで弾が出せないよ
		if (overHertCount < OverHertShot) {
			overHertFlag = true;
			return;
		}
		overHertFlag = false;
		if (shotAttackCount >= 2.0f)
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
				shotAttackCount = 0.0f;
				if (i == 1)
					overHertCount -= 30.0f;
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
