#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../GameManager/GameManager.h"
#include <vector>

class  Result : public IScene
{

public:
	//コンストラクタ 
	Result(GameManager& gameManager);
	//デストラクタ
	~Result();

	//更新前初期化
	virtual void Initialize() override;
	//更新処理
	virtual void Update()override;
	//描画処理
	virtual void Draw() override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//終了時処理
	virtual void End()override;

private:
	GameManager* mGameManager;
	bool  mIsEnd;
	World wo;
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

	//UIの
	int test;
};