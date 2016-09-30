#include "Content.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../Def.h"
#include "../math/Math.h"

// 画像を読み込む
void Content::LoadSprite(Sprite& sprite, Model& model)
{
	WorkFolder::SetWorkFolder("res/Sprite/");
	sprite.Load("blackscreen.png", SPRITE_ID::TARGET_SPRITE);

	sprite.Load("TargetUI.png", SPRITE_ID::TARGET_SPRITE);
	sprite.Load("SneperTargetUI.png", SPRITE_ID::SNEPER_SPRITE);

	/* フェード */
	//sprite.Load("blackscreen.png", SPRITE_ID::BLACK_SCREEN);

	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// ３Ｄモデルを読み込む
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("res/Model/");

	model.Load("player.mv1", MODEL_ID::PLAYER_MODEL, async);
	model.Load("SkyDemo/sky_dome_11.X", MODEL_ID::SKY_DEMO_MODEL, async);
	model.Load("DefaultPlate.mv1", MODEL_ID::DEFAULT_PLATE_MODEL, async);
	model.Load("playerBullet.mv1", MODEL_ID::PLAYER_BULLET_MODEL, async);
	model.Load("RespawnModel.mv1", MODEL_ID::RESPAWN_MODEL, async);
	model.Load("Tree/Tree.mv1", MODEL_ID::TREE_MODEL, async);
	model.Load("TestModel.mqo", MODEL_ID::TEST_MODEL, async);
	WorkFolder::SetWorkFolder("res/Model2D/");
}

// 音楽を読み込む
void Content::LoadSound(Sound& sound)
{
	WorkFolder::SetWorkFolder("res/Sound/GAME_BGM/");

	WorkFolder::SetWorkFolder("res/Sound/SE/");

	sound.SetAllBGMVolume(BGMVOLUME);
	sound.SetAllSEVolume(SEVOLUME);
}

void Content::EnableASync()
{
	SetUseASyncLoadFlag(TRUE);
}
void Content::DisableASync()
{
	SetUseASyncLoadFlag(FALSE);
}

template <typename T>
int Content::GetASyncLoadCount(T& content)
{
	return (content.GetCount() - GetASyncLoadNum() + 1);
}
template <>
int Content::GetASyncLoadCount(Sound& content)
{
	return ((content.GetCountBGM() + content.GetCountSE()) - GetASyncLoadNum() + 1);
}
int Content::GetASyncLoadAllCount(Model& model, Sprite& sprite, Sound& sound)
{
	auto count = model.GetCount() + sprite.GetCount() + sound.GetCountBGM() + sound.GetCountSE();
	return (count - GetASyncLoadNum() + 1);
}
bool Content::IsASync()
{
	return GetASyncLoadNum() > 0;
}