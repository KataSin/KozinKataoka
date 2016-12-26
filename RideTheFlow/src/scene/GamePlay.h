#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GamePlayManager/GamePlayManager.h"
#include "../GameManager/GameManager.h"

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

private:
	typedef std::shared_ptr<GamePlayManager>GamePlayManagerPtr;
	GamePlayManagerPtr mGamePlayManager;
	GameManager* mGameManager;
	Scene mNextScene;
	bool  mIsEnd;
	World wo;
	Light light;

	int test;

	int mRandCount;
	int mEndRaundCount;
};