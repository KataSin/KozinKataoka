#include "CameraActor.h"
#include "../../world/IWorld.h"
#include "../../Def.h"

#include "../Collision.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../time/Time.h"
#include "../../math/Quaternion.h"
#include "../../math/Math.h"

#include "../../camera/Camera.h"
#include"../Player/Player.h"

CameraActor::CameraActor(IWorld& world, Actor &parent_, float angleY) :
	Actor(world),
	mPlayer(dynamic_cast<Player*>(&parent_)),
	mCameraState(CameraState::DEFAULT),
	mPosition(Vector3::Zero),
	mVelocity(Vector3::Zero),
	mDis(30.0f),
	mRotateUp(0.0f),
	mRotateLeft(-50.0f),
	mKillRotateY(0.0f)
{
	//カメラとプレイヤーの紐づけ
	parent = &parent_;
	mRotateUp = angleY;
	mPlayerMat = parent->GetParameter().mat;
	//注視点を設定
	mTargetPos = mPlayerMat.GetPosition() + Vector3(0, 10, 0);
	//パラメーター設定
	parameter.playNumber = parent_.GetParameter().playNumber;
	parameter.isDead = false;
	parameter.mat = Matrix4::Scale(0)*
		Matrix4::RotateX(mRotateLeft)*
		Matrix4::RotateY(mRotateUp)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
	//パッド設定
	mPad = world.GetPadNum()[(int)(parameter.playNumber - 1)];

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(mTargetPos);
	Camera::GetInstance().Up.Set(Vector3::Up);
}
CameraActor::~CameraActor()
{

}
void CameraActor::Update()
{
	//プレイヤー動かない場合絶対デフォルト
	if (!world.GetInputPlayer())
		mCameraState = DEFAULT;
	//プレイヤーマトリックス
	mPlayerMat = parent->GetParameter().mat;
	//変換
	mPlayer = dynamic_cast<Player*>(parent);
	//あたり判定
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLATE_ACTOR, COL_ID::CAMERA_PLATE_COL);
	//カメラ状態を更新
	//if (mPlayer->GetPlayerState() != PlayerState::PLAYERRESPAWN)
		StateUpdate(mCameraState);


	//一番近い当たったポジションにする
	if (mIsColFlag) {
		Vector3 playerPos = parent->GetParameter().mat.GetPosition();
		Vector3 colPos = Vector3(999999);
		for (auto& i : mIsColVectorPos) {
			if (Vector3::Distance(playerPos, i) <= Vector3::Distance(colPos, playerPos))
				colPos = i;
		}
		mIsColPos = colPos;
		mIsColVectorPos.clear();
	}
	//カメラの向きを生成
	Vector3 cameraFront = (mPlayerMat.GetPosition() - parameter.mat.GetPosition()).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3::Up).Normalized();
	Vector3 cameraUp = Vector3::Cross(cameraFront, cameraLeft);

	//カメラの向きからマトリクスを生成
	parameter.mat.SetFront(cameraFront);
	parameter.mat.SetLeft(cameraLeft);
	parameter.mat.SetUp(cameraUp);
	//カメラの障害物に当たった時の補正
	if (mIsColFlag)
	{
		mPosition = mIsColPos;
	}
	//ポジションを設定
	parameter.mat.SetPosition(mPosition);
	//フラグを初期化
	mIsColFlag = false;
}
void CameraActor::Draw() const
{

}

void CameraActor::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (COL_ID::CAMERA_PLATE_COL == colpara.colID)
	{
		mIsColFlag = true;
		mIsColVectorPos.push_back(colpara.colPos);
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
	mVelocity = friction * (mVelocity + acceleration);
	// 座標の更新
	mPosition += mVelocity;
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
	Vector2 vec = GamePad::GetInstance().RightStick(mPad);
	//ベクトルを足し算
	mRotateUp += vec.x*CameraSpeed*Time::GetInstance().deltaTime();
	mRotateLeft -= vec.y*CameraSpeed*Time::GetInstance().deltaTime();
	//キーボード処理
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	{
		mRotateUp += CameraSpeed*Time::GetInstance().deltaTime();
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	{
		mRotateUp -= CameraSpeed*Time::GetInstance().deltaTime();
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
	{
		mRotateLeft += CameraSpeed*Time::GetInstance().deltaTime();
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
	{
		mRotateLeft -= CameraSpeed*Time::GetInstance().deltaTime();
	}

	//Z軸回転制限
	mRotateLeft = Math::Clamp(mRotateLeft, -65.0f, 20.0f);
	//注視点設定
	mTargetPos = mPlayerMat.GetPosition() + Vector3(0, 6, 0);
	//カメラの位置を計算
	mPosition = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(mRotateLeft)*Matrix4::RotateY(mRotateUp)
		+ mPlayerMat.GetPosition();
}
//遺産
void CameraActor::KillCmaera()
{
	//倒された相手の取得
	Player* killPlayer;
	PLAYER_NUMBER num;
	num = dynamic_cast<Player*>(parent)->GetDamagePlayer();
	if (num == PLAYER_NUMBER::PLAYER_NULL)return;
	killPlayer = dynamic_cast<Player*>(world.GetPlayer(num).get());

	//倒された相手の回りをくるくると
	mKillRotateY += 70.0f*Time::GetInstance().deltaTime();
	mRestPos = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(-20)*Matrix4::RotateY(mKillRotateY)
		+ killPlayer->GetParameter().mat.GetPosition();
	//注視点も変更
	mTargetPos = killPlayer->GetParameter().mat.GetPosition() + Vector3(0, 2, 0);
	SpringCamra(mRestPos, 0.2f, 0.5f, 1.0f);
}
void CameraActor::DropDownCamera()
{
	//落ちたときは何もしない
}
Vector3 CameraActor::GetTarget()
{
	//注視点とカメラのポジションのベクトル
	Vector3 mTargetPosVec = (mTargetPos - parameter.mat.GetPosition()).Normalized();
	//ここに球を撃つ
	Vector3 mTargetPosPos = mTargetPosVec * mDis + parameter.mat.GetPosition();
	//謎の補正
	return mTargetPosPos + Vector3(0.0f, 0.5f, 0.0f);
}

void CameraActor::SetCamera(int num)
{
	//2人ようカメラ設定
	if (num == 2) {
		switch (parameter.playNumber)
		{
		case PLAYER_NUMBER::PLAYER_1:
		{
			SetCameraPoint(
				Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / 4),
				Vector2::Zero,
				Vector2(WINDOW_WIDTH + 1, WINDOW_HEIGHT / 2 + 1)
				);
			break;
		}
		case PLAYER_NUMBER::PLAYER_2:
		{
			SetCameraPoint(
				Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 4),
				Vector2(0, WINDOW_HEIGHT / 2 + 1),
				Vector2(WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1));
			break;
		}
		}
	}
	else if (num == 3) {
		switch (parameter.playNumber)
		{
		case PLAYER_NUMBER::PLAYER_1:
		{
			SetCameraScreenCenter(320, 180);
			SetDrawArea(0, 0, WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT / 2 + 1);
			break;
		}
		case PLAYER_NUMBER::PLAYER_2:
		{
			SetCameraScreenCenter(960, 180);
			SetDrawArea(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH + 1, WINDOW_HEIGHT / 2 + 1);
			break;
		}
		case PLAYER_NUMBER::PLAYER_3:
		{
			SetCameraScreenCenter(320, 720 - 180);
			SetDrawArea(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT + 1);
			break;
		}
		}
	}
	else if (num == 4) {
		switch (parameter.playNumber)
		{
		case PLAYER_NUMBER::PLAYER_1:
		{
			SetCameraScreenCenter(320, 180);
			SetDrawArea(0, 0, WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT / 2 + 1);
			break;
		}
		case PLAYER_NUMBER::PLAYER_2:
		{
			SetCameraScreenCenter(960, 180);
			SetDrawArea(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH + 1, WINDOW_HEIGHT / 2 + 1);
			break;
		}
		case PLAYER_NUMBER::PLAYER_3:
		{
			SetCameraScreenCenter(320, 720 - 180);
			SetDrawArea(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT + 1);
			break;
		}
		case PLAYER_NUMBER::PLAYER_4:
		{
			SetCameraScreenCenter(960, 720 - 180);
			SetDrawArea(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1);
			break;
		}
		}
	}

	//カメラ設定
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(mPosition);
	Camera::GetInstance().Target.Set(mTargetPos);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();
}

void CameraActor::SetCameraPoint(const Vector2 & center, const Vector2 & areaMin, const Vector2 & areaMax)
{
	//カメラエリア設定
	SetCameraScreenCenter(center.x, center.y);
	SetDrawArea(areaMin.x, areaMin.y, areaMax.x, areaMax.y);
}

void CameraActor::SetCameraState(CameraState state)
{
	mCameraState = state;
}
void CameraActor::SetTargetDistance(float dis)
{
	mDis = dis;
}
Line CameraActor::GetCameraLine()
{
	Line line;
	line.startPos = mTargetPos;
	line.endPos = Vector3(0, 0, 1)*CameraDis
		*Matrix4::RotateX(mRotateLeft)*Matrix4::RotateY(mRotateUp)
		+ mPlayerMat.GetPosition();
	return line;
}
