#include "UIActorManager.h"
#include "UIActor.h"
#include<algorithm>
#include "../actor/ID.h"
UIActorManager::UIActorManager(){

}

UIActorManager::~UIActorManager(){

}

void UIActorManager::Update(PLAYER_NUMBER playerNumber){
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[&](UIActorPtr actor){ actor->Update(playerNumber); });
}

void UIActorManager::Draw() const{
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[](UIActorPtr actor){
		actor->Draw();
	});
}

void UIActorManager::Add(UIActorPtr actor){
	actorPtr.push_back(actor);
}

void UIActorManager::Clear(){
	actorPtr.clear();
}
void UIActorManager::Remove(){
	actorPtr.remove_if([](UIActorPtr actor){return actor->IsDead(); });
}

std::list<UIActorPtr> UIActorManager::getlist()
{
	return actorPtr;
}

//q‚ğ„‰ñ
void UIActorManager::EachActor(std::function<void(UIActor&)> func)
{
	std::for_each(actorPtr.begin(), actorPtr.end(),
		[&](const UIActorPtr& actor) {func(*actor); });
}