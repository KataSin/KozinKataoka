#include "GameFrameUI.h"

GameFrameUI::GameFrameUI(IWorld& world, const Vector2& position, int playNum) :
	UIActor(world),
	mPosition(position),
	mPlayNum(playNum)
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
	//�v���C�l���ɂ���ăQ�[���t���[���e�N�X�`����ς���
	if (mPlayNum == 2)
		Sprite::GetInstance().Draw(SPRITE_ID::GAME_FRAME2_SPRITE, mPosition);
	else if (mPlayNum == 3)
		Sprite::GetInstance().Draw(SPRITE_ID::GAME_FRAME3_SPRITE, mPosition);
	else if (mPlayNum == 4)
		Sprite::GetInstance().Draw(SPRITE_ID::GAME_FRAME4_SPRITE, mPosition);
}
