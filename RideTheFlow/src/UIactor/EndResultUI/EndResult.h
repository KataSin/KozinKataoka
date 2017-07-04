#pragma once
#include "../UIActor.h"
#include "../../GameManager/GameManager.h"
#include "../../math/Matrix4.h"
#include "../../actor/Stage/Stage.h"
#include <vector>
#include <memory>
class EndResultUI : public UIActor
{
public:
	EndResultUI(IWorld& world, GameManager& gameManager);
	~EndResultUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

public:
	//終わってもよいか？
	bool GetIsEnd();
private:
	//観客セット
	void SuportSet();
private:
	//ゲームマネージャー
	GameManager* mGameManager;
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

	//注視点の位置
	Vector3 mTargetPos;
	//注視点の行くべき位置
	Vector3 mResTargetPos;
	//注視点速度
	Vector3 mTargetVelo;

	//Winnerα
	float mWinnerAlpha;
	//アクションタイム(イベント系)
	float mActionTime;
	//ボタンおしてαカウント
	float mPleaseAphaCount;
	//終わってもよいか？
	bool mIsEnd;
	//観客の情報
	std::vector<Stage::KankyakuState> mKankyakuMats;

};