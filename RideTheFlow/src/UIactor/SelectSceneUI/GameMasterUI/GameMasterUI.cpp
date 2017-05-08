#include "GameMasterUI.h"
#include "../../../graphic/Sprite.h"
#include "../../../Text/MessageBox/MessageText.h"
#include "../../../input/Keyboard.h"
#include "../../../graphic/AnimetionClass.h"
GameMasterUI::GameMasterUI(IWorld & world) :
	UIActor(world)
{
	parameter.isDead = false;
	//メッセージ
	mMessageText = new MessageText(world, Vector2::Zero, TEXT_FILE_ID::GAMEMASTER_TXT);
	mMessageCount = 0;
	mTextBackSize = Sprite::GetInstance().GetSize(SPRITE_ID::TEX_BACK_SPRITE);
	mTextBackPos = Vector2(WINDOW_WIDTH - mTextBackSize.x, WINDOW_HEIGHT - mTextBackSize.y);
	//mGameMasterAnim = new AnimetionClass();
}

GameMasterUI::~GameMasterUI()
{
}

void GameMasterUI::Update(PLAYER_NUMBER playerNumber)
{
	mMessageText->update();
}

void GameMasterUI::Draw() const
{
	//テキストの後ろの画像を表示
	Sprite::GetInstance().Draw(SPRITE_ID::TEX_BACK_SPRITE,mTextBackPos);
	mMessageText->draw(mTextBackPos+Vector2(96,48));
}

void GameMasterUI::SetMasterText(int num)
{
	mMessageText->SetTextCount(num);
}

int GameMasterUI::GetMasterText()
{
	return mMessageText->GetTextCount();
}
