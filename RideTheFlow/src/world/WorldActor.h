#pragma once
#include "../actor/ActorPtr.h"
#include "../actor/ActorManager.h"
#include "../UIactor/UIActorPtr.h"
#include "../UIactor/UIActorManager.h"
#include <map>
#include <vector>
#include "../actor/ID.h"

enum ACTOR_ID;
enum UI_ID;

struct CollideSelect{
	ACTOR_ID otherID;
	COL_ID colID;
};

class WorldActor{
public:
	WorldActor();
	~WorldActor();
	void Update();
	void UpdateUI(PLAYER_NUMBER playerNumber);
	void Draw() const;
	void Add(ACTOR_ID id, ActorPtr actor);
	void UIAdd(UI_ID id, UIActorPtr UIactor);
	void Clear();
	void SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID);
	int GetActorCount(ACTOR_ID id,ACTOR_ID id2);
	ActorPtr GetPlayer(PLAYER_NUMBER playerNumber);
	ActorPtr GetCamera(PLAYER_NUMBER playerNumber);
	//�q�I�u�W�F�N�g������
	void EachActor(ACTOR_ID id, std::function<void(const Actor&)> func);
	void EachUIActor(UI_ID id, std::function<void(const UIActor&)> func);

	std::vector<ActorPtr> GetActors(ACTOR_ID id);
	std::vector<UIActorPtr> GetUIActors(UI_ID id);


private:
	typedef std::shared_ptr<ActorManager> ActorManagerPtr;
	typedef std::map<ACTOR_ID, ActorManagerPtr> ActorManagerPtrMap;
	typedef std::pair<ACTOR_ID, ActorManagerPtr> ActorManagerPair;
	ActorManagerPtrMap managers;
	std::map<ActorPtr, std::vector<CollideSelect>> colselect;

	typedef std::shared_ptr<UIActorManager> UIActorManagerPtr;
	typedef std::map<UI_ID, UIActorManagerPtr> UIActorManagerPtrMap;
	typedef std::pair<UI_ID, UIActorManagerPtr> UIActorManagerPair;
	UIActorManagerPtrMap UImanagers;

};