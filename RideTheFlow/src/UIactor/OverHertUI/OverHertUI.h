#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
class OverHertUI : public UIActor
{
public:
	OverHertUI(IWorld& world, const Vector2& position, Actor& manager);
	~OverHertUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//アタックマネージャー
	PlayerAttackManager* mAttackManager;
	//α値
	float mAlpha;
	//フォントα値
	float mFontAlpha;
	//α値用カウント
	float mAlphaCount;
	//テクスチャサイズ
	Vector2 mTexSize;
};