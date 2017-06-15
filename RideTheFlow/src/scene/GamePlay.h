#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GamePlayManager/GamePlayManager.h"
#include "../GameManager/GameManager.h"

class GameTimerUI;
class GamePlayFontUI;
class  GamePlay : public IScene
{

public:
	//コンストラクタ 
	GamePlay(GameManager& gameManager);
	//デストラクタ
	~GamePlay();

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

public:
	//カメラをセット（プレイ人数によって変える）
	void SetCamera(int num);

private:
	//ゲームプレイマネージャーポインター
	typedef std::shared_ptr<GamePlayManager>GamePlayManagerPtr;
	GamePlayManagerPtr mGamePlayManager;
	//ゲームマネージャー
	GameManager* mGameManager;
	//次のシーン
	Scene mNextScene;
	//エンドフラグ
	bool  mIsEnd;
	//ワールド
	World wo;
	//ライト（たぶん消す）
	Light light;
	//ゲームタイマー
	GameTimerUI* mGameTimer;
	//フォント
	GamePlayFontUI* fontUi;
	//今何ラウンド目か
	int mRandCount;
	//何ラウンド目に終わるか
	int mEndRaundCount;
	//スタート時のフォントフラグ
	bool mStartFontFlag;
	//フォントフラグ
	bool mFontFlag;
	bool mIsEndRanund;
	//終わるフラグ
	bool mRaundTimeUpFlag;
	bool mRaundNoPlayerFlag;
	//勝ったプレイヤー
	PLAYER_NUMBER mWinPlayer;
	//何人プレイヤーがいるか
	int mPlayerNum;

	//スタートSEを鳴らすタイミング
	float mSeTimer;
	bool mSeFlag;
	//流すBGM
	BGM_ID mBgm;
};