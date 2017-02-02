#pragma once
#include "../../UIActor.h"
#include <vector>

class GameMasterUI : public UIActor
{
	struct SpriteState
	{
		SPRITE_ID spriteID;
		Vector2 spriteSize;
		Vector2 position;
	};
public:
	GameMasterUI(IWorld& world);
	~GameMasterUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//ポジション
	Vector2 mPosition;
	//テキストの情報
	std::vector<SpriteState> mTexs;
	//どのぐらいテキストが決まったか
	int texNum;
	//テキストマックスサイズ
	int texMaxSize;

	SpriteState mTexBackUp;
	SpriteState mTexBack;
};
