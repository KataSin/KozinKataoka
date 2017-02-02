#pragma once
#include "../actor/ActorPtr.h"
#include "../UIactor/UIActorPtr.h"
#include <functional>
#include <vector>
#include "../actor/ID.h"
enum ACTOR_ID;
enum COL_ID;
enum UI_ID;

class IWorld{
public:
	virtual ~IWorld(){}
	virtual void Add(ACTOR_ID id, ActorPtr actor) = 0;
	virtual void UIAdd(UI_ID id, UIActorPtr UIactor) = 0;
	virtual bool IsEnd()const = 0;
	virtual void SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID) = 0;

	virtual int GetActorCount(ACTOR_ID id,ACTOR_ID id2)=0 ;

	//子オブジェクトを巡回
	virtual void EachActor(ACTOR_ID id, std::function<void(const Actor&)> func) = 0;
	virtual void EachUIActor(UI_ID id, std::function<void(const UIActor&)> func) = 0;

	virtual ActorPtr GetPlayer(PLAYER_NUMBER playerNumber) = 0;
	virtual ActorPtr GetCamera(PLAYER_NUMBER playerNumber) = 0;

	virtual void SetCamera(PLAYER_NUMBER playerNumber)= 0;

	//プレイする人の数を取得
	virtual int GetPlayerNum()=0;
	//プレイする人の数を設定
	virtual void SetPlayerNum(int num) = 0;

	//入力を受け付けるかどうかtrue:受け付ける
	virtual void SetInputPlayer(bool flag)=0;
	//操作できるかどうか
	virtual bool GetInputPlayer() = 0;

	virtual std::vector<ActorPtr> GetActors(ACTOR_ID id)= 0;

	virtual std::vector<UIActorPtr> GetUIActors(UI_ID id) = 0;
};