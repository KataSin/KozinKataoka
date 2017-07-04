#include "Player.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../../graphic/Sprite.h"
#include "../../graphic/Model.h"
#include "../../input/Keyboard.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../camera/Camera.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../input/GamePad.h"
#include "../../sound/Sound.h"

#include "../CameraActor/CameraActor.h"
#include "../../actor/PlayerBullet/PlayerBullet.h"
#include "../PlayerBullet\TargetRay.h"
#include "../PlayerAttack\PlayerAttackManager\PlayerAttackManager.h"
#include "../../UIactor/DamageUI/DamageUI.h"
#include "../../Def.h"
#include "../ParticleManager\ParticleManager.h"
#include "../../UIactor/DamageBackUI/DamageBackUI.h"

const float PlayerSpeed = 25.0f;
const float LowPlayerSpeed = 5.0f;
const float AttackPlayerSpeed = 5.0f;

const float IsDamageMachineKnockBack = 1.0f;
const float IsDamageSniperKnockBack = 4.0f;
const float IsDamageShotKnockBack = 2.0f;
const float KnockBackTikara = 75.0f;
Player::Player(IWorld& world, Vector3 position_, float rotateY, PLAYER_NUMBER player) :
	Actor(world),
	mCameraMat(Matrix4::Identity),
	mCameraPos(Vector3::Zero),
	mCoppyPos(Vector3::Zero),
	mVecPos(Vector3::Zero),
	mVelocity(Vector3::Zero),
	mPlayerVelocity(Vector3::Zero),
	mPadVec(Vector2::Zero),
	mCurPlayerPos(Vector3::Zero),
	mRespawnCount(0.0f),
	mAngleY(rotateY),
	mJumpCount(0.0f),
	mJumpFlag(false),
	mPosition(position_),
	mDropDownFlag(false),
	mIsDamageMachine(false),
	mIsDamageSniper(false),
	mIsDamageShot(false),
	mSniperFlag(false)
{
	//パラメーター初期化
	parameter.HP = 0;
	parameter.playNumber = player;
	parameter.isDead = false;
	parameter.height = 5.0f;
	parameter.radius = 2.0f;
	parameter.isRespawn = false;
	parameter.id = ACTOR_ID::PLAYER_ACTOR;
	parameter.mat =
		Matrix4::Scale(0)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(mAngleY)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
	mPlayerState = PlayerState::PLAYERSTOP;
	//カラーの設定
	switch (parameter.playNumber)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		mColor = Vector4(0.0f, 0.0f, 255.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		mColor = Vector4(255.0f, 0.0f, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_3:
	{
		mColor = Vector4(0.0f, 255.0f, 0.0f, 1.0f);
		break;
	}
	case PLAYER_NUMBER::PLAYER_4:
	{
		mColor = Vector4(255.0f, 255.0f, 0.0f, 1.0f);
		break;
	}
	}

	//カメラを追加
	world.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<CameraActor>(world, *this, mAngleY));
	//武器を追加
	world.Add(ACTOR_ID::MANAGER_ACTOR, std::make_shared<PlayerAttackManager>(world, *this));
	//カメラの向いている方向にプレイヤーも向く
	float mAngleY = world.GetCamera(parameter.playNumber)->GetParameter().mat.GetRotateDegree().y;
	mRotate = Vector3(0.0f, mAngleY, 0.0f);
	//プレイヤー個別設定
	PlayerNumSet(parameter.playNumber);
	//ダメージUIを追加
	world.UIAdd(UI_ID::DAMAGE_NUM_UI, std::make_shared<DamageUI>(world, mUiDamagePos, this));
	//死んだ時のUI
	world.UIAdd(UI_ID::DAMAGE_BACK_UI, std::make_shared<DamageBackUI>(world, mUiDamageBackPos, *this));
	//アニメーションクラスの生成
    mAnim = std::make_shared<AnimationClass>(this, ANIMATION::PLAYER_IDLE_ANIM, mModelId);
	//パッド設定
	mPad = world.GetPadNum()[(int)(parameter.playNumber - 1)];
	//カメラ
	mCameraActor = dynamic_cast<CameraActor*>(world.GetCamera(parameter.playNumber).get());
	//パーティクル設定
	ParticleSetting();
	//パーティクル追加
	mDashParticle = std::make_shared<ParticleEffectSystem>(world, mDashParticleSet);
	world.Add(ACTOR_ID::PARTICLE_ACTOR, mDashParticle);

	//プレイヤーのスピード設定
	mPlayerSpeed = PlayerSpeed;
	//リスポーン地点設定
	mRespawnPoint = position_;

	//パーティクル設定

}
Player::~Player() {
}

void Player::Update() {

	mAnim->update();

	//ポジションをセーブ
	mCoppyPos = mPosition;

	//自分のカメラを取得
	mCameraMat = mCameraActor->GetParameter().mat;
	mCameraPos = mCameraMat.GetPosition();



	if (parameter.mat.GetPosition().y <= -10.0f)
	{
		mDropDownFlag = true;
		Respawn();
	}

	//リスポーン中以外は行動可能
	if (mPlayerState != PlayerState::PLAYERRESPAWN&&
		world.GetInputPlayer())
	{
		//重力処理
		if (mGravityFlag)
			mVelocity.y -= 30.0f*Time::GetInstance().deltaTime();
		else if (mPlayerState != PlayerState::PLAYERJUMP)
			mVelocity.y = 0.0f;
		mPosition += mVelocity*Time::GetInstance().deltaTime();
		//どのアニメーションを再生するか
		PlayerAnimetion(mPlayerState);
		//歩き
		Move();
		//ジャンプ
		Jump();
		//ノックバック
		AttackMove();
	}
	//パーティクル
	ParticleUpdate();
	//無敵時間
	if (mSniperFlag)
	{
		mSniperCount += Time::GetInstance().deltaTime();
		if (mSniperCount >= 0.5f)
		{
			mSniperCount = 0.0f;
			mSniperFlag = false;
		}
	}
	//マトリクス計算
	parameter.mat =
		Matrix4::Scale(0.15f)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(mAngleY)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);

	//フラグの初期化
	mGravityFlag = true;
	mLowStateFlag = false;

	//速度取得
	mPlayerVelocity = mPosition - mCurPlayerPos;
	mCurPlayerPos = mPosition;
}
void Player::Draw() const {
	if (mPlayerState != PlayerState::PLAYERRESPAWN)
	{
		//Model::GetInstance().Draw(MODEL_ID::PLAYER_MODEL, parameter.mat);
		mAnim->draw();
	}
	//if (parameter.playNumber == PLAYER_NUMBER::PLAYER_1)
		//DrawFormatString(550, 25, GetColor(255, 0, 255), "プレイヤー1蓄積ダメージ:%d", (int)parameter.HP);
	//else
	//	DrawFormatString(550, 25 + 32, GetColor(255, 0, 255), "プレイヤー2蓄積ダメージ:%f", testaaa);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + Vector3(0.0f, parameter.height / 2.0f, 0.0f))
	//	, parameter.radius, 10, 1, 1, FALSE);
	//DrawLine3D(Vector3::ToVECTOR(mPosition), Vector3::ToVECTOR(mPosition + mVecPos), GetColor(255, 255, 255));
}

void Player::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLATE_PLAYER_COL&&!mJumpFlag)
	{
		//自分の色のプレートじゃなかったら
		if (other.GetParameter().playNumber != parameter.playNumber &&
			other.GetParameter().playNumber != PLAYER_NUMBER::PLAYER_NULL)
			mLowStateFlag = true;
		mGravityFlag = false;
		mPlayerState = PlayerState::PLAYERSTOP;
	}

	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL&&
		other.GetParameter().id == ACTOR_ID::PLAYER_BULLET_ACTOR)
	{
		mIsDamageMachine = true;
		parameter.HP += 5;
		//誰の弾を受けたか保存
		mDamagePlayerNumber = other.GetParameter().playNumber;
		//攻撃されたプレイヤーのポジション
		mDamagePlayerPos = world.GetPlayer(other.GetParameter().playNumber)->GetParameter().mat.GetPosition();
		Sound::GetInstance().PlaySE(SE_ID::PLAYER_DAMAGE_SE, DX_PLAYTYPE_BACK);

	}
	//ショットガンの弾
	if (colpara.colID == COL_ID::PLAYERBULLET_PLAYER_COL&&
		other.GetParameter().id == ACTOR_ID::PLAYER_BULLET_SHOT_ACTOR)
	{
		mIsDamageShot = true;
		parameter.HP += 7;
		//誰の弾を受けたか保存
		mDamagePlayerNumber = other.GetParameter().playNumber;
		//攻撃されたプレイヤーのポジション
		mDamagePlayerPos = world.GetPlayer(other.GetParameter().playNumber)->GetParameter().mat.GetPosition();
		Sound::GetInstance().PlaySE(SE_ID::PLAYER_DAMAGE_SE, DX_PLAYTYPE_BACK);

	}

	//スナイパー用
	if (colpara.colID == COL_ID::PLAYER_GUNLINE_COL&&
		colpara.colFlagSub&&!mSniperFlag)
	{
		//ノックバック用フラグ
		mIsDamageSniper = true;
		//無敵判定のフラグ
		mSniperFlag = true;
		//ダメージを食らう
		parameter.HP += 15;
		//誰の弾を受けたか保存
		mDamagePlayerNumber = other.GetParameter().playNumber;
		//攻撃されたプレイヤーのポジション
		mDamagePlayerPos = world.GetPlayer(other.GetParameter().playNumber)->GetParameter().mat.GetPosition();
		Sound::GetInstance().PlaySE(SE_ID::PLAYER_DAMAGE_SE, DX_PLAYTYPE_BACK);
	}

	if (colpara.colID == COL_ID::PLAYER_TREE_COL)
	{
		//めり込み防止
		mPosition = colpara.colPos;
	}
	if (colpara.colID == COL_ID::PLAYER_STAGELINE_COL&&
		mPlayerState != PlayerState::PLAYERRESPAWN) {
		//線に当たったら死ぬ
		Respawn();
	}
}

void Player::RotateMovePlayer()
{
	//プレイヤーの移動ベクトルを取得
	mVecPos = mPosition - mCoppyPos;
	//正規化＆ベクトルのy軸無視
	mVecPos = (mVecPos*Vector3(1, 0, 1)).Normalized();

	//プレイヤーの向き取得
	Vector3 playerFront = mVecPos;
	Vector3 playerLeft = Vector3::Cross(Vector3::Up, mVecPos).Normalized();
	Vector3 playerUp = Vector3::Cross(playerFront, playerLeft).Normalized();

	//移動量がゼロだったら直前の角度を保持
	if (mVecPos.x != 0)
		mAngleY = -(Math::Atan2(mVecPos.z, mVecPos.x)*180.0f / 3.1415f) - 90.0f;
	//アッタック中のプレイヤー向き
	if (PlayerState::PLAYERATTACK == mPlayerState)
	{
		//カメラの方向を計算
		Vector3 front = (mCameraMat.GetPosition() - mCameraActor->GetTarget()).Normalized();
		Vector3 left = Vector3::Cross(front, Vector3::Up).Normalized();
		Vector3 up = Vector3::Cross(front, left).Normalized();
		Matrix4 mat;
		mat.SetFront(front);
		mat.SetLeft(left);
		mat.SetUp(up);
		mAngleY = mat.GetRotateDegree().y;
	}
}

void Player::Move()
{
	/************************************************************************/
	//移動の仕様はsplatoonと同じ（カメラから見た移動＆球を撃っているときは蟹移動）
	//ゲームパッド対応にすよ
	/************************************************************************/


	//カメラの方向を計算
	Vector3 cameraFront = (parameter.mat.GetPosition() - mCameraPos).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3::Up).Normalized();
	Vector3 cameraUp = Vector3::Cross(cameraFront, cameraLeft).Normalized();

	mPadVec = GamePad::GetInstance().Stick(mPad)*mPlayerSpeed;


	mPosition -= mPadVec.y*Vector3(cameraFront*Vector3(1, 0, 1))*Time::GetInstance().deltaTime();
	mPosition -= mPadVec.x*Vector3(cameraLeft*Vector3(1, 0, 1))*Time::GetInstance().deltaTime();

	//キーボード処理　テスト用
	if (parameter.playNumber == PLAYER_NUMBER::PLAYER_2)
	{
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		{
			mPosition += mPlayerSpeed*cameraFront*Vector3(1, 0, 1)*Time::GetInstance().deltaTime();
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		{
			mPosition += mPlayerSpeed*-cameraFront*Vector3(1, 0, 1)*Time::GetInstance().deltaTime();
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		{
			mPosition += mPlayerSpeed*cameraLeft*Vector3(1, 0, 1)*Time::GetInstance().deltaTime();
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		{
			mPosition += mPlayerSpeed*-cameraLeft*Vector3(1, 0, 1)*Time::GetInstance().deltaTime();
		}
	}
	//移動先に回転※移動した最後に実行すること
	RotateMovePlayer();
	mCameraActor->SetCameraState(CameraState::DEFAULT);

	//敵のプレートに当たってたらスピードダウン
	//if (mLowStateFlag)
	//{
	//	mPlayerSpeed = LowPlayerSpeed;
	//}
	//else if (!mLowStateFlag)
	//{
	//	mPlayerSpeed = PlayerSpeed;
	//}
}

void Player::AttackMove()
{
	//相手から自身のベクトルを計算
	Vector3 damageToPlayer = (parameter.mat.GetPosition() - mDamagePlayerPos).Normalized();
	if (mIsDamageMachine)
	{
		mKnockBackVelo += damageToPlayer*(parameter.HP)*IsDamageMachineKnockBack;
		mIsDamageMachine = false;
	}
	if (mIsDamageSniper)
	{
		mKnockBackVelo += damageToPlayer*(parameter.HP)*IsDamageSniperKnockBack;
		mIsDamageSniper = false;
	}
	if (mIsDamageShot)
	{
		mKnockBackVelo += damageToPlayer*(parameter.HP)*IsDamageShotKnockBack;
		mIsDamageShot = false;
	}
	//減速
	Deceleration(mKnockBackVelo);
	//Y軸は無視
	mKnockBackVelo.y = 0;
	mPosition += mKnockBackVelo*Time::GetInstance().deltaTime();
}
//減速関数
void Player::Deceleration(Vector3& pos)
{
	pos += -pos.Normalized()*KnockBackTikara*Time::GetInstance().deltaTime();

	if (pos.x <= 0.5f&&pos.x >= -0.5f) {
		pos = Vector3::Zero;
	}
}

void Player::Jump()
{
	//ジャンプした瞬間何秒間は地面のあたり判定無効
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3, mPad) &&
		!mGravityFlag)
	{
		Sound::GetInstance().PlaySE(SE_ID::PLAYER_JUMP_SE,DX_PLAYTYPE_BACK);
		mVelocity.y = 11.0f;
		mJumpFlag = true;
		mPlayerState = PlayerState::PLAYERJUMP;
	}
	if (mJumpFlag)
	{
		mJumpCount += Time::GetInstance().deltaTime();
		if (mJumpCount >= 0.02f)
		{
			mJumpFlag = false;
			mJumpCount = 0.0f;
		}
	}
}

void Player::Respawn()
{
	if (mPlayerState != PlayerState::PLAYERRESPAWN)
		world.Add(ACTOR_ID::PARTICLE_ACTOR, std::make_shared<ParticleManager>
			(world, parameter.mat.GetPosition(),
				Vector3::Zero,
				mColor,
				5,
				Vector3(20, 20, 20),
				Vector3(-20, -20, -20)));

	if (!parameter.isRespawn)Sound::GetInstance().PlaySE(SE_ID::PLAYER_DEAD_SE, DX_PLAYTYPE_BACK);

	parameter.isRespawn = true;
	//プレイヤーの状態変更
	mPlayerState = PlayerState::PLAYERRESPAWN;


	if (mDropDownFlag)
		mCameraActor->SetCameraState(CameraState::DROP_DOWN_CAMERA);
	//ノックバックの速度を初期化
	mKnockBackVelo = Vector3::Zero;
}

//プレイヤーの状態を取得
PlayerState Player::GetPlayerState()
{
	return mPlayerState;
}
//受けたダメージのプレイヤーのナンバーを取得
PLAYER_NUMBER Player::GetDamagePlayer()
{
	return mDamagePlayerNumber;
}



void Player::PlayerNumSet(PLAYER_NUMBER num)
{
	if (world.GetPlayerNum() == 2) {
		switch (num)
		{
		case PLAYER_NULL:
			break;
		case PLAYER_1: {
			mUiDamagePos = Vector2(28, WINDOW_HEIGHT / 2 - 55);
			mUiDamageBackPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
			mModelId = MODEL_ID::PLAYER1_MODEL;
			break;
		}
		case PLAYER_2: {
			mUiDamagePos = Vector2(28, WINDOW_HEIGHT - 55);
			mUiDamageBackPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 4);
			mModelId = MODEL_ID::PLAYER2_MODEL;
			break;
		}
		}
	}
	else {
		//パッドのプレイヤー設定
		switch (num)
		{
		case PLAYER_NULL:
			break;
		case PLAYER_1: {
			mUiDamagePos = Vector2(28, WINDOW_HEIGHT / 2 - 55);
			mUiDamageBackPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);
			mModelId = MODEL_ID::PLAYER1_MODEL;
			break;
		}
		case PLAYER_2: {
			mUiDamagePos = Vector2(WINDOW_WIDTH - 56, WINDOW_HEIGHT / 2 - 55);
			mUiDamageBackPos = Vector2(WINDOW_WIDTH - WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);
			mModelId = MODEL_ID::PLAYER2_MODEL;
			break;
		}
		case PLAYER_3: {
			mUiDamagePos = Vector2(28, WINDOW_HEIGHT - 55);
			mUiDamageBackPos = Vector2(WINDOW_WIDTH / 4, WINDOW_HEIGHT - WINDOW_HEIGHT / 4);
			mModelId = MODEL_ID::PLAYER3_MODEL;
			break;
		}
		case PLAYER_4: {
			mUiDamageBackPos = Vector2(WINDOW_WIDTH - WINDOW_WIDTH / 4, WINDOW_HEIGHT - WINDOW_HEIGHT / 4);
			mUiDamagePos = Vector2(WINDOW_WIDTH - 56, WINDOW_HEIGHT - 55);
			mModelId = MODEL_ID::PLAYER4_MODEL;
			break;
		}
		}
	}
}

void Player::PlayerAnimetion(PlayerState state)
{
	if (mPlayerState == PlayerState::PLAYERJUMP) {
		mAnim->changeAnim(ANIMATION::PLAYER_JUMP_ANIM);
		return;
	}

	//今回は押したら絶対に武器を構えるため
	if (GamePad::GetInstance().ButtonStateDown(PADBUTTON::NUM6, mPad)) {
		if (mPadVec.x == 0 && mPadVec.y == 0) mAnim->changeAnim(ANIMATION::PLAYER_BUKI_IDLE_ANIM);
		else {
			mAnim->changeAnim(ANIMATION::PLAYER_BUKI_RUN_ANIM);
			mPlayerState = PlayerState::PLAYERATTACK;
		}
		return;
	}
	//歩きアニメーション
	else {
		if (mPadVec.x == 0 && mPadVec.y == 0) mAnim->changeAnim(ANIMATION::PLAYER_IDLE_ANIM);
		else {
			mAnim->changeAnim(ANIMATION::PLAYER_RUN1_ANIM);
			mPlayerState = PlayerState::PLAYERWALK;
		}
		return;
	}
}

void Player::ParticleSetting()
{
	//ダッシュパーティクル設定
	mDashParticleSet.position = parameter.mat.GetPosition();
	mDashParticleSet.isParticleNum = 5;
	mDashParticleSet.SpawnSpeed = 0.2f;
	mDashParticleSet.IsDeadTime = 1.0f;
	mDashParticleSet.Vec = -parameter.mat.GetFront();
	mDashParticleSet.VecRandom = parameter.mat.GetLeft();
	mDashParticleSet.InitializeVelocity = Vector3(5, 5, 5);
	mDashParticleSet.MinusAlphaNum = 2.0f;
	mDashParticleSet.MinusAlphaTime = 0.5f;
	mDashParticleSet.DecelerationTime = 0.3f;
	mDashParticleSet.Deceleration = 10.0f;
	std::vector<SPRITE_ID> ids;
	ids.push_back(SPRITE_ID::KEMURI_1_SPRITE);
	ids.push_back(SPRITE_ID::KEMURI_2_SPRITE);
	ids.push_back(SPRITE_ID::KEMURI_3_SPRITE);
	mDashParticleSet.texture = ids;
}

void Player::ParticleUpdate()
{
	//パーティクルセット
	mDashParticleSet.position = parameter.mat.GetPosition();
	mDashParticleSet.Vec = parameter.mat.GetFront();
	mDashParticleSet.VecRandom = parameter.mat.GetLeft();
	if (mPlayerState == PlayerState::PLAYERWALK)
		mDashParticleSet.isParticle = true;
	else
		mDashParticleSet.isParticle = false;
	static_cast<ParticleEffectSystem*>(mDashParticle.get())->SetParticle(mDashParticleSet);
}
void Player::SetPlayerState(PlayerState state)
{
	mPlayerState = state;
}
void Player::SetRotateY(float angleY)
{
	mAngleY = angleY;
}
Vector3 Player::GetPlayerGunPos()
{
	return parameter.mat.GetPosition() - (parameter.mat.GetFront().Normalized()*4.0f) + Vector3(0.0f, 2.7f, 0.0f);
}