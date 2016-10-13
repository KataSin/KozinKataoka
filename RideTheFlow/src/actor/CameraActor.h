#pragma once
#include "Actor.h"
#include "../camera/Camera.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include <memory>
#include "Collision.h"
//#include "Player.h"

//カメラ感度
const float CameraSpeed = 100.0f;
//カメラとプレイヤーの距離
const float CameraDis = 20.0f;

class Player;

enum CameraState
{
	DEFAULT,
	ATTACKMACHINEGUN,
	ATTACKSNIPERGUN,
	ATTACKSHOTGUN,
	DROP_DOWN_CAMERA,
	KILL_CAMERA,
};

class CameraActor :public Actor, public std::enable_shared_from_this<CameraActor>
{
public:
	CameraActor(IWorld& world, Actor &parent_);
	~CameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor & other, CollisionParameter colpara);

private:
	void SpringCamra(const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass);
private:
	void StateUpdate(CameraState state);
	void Default();
	void KillCmaera();
	void DropDownCamera();

public:
	void SetCameraState(CameraState state);
	Vector3 GetTarget();
	void SetTargetDistance(float dis)
	{
		mDis = dis;
	}
	void SetCamera()
	{
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
		//カメラ
		Camera::GetInstance().Update();
		Camera::GetInstance().SetRange(0.1f, 9999.0f);
		Camera::GetInstance().Position.Set(mPosition);
		Camera::GetInstance().Target.Set(target);
		Camera::GetInstance().Up.Set(Vector3::Up);
	}
	Line GetCameraLine()
	{
		Line line;
		line.startPos = target;
		line.endPos = Vector3(0, 0, 1)*CameraDis
			*Matrix4::RotateX(rotateLeft)*Matrix4::RotateY(rotateUp)
			+ playerMat.GetPosition();
		return line;
	}
private: 
	//カメラの別のマトリクス
	Matrix4 CameraMat;
	Vector3 mPosition;
	//カメラスタテ
	CameraState cameraState;
	//注視点
	Vector3 target;
	//バネカメラ
	Vector3 restPos;
	Vector3 velocity;

	//カメラの角度
	float rotateLeft;
	float rotateUp;

	//キルカメラ
	float killRotateY;
	//プレイヤー情報
	Player* mPlayer;
	Matrix4 playerMat;
	//パッドの情報
	int pad;
	//カメラの当たった関係
	Vector3 isColPos;
	bool isColFlag;
	//ターゲットとプレイヤーの距離
	float mDis;
};