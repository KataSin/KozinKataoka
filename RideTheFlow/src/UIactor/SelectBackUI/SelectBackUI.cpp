#include "SelectBackUI.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../UIactor/NumberTexture/NumberTexture.h"
SelectBackUI::SelectBackUI(IWorld & world) :
	UIActor(world),
	mLerpTimer(0.0f)
{
	//èâä˙âª
	parameter.isDead = false;
	mId = SPRITE_ID::UP_NINZU_SPRITE;
	mMove = BackUiMove::UIMOVE_STOP;
	parameter.position = Vector2(0, WINDOW_HEIGHT / 3);
	mScale = 1.5f;
	mNum = 1;
	Vector2 texSize = Sprite::GetInstance().GetSize(SPRITE_ID::UP_NINZU_SPRITE) / 2;
	//çsÇ´ï‚ä‘ÇÃê›íË
	mStartStartPos = parameter.position - Vector2(texSize.x*mScale, 0.0f);
	mStartEndPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
	//ãAÇËÇÃê›íË
	mEndStartPos = mStartEndPos;
	mEndEndPos = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT / 3) + Vector2(texSize.x, 0.0f);
}

SelectBackUI::~SelectBackUI()
{
}

void SelectBackUI::Update(PLAYER_NUMBER playerNumber)
{
	if (mMove == BackUiMove::UIMOVE_STOP) return;
	if (mMove == BackUiMove::UIMOVE_START) {
		parameter.position = Vector2::Lerp(mStartStartPos, mStartEndPos, mLerpTimer);
		mScale = Math::Lerp(1.5f, 1.0f, mLerpTimer);
	}
	else {
		parameter.position = Vector2::Lerp(mEndStartPos, mEndEndPos, mLerpTimer);
		mScale = Math::Lerp(1.0f, 0.5f, mLerpTimer);
	}


	mLerpTimer += 2.0f*Time::GetInstance().deltaTime();
	mLerpTimer = Math::Clamp(mLerpTimer, 0.0f, 1.0f);
}

void SelectBackUI::Draw() const
{
	if (mMove == BackUiMove::UIMOVE_STOP) return;
	Sprite::GetInstance().Draw(mId, parameter.position, Sprite::GetInstance().GetSize(mId) / 2, Vector2(mScale), true, false);
	NumberTexture num(SPRITE_ID::SUUZI_SPRITE, 32, 64);
	num.draw(parameter.position + Vector2(0, 32), mNum,Vector4(255,255,255,1));
}

void SelectBackUI::SetSpriteID(const SPRITE_ID & id)
{
	mId = id;
}

void SelectBackUI::SetMove(const BackUiMove & state)
{
	if (mMove == state)return;
	mMove = state;
	mLerpTimer = 0.0f;
}

void SelectBackUI::SetNumber(int num)
{
	mNum = num;
}
