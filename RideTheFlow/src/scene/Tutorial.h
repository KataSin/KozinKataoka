#pragma once
#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>

class  Tutorial : public IScene
{

public:
	//コンストラクタ 
	Tutorial();
	//デストラクタ
	~Tutorial();

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
	//次のシーン
	Scene mNextScene;
	//エンドフラグ
	bool  mIsEnd;
	//ワールド
	World wo;
	//何人プレイヤーがいるか
	int mPlayerNum;
};