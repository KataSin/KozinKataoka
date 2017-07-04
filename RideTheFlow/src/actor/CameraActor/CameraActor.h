#pragma once
#include "../Actor.h"
#include "../Collision.h"
#include <memory>
#include <vector>

//カメラ感度
const float CameraSpeed = 100.0f;
//カメラとプレイヤーの距離
const float CameraDis = 30.0f;

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
	void SetCameraPoint(const Vector2& center, const Vector2& areaMin, const Vector2& areaMax);

public:
	//カメラの状態をセットする
	void SetCameraState(CameraState state);
	//弾を打つターゲットの位置を取得
	Vector3 GetTarget();
	//ターゲットの遠さを設定
	void SetTargetDistance(float dis);
	//表示位置設定
	void SetCamera(int num);
	//注視点とカメラのLineを取得
	Line GetCameraLine();
private: 
	//カメラの別のマトリクス
	Matrix4 mCameraMat;
	Vector3 mPosition;
	//カメラスタテ
	CameraState mCameraState;
	//注視点
	Vector3 mTargetPos;
	//バネカメラ
	Vector3 mRestPos;
	Vector3 mVelocity;

	//カメラの角度
	float mRotateLeft;
	float mRotateUp;

	//キルカメラ
	float mKillRotateY;
	//プレイヤー情報
	Player* mPlayer;
	Matrix4 mPlayerMat;
	//パッドの情報
	int mPad;
	//カメラの当たった関係
	Vector3 mIsColPos;
	std::vector<Vector3>mIsColVectorPos;
	bool mIsColFlag;
	//ターゲットとプレイヤーの距離
	float mDis;
};