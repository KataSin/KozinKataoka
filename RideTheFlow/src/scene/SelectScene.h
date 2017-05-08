#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GameManager/GameManager.h"

class  SelectScene : public IScene
{
public:
	//コンストラクタ 
	SelectScene(GameManager& gameManager);
	//デストラクタ
	~SelectScene();
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
	ActorPtr mMaster;
	bool  mIsEnd;
	World wo;
	Light light;
	bool player2Flag;
	bool player3Flag;
	bool player4Flag;
	std::vector<int> pads;
};