#include "GameMasterUI.h"
#include "../../../graphic/Sprite.h"
GameMasterUI::GameMasterUI(IWorld & world) :
	UIActor(world)
{
	parameter.isDead = false;

	//テクスチャを設定
	Vector2 size = Sprite::GetInstance().GetSize(SPRITE_ID::TEX_BACK_SPRITE);
	mTexBack.spriteID = SPRITE_ID::TEX_BACK_SPRITE;
	mTexBack.spriteSize = size;
	mTexBack.position = Vector2(WINDOW_WIDTH / 2.0f, size.y / 2.0f);

	Vector2 sizeUp = Sprite::GetInstance().GetSize(SPRITE_ID::TEX_BACK_UP_SPRITE);
	mTexBackUp.spriteID = SPRITE_ID::TEX_BACK_UP_SPRITE;
	mTexBackUp.spriteSize = sizeUp;
	mTexBackUp.position = Vector2(WINDOW_WIDTH - sizeUp.x / 2, WINDOW_HEIGHT - size.y / 2.0f);
}

GameMasterUI::~GameMasterUI()
{
}

void GameMasterUI::Update(PLAYER_NUMBER playerNumber)
{
}

void GameMasterUI::Draw() const
{
	//テキストの後ろの画像を表示
	Sprite::GetInstance().Draw(SPRITE_ID::TEX_BACK_SPRITE,mTexBack.position,Vector4(255,255,255,1),mTexBack.spriteSize/2,1.0f,Vector2(1),0);
	Sprite::GetInstance().Draw(SPRITE_ID::TEX_BACK_UP_SPRITE, mTexBackUp.position, Vector4(255, 255, 255, 1), mTexBackUp.spriteSize / 2, 1.0f, Vector2(1), 0);
}
