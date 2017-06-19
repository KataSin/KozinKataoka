#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>
#include "../UIactor/NumberTexture/NumberTexture.h"

class  TitleScene : public IScene
{

public:
	//コンストラクタ 
	TitleScene();
	//デストラクタ
	~TitleScene();

	//更新前初期化
	virtual void Initialize() override;
	//更新処理
	virtual void Update()override;
	//描画処理
	virtual void Draw()override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//終了時処理
	virtual void End()override;

	virtual bool GetGameEndFlag()override;
private:
	bool  mIsEnd;
	World wo;
	//タイトルのUI
	UIActorPtr mTitleUi;
	//次のシーン
	Scene mScene;
	//ゲーム終わるかどうか
	bool mGameEndFlag;
};