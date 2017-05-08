#include "GameTimerUI.h"
#include "../NumberTexture/NumberTexture.h"
#include "../../time/Time.h"
GameTimerUI::GameTimerUI(IWorld & world, Vector2 position, float time):
	UIActor(world),
	mPosition(position),
	mGameTimer(time),
	mStopFlag(true)
{
	parameter.isDead = false;
}

GameTimerUI::~GameTimerUI()
{
}

void GameTimerUI::Update(PLAYER_NUMBER playerNumber)
{
	if(!mStopFlag)
	mGameTimer -= 1.0f/4.0f*Time::GetInstance().deltaTime();
}

void GameTimerUI::Draw() const
{
	NumberTexture num(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	num.draw(mPosition-Vector2(32,32), mGameTimer,Vector4(255, 0, 255, 1), 1.0f);
}
