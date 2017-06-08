#pragma once
#include "../UIActor.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../UIactor/UIActorPtr.h"
#include <vector>
class SceneChangeManager :public UIActor {

public:
	SceneChangeManager(IWorld& world);
	~SceneChangeManager();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
	//ブロックを埋める(true:ブロックで埋める,false:ブロックをはけさせる)
	void ChangeJudge(bool flag);
	float GetTime();
	//完全にブロックたちがはけているか
	bool GetNoBlockFlag();
	//完全にブロックたちが埋まっているか
	bool GetYesBlockFlag();
	//画像分割
	void SpriteSet(const SPRITE_ID& id);
private:
	//ブロックたち
	std::vector<UIActorPtr> mBlocks;
	//タイム
	float mTime;
	//タイムが1秒にになってからのカウント
	float mTimeCount;
	//埋めるかフラグ
	bool mFlag;
	//現在のSpriteID
	SPRITE_ID mNowId;
};