#include "WorldActor.h"
#include<algorithm>
#include "../actor/ID.h"
#include <algorithm>
#include "../actor/Actor.h"
#include "../actor/ActorPtr.h"

WorldActor::WorldActor(){
	for (int i = ACTOR_ID::BEGIN_ACTOR; i <= ACTOR_ID::END_ACTOR; ++i)
		managers.emplace(ACTOR_ID(i), std::make_shared<ActorManager>());
	for (int i = UI_ID::BEGIN_UI; i <= UI_ID::END_UI; ++i)
		UImanagers.emplace(UI_ID(i), std::make_shared<UIActorManager>());
}
WorldActor::~WorldActor(){

}
void WorldActor::Update(){
	//�S�L�����A�b�v�f�[�g
	std::for_each(managers.begin(), managers.end(),
		[&](ActorManagerPair pair){pair.second->Update(); });
	//�����蔻��
	for (auto& cols : colselect){
		for (auto& sec : cols.second){
			managers[sec.otherID]->Collide(sec.colID, *cols.first);
		}
	}

	colselect.clear();
	//����ł���̂�����
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Remove(); });
}
void WorldActor::UpdateUI(PLAYER_NUMBER playerNumber)
{
	//�S�G�t�F�N�g�A�b�v�f�[�g
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[&](UIActorManagerPair UIpair) {UIpair.second->Update(playerNumber); });

	std::for_each(UImanagers.begin(), UImanagers.end(),
		[](UIActorManagerPair UIpair) {UIpair.second->Remove(); });
}
void WorldActor::Draw() const{

	//�S�L�����`��
	std::for_each(managers.begin(), managers.end(),
		[&](ActorManagerPair pair){pair.second->Draw(); });

	//�S�G�t�F�N�g�`��
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[&](UIActorManagerPair UIpair){UIpair.second->Draw(); });
}
void WorldActor::Add(ACTOR_ID id, ActorPtr actor){
	managers[id]->Add(actor);
}

void WorldActor::UIAdd(UI_ID id, UIActorPtr UIactor){
	UImanagers[id]->Add(UIactor);
}
void WorldActor::Clear(){
	//�S�L�����N���A
	std::for_each(managers.begin(), managers.end(),
		[](ActorManagerPair pair){pair.second->Clear(); });
	//�S�G�t�F�N�g�N���A
	std::for_each(UImanagers.begin(), UImanagers.end(),
		[](UIActorManagerPair UIpair){UIpair.second->Clear(); });

	colselect.clear();
}

void WorldActor::SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID){
	CollideSelect c = { otherID, colID };
	colselect[thisActor].push_back(c);
}

//�q������
void WorldActor::EachActor(ACTOR_ID id, std::function<void(const Actor&)> func)
{
	managers[id]->EachActor(func);
}
void WorldActor::EachUIActor(UI_ID id, std::function<void(const UIActor&)> func)
{
	UImanagers[id]->EachActor(func);
}
int WorldActor::GetActorCount(ACTOR_ID id, ACTOR_ID id2)
{
	int count = 0;
	if (managers[id]->getlist().size() < 1)return 0;

	for (auto i : managers[id]->getlist()){
		if (i->GetParameter().id ==id2 )
			count++;
	}
	return count;
}
ActorPtr WorldActor::GetPlayer(PLAYER_NUMBER playerNumber)
{
	for (auto i : managers[ACTOR_ID::PLAYER_ACTOR]->getlist())
	{
		PLAYER_NUMBER num = i->GetParameter().playNumber;
		if (i->GetParameter().playNumber == playerNumber)
		{
			return i;
		}
	}
	//������Ȃ�������null
	return nullptr;
}
ActorPtr WorldActor::GetCamera(PLAYER_NUMBER playerNumber)
{
	for (auto i : managers[ACTOR_ID::CAMERA_ACTOR]->getlist())
	{
		PLAYER_NUMBER num = i->GetParameter().playNumber;
		if (i->GetParameter().playNumber == playerNumber)
		{
			return i;
		}
	}
	//������Ȃ�������null
	return nullptr;
}
std::vector<ActorPtr> WorldActor::GetActors(ACTOR_ID id)
{
	std::vector<ActorPtr> masters;
	if (managers[id]->getlist().size() < 1)return masters;

	for (auto i : managers[id]->getlist())
	{
		masters.push_back(i);
	}
	return masters;
}

std::vector<UIActorPtr> WorldActor::GetUIActors(UI_ID id)
{
	std::vector<UIActorPtr> masters;
	if (UImanagers[id]->getlist().size() < 1)return masters;

	for (auto i : UImanagers[id]->getlist())
	{
		masters.push_back(i);
	}
	return masters;
}
