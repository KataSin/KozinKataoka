#include "GameTimerUI.h"
#include "../NumberTexture/NumberTexture.h"
#include "../../time/Time.h"
GameTimerUI::GameTimerUI(IWorld & world, Vector2 position, float time):
	UIActor(world),
	mPosition(position),
	mGameTimer(time)
{
	parameter.isDead = false;
}

GameTimerUI::~GameTimerUI()
{
}

void GameTimerUI::Update(PLAYER_NUMBER playerNumber)
{
	mGameTimer -= Time::DeltaTime;
}

void GameTimerUI::Draw() const
{
	NumberTexture num(SPRITE_ID::SUUZI_SPRITE, 12, 24);
	num.draw(mPosition, mGameTimer,Vector4(255, 0, 255, 1), 2.0f);
}
