#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
#include <map>
#include "../../actor/ID.h"
class GamePlayFontUI : public UIActor
{
	struct FontState
	{
		//α値
		float mAlpha=0.0f;
		//サイズ
		float mScale=0.0f;
		//カウント
		float mCount=0.0f;
		//どのぐらい表示させるか
		float mFontTime = 0.0f;
		//ずっと表示するかどうか
		bool mFlag=false;
	};
public:
	GamePlayFontUI(IWorld& world);
	~GamePlayFontUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

public:

	//フォントが表示し終わったかを取得
	bool GetEndFont(const SPRITE_ID& font);
	//フォントの再生をスタート
	void StartFont(const SPRITE_ID& font,float timer=15.0f, bool flag=false);
private:
	//フォントmap
	std::map<SPRITE_ID, FontState> mFonts;

};