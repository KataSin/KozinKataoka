#include "CameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include "../math/Quaternion.h"
#include "../math/Math.h"
#include"Player.h"
#include <string>
#include "../input/GamePad.h"

CameraActor::CameraActor(IWorld& world, Actor &parent_) :
	Actor(world),
	mPlayer(dynamic_cast<Player*>(&parent_)),
	cameraState(CameraState::DEFAULT),
	mPosition(Vector3::Zero),
	velocity(Vector3::Zero),
	mDis(30.0f),
	rotateLeft(0.0f),
	rotateUp(0.0f),
	killRotateY(0.0f)
{
	//カメラとプレイヤーの紐づけ
	parent = &parent_;
	playerMat = parent->GetParameter().mat;
	//注視点を設定
	target = playerMat.GetPosition() + Vector3(0, 10, 0);
	//パラメーター設定
	parameter.playNumber = parent_.GetParameter().playNumber;
	parameter.isDead = false;
	parameter.mat = Matrix4::Scale(0)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(0)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);

	//パッドの設定
	switch (parameter.playNumber)
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


	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(target);
	Camera::GetInstance().Up.Set(Vector3::Up);


}
CameraActor::~CameraActor()
{

}
void CameraActor::Update()
{
	//プレイヤーマトリックス
	playerMat = parent->GetParameter().mat;
	//変換
	mPlayer = dynamic_cast<Player*>(parent);
	//あたり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::CAMERA_PLATE_COL);
	//カメラ状態を更新
	StateUpdate(cameraState);

	//カメラの向きを生成
	Vector3 cameraFront = (playerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3::Up).Normalized();
	Vector3 cameraUp = Vector3::Cross(cameraFront, cameraLeft);

	//カメラの向きからマトリクスを生成
	parameter.mat.SetFront(cameraFront);
	parameter.mat.SetLeft(cameraLeft);
	parameter.mat.SetUp(cameraUp);
	//カメラの障害物に当たった時の補正
	if (isColFlag)
	{
		mPosition = isColPos;
	}
	//ポジションを設定
	parameter.mat.SetPosition(mPosition);
	//フラグを初期化
	isColFlag = false;
}
void CameraActor::Draw() const
{

}

void CameraActor::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (COL_ID::CAMERA_PLATE_COL == colpara.colID)
	{
		isColFlag = true;
		isColPos = colpara.colPos;
	}

}

void CameraActor::SpringCamra(const Vector3 & restPosition,
	float stiffness, float friction, float mass)
{
	// バネの伸び具合を計算
	Vector3 stretch = mPosition - restPosition;
	// バネの力を計算
	Vector3 force = -stiffness * stretch;
	// 加速度を計算
	Vector3 acceleration = force / mass;
	// 移動量を計算
	velocity = friction * (velocity + acceleration);
	// 座標の更新
	mPosition += velocity;
}

void CameraActor::StateUpdate(CameraState state)
{
	switch (state)
	{
	case DEFAULT:
		Default();
		break;
	case KILL_CAMERA:
		KillCmaera();
		break;
	case DROP_DOWN_CAMERA:
		DropDownCamera();
		break;
	}
}

void CameraActor::Default()
{
	//パットのベクトルを取得
	Vector2 vec = GamePad::GetInstance().RightStick(pad);
	//ベクトルを足し算
	rotateUp += vec.x*CameraSpeed*Time::DeltaTime;
	rotateLeft -= vec.y*CameraSpeed*Time::DeltaTime;
	//キーボード処理
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	{
		rotateUp += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	{
		rotateUp -= CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
	{
		rotateLeft += CameraSpeed*Time::DeltaTime;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
	{
		rotateLeft -= CameraSpeed*Time::DeltaTime;
	}

	//Z軸回転制限
	rotateLeft = Math::Clamp(rotateLeft, -65.0f, 20.0f);
	//注視点設定
	target = playerMat.GetPosition() + Vector3(0, 6, 0);
	//カメラの位置を計算
	mPosition = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(rotateLeft)*Matrix4::RotateY(rotateUp)
		+ playerMat.GetPosition();
}

void CameraActor::KillCmaera()
{
	//倒された相手の取得
	Player* killPlayer;
	PLAYER_NUMBER num;
	num = dynamic_cast<Player*>(parent)->GetDamagePlayer();
	killPlayer = dynamic_cast<Player*>(world.GetPlayer(num).get());

	//倒された相手の回りをくるくると
	killRotateY += 70.0f*Time::DeltaTime;
	restPos = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(-30)*Matrix4::RotateY(killRotateY)
		+ killPlayer->GetParameter().mat.GetPosition();
	//注視点も変更
	target = killPlayer->GetParameter().mat.GetPosition() + Vector3(0, 2, 0);
	SpringCamra(restPos, 1.0f, 0.2f, 1.0f);
}
void CameraActor::DropDownCamera()
{
	//落ちたときは何もしない
}
Vector3 CameraActor::GetTarget()
{
	//注視点とカメラのポジションのベクトル
	Vector3 targetVec = (target - parameter.mat.GetPosition()).Normalized();
	//ここに球を撃つ
	Vector3 targetPos = targetVec * mDis + parameter.mat.GetPosition();
	//謎の補正
	return targetPos + Vector3(0.0f, 0.5f, 0.0f);
}

void CameraActor::SetCamera()
{
	//プレイヤーに応じて画面の位置を変更
	switch (parameter.playNumber)
	{
	case PLAYER_NUMBER::PLAYER_1:
	{
		SetCameraScreenCenter(640, 540);
		SetDrawArea(0, 360, 1281, 721);
		break;
	}
	case PLAYER_NUMBER::PLAYER_2:
	{
		SetCameraScreenCenter(640, 180);
		SetDrawArea(0, 0, 1281, 361);
		break;
	}
	}
	//カメラ設定
	Camera::GetInstance().Update();
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(target);
	Camera::GetInstance().Up.Set(Vector3::Up);
}

void CameraActor::SetCameraState(CameraState state)
{
	cameraState = state;
}
