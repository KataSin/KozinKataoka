#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GameManager/GameManager.h"

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
	Light light;

	int test;
};