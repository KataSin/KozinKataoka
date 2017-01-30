#pragma once
#include "Actor.h"
#include "../camera/Camera.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include <memory>
#include "Collision.h"
#include <vector>
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
	CameraActor(IWorld& world, Actor &parent_, float angleY);
	~CameraActor();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor & other, CollisionParameter colpara);

private:
	//バネ補正
	void SpringCamra(const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass);
private:
	//カメラの状態関数
	void StateUpdate(CameraState state);
	void Default();
	void KillCmaera();
	void DropDownCamera();

public:
	//カメラの状態をセットする
	void SetCameraState(CameraState state);
	//弾を打つターゲットの位置を取得
	Vector3 GetTarget();
	//ターゲットの遠さを設定
	void SetTargetDistance(float dis)
	{
		mDis = dis;
	}
	//表示位置設定
	void SetCamera();
	//注視点とカメラのLineを取得
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
	std::vector<Vector3>isColVectorPos;
	bool isColFlag;
	//ターゲットとプレイヤーの距離
	float mDis;
};