#include "ResultUI.h"
#include "../../Def.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
ResultUI::ResultUI(IWorld & world, GamePlayManager & gamePlayManager, PLAYER_NUMBER winPlayer) :
	UIActor(world),
	mAlpha(0.0f),
	mSize(1.5f),
	mTrophyAlpha(0.0f)
{
	parameter.isDead = false;
	//ここでリザルト処理＆勝った人を取る
	mWinPlayer = winPlayer;
	mWinCount = gamePlayManager.GetWinCount();
	mTexSize = Sprite::GetInstance().GetSize(SPRITE_ID::KEKKA_SPRITE);
	mTrophyAllPos = (Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2 - mTexSize / 2)+Vector2(128,96);
	mTrophyPos = Vector2(mWinCount[mWinPlayer] * 32, (int)mWinPlayer * 32)-Vector2(16,16);
}

ResultUI::~ResultUI()
{
}

void ResultUI::Update(PLAYER_NUMBER playerNumber)
{
	//結果のαを足してく
	mAlpha += Time::DeltaTime;
	//クランプ
	mAlpha = Math::Clamp(mAlpha, 0.0f, 1.0f);
	//結果が表示し終わったらトロフィーをあげる
	if (mAlpha >= 1.0f) {
		mTrophyAlpha += 0.3f*Time::DeltaTime;
		mSize = Math::Lerp(1.5f, 1.0f, mTrophyAlpha);
	}

}

void ResultUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::KEKKA_SPRITE, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2, mTexSize / 2, mAlpha, Vector2(mAlpha), true, false);
	//勝った人は後でトロフィーをあげるので勝ち数-1にしてある
	for (const auto& i : mWinCount) {
		int loop = i.second;
		if (i.first == mWinPlayer) loop--;
		for (int j = 0; j < loop; j++) {
			Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + Vector2(j * 32, ((int)i.first - 1) * 32));
		}
	}
	//あげるトロフィー表示
	Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + mTrophyPos,Vector2(16,16),mTrophyAlpha,Vector2(mSize),0,true,false);

}
