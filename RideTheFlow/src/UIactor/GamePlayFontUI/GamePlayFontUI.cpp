#include "GamePlayFontUI.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
GamePlayFontUI::GamePlayFontUI(IWorld & world) :
	UIActor(world)
{
	parameter.isDead = false;
	mFonts.clear();
}

GamePlayFontUI::~GamePlayFontUI()
{
}

void GamePlayFontUI::Update(PLAYER_NUMBER playerNumber)
{
	if (mFonts.empty()) return;
	for (auto& i : mFonts) {
		int num = 1;
		if (!i.second.mFlag) {
			if (i.second.mCount >= i.second.mFontTime) num = -1;
		}
		i.second.mAlpha += num*Time::GetInstance().deltaTime();
		i.second.mAlpha = Math::Clamp(i.second.mAlpha, 0.0f, 1.0f);

		i.second.mScale = i.second.mAlpha;
		i.second.mCount += Time::GetInstance().deltaTime();
		if (!i.second.mFlag) {
			if (i.second.mCount >= i.second.mFontTime+1.0f) {
				mFonts.erase(i.first);
				break;
			}
		}
	}
}

void GamePlayFontUI::Draw() const
{
	if (mFonts.size() == 0) return;
	for (const auto& i : mFonts) {
		Vector2 size = Sprite::GetInstance().GetSize(i.first);
		Sprite::GetInstance().Draw(i.first, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2, size / 2, i.second.mAlpha, Vector2(i.second.mScale), true, false);
	}
}

bool GamePlayFontUI::GetEndFont(const SPRITE_ID & font)
{
	if (mFonts.size() == 0) return true;

	if (mFonts.count(font) == 0)return true;
	return false;
}

void GamePlayFontUI::StartFont(const SPRITE_ID & font, float timer, bool flag)
{
	if (!GetEndFont(font)) return;
	mFonts[font].mAlpha = 0.0f;
	mFonts[font].mCount = 0.0f;
	mFonts[font].mScale = 0.0f;
	mFonts[font].mFontTime = timer;
	mFonts[font].mFlag = flag;
}
