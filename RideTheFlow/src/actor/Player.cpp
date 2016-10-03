﻿#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../time/Time.h"
#include "../graphic/Anime.h"
#include "../math/Math.h"
#include "../camera/Camera.h"
#include "../math/Quaternion.h"
#include "../game/Random.h"
#include "../input/GamePad.h"
#include "../sound/Sound.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "CameraActor.h"
#include "../actor/PlayerBullet/PlayerBullet.h"
#include "DeadBullet\DeadBulletManager.h"
#include "PlayerBullet\TargetRay.h"

const float PlayerSpeed = 20.0f;
const float LowPlayerSpeed = 5.0f;
const float AttackPlayerSpeed = 5.0f;

Player::Player(IWorld& world, Vector3 position_, float rotateY, PLAYER_NUMBER player) :
	Actor(world),
	cameraMat(Matrix4::Identity),
	playerModelMat(Matrix4::Identity),
	cameraPos(Vector3::Zero),
	coppyPos(Vector3::Zero),
	vecPos(Vector3::Zero),
	mVelocity(Vector3::Zero),
	respawnCount(0.0f),
	chargeCount(0.0f),
	angleY(rotateY),
	attackCoolCount(0.0f),
	jumpCount(0.0f),
	bulletAttackNum(0.0f),
	respawnFlag(false),
	jumpFlag(false),
	mPosition(position_)
{
	parameter.HP = 10;
	parameter.playNumber = player;
	parameter.isDead = false;
	parameter.radius = 2.0f;
	parameter.height = 5.0f;
	parameter.isRespawn = false;
	parameter.mat =
		Matrix4::Scale(0)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(angleY)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);

	//カメラを追加
	world.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(world, *this));
	//ターゲットを追加
	world.Add(ACTOR_ID::PLAYER_TARGET_ACTOR, std::make_shared<TargetRay>(world, *this));
	//カメラの向いている方向にプレイヤーも向く
	float angleY = world.GetCamera(parameter.playNumber)->GetParameter().mat.GetRotateDegree().y;
	mRotate = Vector3(0.0f, angleY - 90.0f, 0.0f);
	//攻撃形態をマシンガンで初期化
	attackState = PlayerAttackState::MACHINE_GUN;

	//弾情報初期化
	bulletState.vertexPoint = Vector3::Zero;
	bulletState.playerNumber = player;
	bulletState.position = Vector3::Zero;

	//カメラ
	cameraActor = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());

	//プレイヤーのスピード設定
	playerSpeed = PlayerSpeed;
	//リスポーン地点設定
	respawnPoint = position_;
	//パッドのプレイヤー設定
	switch (player)
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


	test = Vector3::Zero;
}
Player::~Player() {

}

void Player::Update() {

	//状態の初期化
	playerState = PlayerState::PLAYERSTOP;

	//ポジションをセーブ
	coppyPos = mPosition;

	//自分のカメラを取得
	cameraMat = cameraActor->GetParameter().mat;
	cameraPos = cameraMat.GetPosition();

	//重力処理
	if (gravityFlag)
		mVelocity.y -= 30.0f*Time::DeltaTime;
	else if (playerState != PlayerState::PLAYERJUMP)
		mVelocity.y = 0.0f;
	mPosition += mVelocity*Time::DeltaTime;

	//hpがゼロになったらリスポーン
	if (parameter.HP <= 0)
	{
		Respawn();
	}

	//リスポーン中以外は行動可能
	if (playerState != PlayerState::PLAYERRESPAWN)
	{
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::H))
			attackState = PlayerAttackState::SNIPER_GUN;
		//歩き
		Move();
		//攻撃
		PlayerAttacUpdate(attackState);
		//ジャンプ
		Jump();
	}

	//敵のプレートに当たってたらスピードダウン
	if (lowStateFlag)
	{
		if (playerState == PlayerState::PLAYERATTACK)
			playerSpeed = LowPlayerSpeed / 3.0f;
		else
			playerSpeed = LowPlayerSpeed;
	}
	else if (!lowStateFlag)
	{
		if (playerState == PlayerState::PLAYERATTACK)
			playerSpeed = PlayerSpeed / 3.0f;
		else
		{
			playerSpeed = PlayerSpeed;
		}
	}
	//マトリクス計算
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(angleY - 90)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);

	//フラグの初期化
	gravityFlag = true;
	lowStateFlag = false;
}
void Player::Draw() const {
	if (playerState != PlayerState::PLAYERRESPAWN)
	{
		Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat);
	}
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition()), parameter.radius, 10, 1, 1, FALSE);
	//DrawLine3D(Vector3::ToVECTOR(mPosition), Vector3::ToVECTOR(mPosition + vecPos), GetColor(255, 255, 255));
}

void Player::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_PLAYER_COL&&!jumpFlag)
	{
		//自分の色のプレートじゃなかったら
		if (other.GetParameter().playNumber != parameter.playNumber &&
			other.GetParameter().playNumber != PLAYER_NUMBER::PLAYER_NULL)
			lowStateFlag = true;
		gravityFlag = false;
	}

	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL&&
		other.GetParameter().id == ACTOR_ID::PLAYER_BULLET_ACTOR)
	{
		parameter.HP--;
		//誰の弾を受けたか保存
		damagePlayerNumber = other.GetParameter().playNumber;
	}
	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL&&
		other.GetParameter().id == ACTOR_ID::DEAD_BULLET_ACTOR)
	{
		//死んだ残骸に当たったら即死亡
		parameter.HP = 0;
		//誰の弾を受けたか保存
		damagePlayerNumber = other.GetParameter().playNumber;
	}
	if (colpara.colID == COL_ID::PLAYER_TREE_COL)
	{
		//めり込み防止
		mPosition = colpara.colPos;
	}
}

void Player::PlayerAttacUpdate(PlayerAttackState state)
{
	switch (state)
	{
	case MACHINE_GUN:
		MachineAttack();
		break;
	case SNIPER_GUN:
		SniperAttack();
		break;
	}
}

void Player::RotateMovePlayer()
{
	//プレイヤーの移動ベクトルを取得
	vecPos = mPosition - coppyPos;
	//正規化＆ベクトルのy軸無視
	vecPos = (vecPos*Vector3(1, 0, 1)).Normalized();

	//プレイヤーの向き取得
	Vector3 playerFront = vecPos;
	Vector3 playerLeft = Vector3::Cross(Vector3::Up, vecPos).Normalized();
	Vector3 playerUp = Vector3::Cross(playerFront, playerLeft).Normalized();

	//移動量がゼロだったら直前の角度を保持
	if (vecPos.x != 0)
		angleY = -Math::Atan2(vecPos.z, vecPos.x)*180.0f / 3.1415f;
}

void Player::Move()
{
	/************************************************************************/
	//移動の仕様はsplatoonと同じ（カメラから見た移動＆球を撃っているときは蟹移動）
	//ゲームパッド対応にすよ
	/************************************************************************/


	//カメラの方向を計算
	Vector3 cameraFront = (parameter.mat.GetPosition() - cameraPos).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3::Up).Normalized();
	Vector3 cameraUp = Vector3::Cross(cameraFront, cameraLeft).Normalized();

	Vector2 vec;
	vec = GamePad::GetInstance().Stick(pad)*playerSpeed;

	mPosition -= vec.y*Vector3(cameraFront*Vector3(1, 0, 1))*Time::DeltaTime;
	mPosition -= vec.x*Vector3(cameraLeft*Vector3(1, 0, 1))*Time::DeltaTime;

	if (parameter.playNumber == PLAYER_NUMBER::PLAYER_1)
	{
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		{
			mPosition += playerSpeed*cameraFront*Vector3(1, 0, 1)*Time::DeltaTime;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		{
			mPosition += playerSpeed*-cameraFront*Vector3(1, 0, 1)*Time::DeltaTime;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		{
			mPosition += playerSpeed*cameraLeft*Vector3(1, 0, 1)*Time::DeltaTime;
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		{
			mPosition += playerSpeed*-cameraLeft*Vector3(1, 0, 1)*Time::DeltaTime;
		}
	}

	//移動先に回転※移動した最後に実行すること
	RotateMovePlayer();
	cameraActor->SetCameraState(CameraState::DEFAULT);
	playerState = PlayerState::PLAYERWALK;
}

void Player::AttackMove()
{

}

void Player::MachineAttack()
{
	if ((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad)) &&
		bulletAttackNum < 100.0f)
	{
		attackCoolCount += Time::DeltaTime;
		angleY = cameraActor->GetParameter().mat.GetRotateDegree().y - 90.0f;
		if (attackCoolCount >= 0.1f)
		{
			//bulletAttackNum += 2.0f;
			//頂点の位置を設定
			bulletState.vertexPoint = cameraActor->GetTarget();
			//腰の位置ぐらいから発射
			bulletState.position = parameter.mat.GetPosition() + Vector3(0.0f, 2.0f, 0.0f);
			world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR, std::make_shared<PlayerBullet>(world, bulletState));
			attackCoolCount = 0.0f;
		}
		playerState = PlayerState::PLAYERATTACK;

	}
	else
	{
		attackCoolCount = 0.1f;
	}

	bulletAttackNum = Math::Clamp(bulletAttackNum, 0.0f, 100.0f);
}

void Player::SniperAttack()
{
	if ((Keyboard::GetInstance().KeyStateDown(KEYCODE::G) ||
		GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, pad)))
	{
		//cameraActor->SetCameraState(CameraState::ATTACKCHARGE);
		angleY = cameraActor->GetParameter().mat.GetRotateDegree().y - 90.0f;
		chargeCount += 5.0f*Time::DeltaTime;

	}
	else if (chargeCount > 0.0f)
	{
		chargeCount = 0.0f;
	}
	chargeCount = Math::Clamp(chargeCount, 0.0f, 100.0f);
}

void Player::Jump()
{
	//ジャンプした瞬間何秒間は地面のあたり判定無効
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3, pad) &&
		!gravityFlag)
	{
		mVelocity.y = 15.0f;
		jumpFlag = true;
		playerState = PlayerState::PLAYERJUMP;
	}
	if (jumpFlag)
	{
		jumpCount += Time::DeltaTime;
		if (jumpCount >= 0.2f)
		{
			jumpFlag = false;
			jumpCount = 0.0f;
		}
	}
}

void Player::Respawn()
{
	parameter.isRespawn = true;
	//死んだ時めっちゃ球出す
	if (respawnCount == 0.0f)
		world.Add(ACTOR_ID::PLAYER_BULLET_ACTOR,
			std::make_shared<DeadBulletManager>(world, parameter.mat.GetPosition() + Vector3(0, 5, 0)
				, damagePlayerNumber));
	//プレイヤーの状態変更
	playerState = PlayerState::PLAYERRESPAWN;
	//カメラをキルカメラに
	cameraActor->SetCameraState(CameraState::KILL_CAMERA);

	respawnCount += Time::DeltaTime;
	if (respawnCount >= 5.0f)
	{
		parameter.isRespawn = false;
		cameraActor->SetCameraState(CameraState::DEFAULT);
		respawnCount = 0.0f;
		parameter.HP = 10;
		//ポジションリセットする
		mPosition = respawnPoint;
	}
}

//プレイヤーの状態を取得
PlayerState Player::GetPlayerState()
{
	return playerState;
}
//受けたダメージのプレイヤーのナンバーを取得
PLAYER_NUMBER Player::GetDamagePlayer()
{
	return damagePlayerNumber;
}
