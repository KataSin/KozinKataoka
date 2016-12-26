#include "GameFrameUI.h"

GameFrameUI::GameFrameUI(IWorld & world, const Vector2 & position):
	UIActor(world),
	mPosition(position)
{
	parameter.isDead = false;
}

GameFrameUI::~GameFrameUI()
{
}

void GameFrameUI::Update(PLAYER_NUMBER playerNumber)
{
}

void GameFrameUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::GAME_FRAME_SPRITE, mPosition);
}
