#pragma once
#include "../UIActor.h"
#include "../../GameManager/GameManager.h"
#include "../../math/Matrix4.h"
#include <vector>
#include <memory>
class EndResultUI : public UIActor
{
public:
	EndResultUI(IWorld& world, GameManager& gameManager);
	~EndResultUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//ゲームマネージャー
	GameManager* mGameManager;
	bool  mIsEnd;
	//ステージのマトリックス
	Matrix4 mStageMat;
	//台のマトリックス
	Matrix4 mDaiMat;
	//スカイボックスマトリックス
	Matrix4 mSkyMat;
	//順位に応じての座標
	std::vector<Vector3> mRankPos;

	//カメラの位置
	Vector3 mCameraPos;
	//カメラの行くべき位置
	Vector3 mResCameraPos;
	//カメラ速度
	Vector3 mCameraVelo;


	//アクションタイム(イベント系)
	float mActionTime;

};