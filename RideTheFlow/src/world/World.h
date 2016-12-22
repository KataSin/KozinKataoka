#pragma once
#include "IWorld.h"
#include "WorldActor.h"
#include "../UIactor/UIActor.h"

class World :public IWorld {
public:
	World();
	~World();

	void Initialize();
	void Update();
	void UpdateUI(PLAYER_NUMBER player);
	void Draw() const;
	void UIDraw() const;
	void Clear();
	virtual void Add(ACTOR_ID id, ActorPtr actor);
	virtual void UIAdd(UI_ID id, UIActorPtr UIactor);
	virtual bool IsEnd() const;
	virtual void SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID);

	virtual int GetActorCount(ACTOR_ID id, ACTOR_ID id2);
	//子オブジェクトを巡回
	virtual void EachActor(ACTOR_ID id, std::function<void(const Actor&)> func) override;
	virtual void EachUIActor(UI_ID id, std::function<void(const UIActor&)> func) override;

	virtual ActorPtr GetPlayer(PLAYER_NUMBER playerNumber) override;
	virtual ActorPtr GetCamera(PLAYER_NUMBER playerNumber) override;

	virtual void SetCamera(PLAYER_NUMBER playerNumber)override;

	virtual std::vector<ActorPtr> GetActors(ACTOR_ID id) override;
	virtual std::vector<UIActorPtr> GetUIActors(UI_ID id)override;
private:
	WorldActor actors;
	ActorPtr   playerActor;
	std::vector<ActorPtr> cameraActor;
	std::vector<ActorPtr> masterCastles;

};