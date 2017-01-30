#include "World.h"
#include "../actor/ID.h"
#include "../actor/CameraActor.h"
World::World():
inputFlag(true){

}

World::~World(){
	Clear();
}

void World::Initialize(){
	Clear();
}
void World::Update(){
	actors.Update();
}
void World::UpdateUI(PLAYER_NUMBER playerNumber){
	actors.UpdateUI(playerNumber);
}
void World::Draw() const{
	actors.Draw();
}
void World::UIDraw() const
{
	actors.UIDraw();
}
void World::Clear(){
	actors.Clear();
	playerActor = nullptr;
	masterCastles.clear();
}

void World::Add(ACTOR_ID id, ActorPtr actor){
	actors.Add(id, actor);
}

void World::UIAdd(UI_ID id, UIActorPtr actor){
	actors.UIAdd(id, actor);
}

bool World::IsEnd()const{
	//とりあえず
	return false;
}

void World::SetCollideSelect(ActorPtr thisActor, ACTOR_ID otherID, COL_ID colID){
	actors.SetCollideSelect(thisActor, otherID, colID);
}

//子オブジェクトを巡回
void World::EachActor(ACTOR_ID id, std::function<void(const Actor&)> func)
{
	actors.EachActor(id, func);
}
void World::EachUIActor(UI_ID id, std::function<void(const UIActor&)> func)
{
	actors.EachUIActor(id, func);
}

ActorPtr World::GetPlayer(PLAYER_NUMBER playerNumber)
{
	return actors.GetPlayer(playerNumber);
}

ActorPtr World::GetCamera(PLAYER_NUMBER playerNumber)
{
   return actors.GetCamera(playerNumber);
}

void World::SetCamera(PLAYER_NUMBER playerNumber)
{
	//dynamic_cast<CameraActor*>(actors.GetCamera(playerNumber).get())->SetCamera();
}


std::vector<ActorPtr> World::GetActors(ACTOR_ID id)
{
	return actors.GetActors(id);
}
std::vector<UIActorPtr> World::GetUIActors(UI_ID id)
{
	return actors.GetUIActors(id);
}
void World::SetInputPlayer(bool flag)
{
	inputFlag = flag;
}
bool World::GetInputPlayer()
{
	return inputFlag;
}
int World::GetActorCount(ACTOR_ID id,ACTOR_ID id2)
{
	int count = actors.GetActorCount(id,id2);
	return count;
}