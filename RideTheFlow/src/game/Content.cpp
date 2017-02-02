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
	sprite.Load("suuzi.png", SPRITE_ID::SUUZI_SPRITE);

	sprite.Load("GaugeInUI.png", SPRITE_ID::ATTACK_GAUGE_IN_SPRITE);
	sprite.Load("GaugeOutUI.png", SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE);

	sprite.Load("GaugeOutUI.png", SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE);

	sprite.Load("machineGun.png", SPRITE_ID::MACHINE_UI_SPRITE);
	sprite.Load("shotGun.png", SPRITE_ID::SHOT_UI_SPRITE);
	sprite.Load("sniperUI.png", SPRITE_ID::SNEPER_UI_SPRITE);

	sprite.Load("Player/Player1.png", SPRITE_ID::PLAYER1_MODEL_SPRITE);
	sprite.Load("Player/Player2.png", SPRITE_ID::PLAYER2_MODEL_SPRITE);
	sprite.Load("Player/Player3.png", SPRITE_ID::PLAYER3_MODEL_SPRITE);
	sprite.Load("Player/Player4.png", SPRITE_ID::PLAYER4_MODEL_SPRITE);
	sprite.Load("GameFrame04.png", SPRITE_ID::GAME_FRAME4_SPRITE);
	sprite.Load("GameFrame03.png", SPRITE_ID::GAME_FRAME3_SPRITE);
	sprite.Load("GameFrame02.png", SPRITE_ID::GAME_FRAME2_SPRITE);

	sprite.Load("Kekka/Kekka1.png", SPRITE_ID::KEKKA1_SPRITE);
	sprite.Load("Kekka/Kekka2.png", SPRITE_ID::KEKKA2_SPRITE);
	sprite.Load("Kekka/Kekka3.png", SPRITE_ID::KEKKA3_SPRITE);
	sprite.Load("Kekka/Kekka4.png", SPRITE_ID::KEKKA4_SPRITE);
	
	sprite.Load("trophy.png", SPRITE_ID::TROPHY_SPRITE);

	sprite.Load("PlayerGanmen/Player1Egao.png", SPRITE_ID::PLAYER1_KAO_E);
	sprite.Load("PlayerGanmen/Player2Egao.png", SPRITE_ID::PLAYER2_KAO_E);
	sprite.Load("PlayerGanmen/Player3Egao.png", SPRITE_ID::PLAYER3_KAO_E);
	sprite.Load("PlayerGanmen/Player4Egao.png", SPRITE_ID::PLAYER4_KAO_E);
	sprite.Load("PlayerGanmen/Player1Magao.png", SPRITE_ID::PLAYER1_KAO_M);
	sprite.Load("PlayerGanmen/Player2Magao.png", SPRITE_ID::PLAYER2_KAO_M);
	sprite.Load("PlayerGanmen/Player3Magao.png", SPRITE_ID::PLAYER3_KAO_M);
	sprite.Load("PlayerGanmen/Player4Magao.png", SPRITE_ID::PLAYER4_KAO_M);

	sprite.Load("Font/sinda.png", SPRITE_ID::SINDA_SPRITE);
	sprite.Load("sinuyo.png", SPRITE_ID::SINUYO_SPRITE);
	sprite.Load("DamageBack.png", SPRITE_ID::DAMAGE_BACK_SPRITE);
	sprite.Load("SceneChangeBlock.png", SPRITE_ID::CHANGE_SCENE_PARTICLE_SPRITE);

	sprite.Load("Font/sokomade.png", SPRITE_ID::SOKOMADE_FONT_SPRITE);
	sprite.Load("Font/hikiwake.png", SPRITE_ID::HIKIWAKE_FONT_SPRITE);
	sprite.Load("Font/don.png", SPRITE_ID::DON_SPRITE);
	sprite.Load("Font/yo-i.png", SPRITE_ID::YO_I_FONT_SPRITE);
	sprite.Load("OverHert.png", SPRITE_ID::OVER_HERT_SPRITE);
	sprite.Load("OverHertFont.png", SPRITE_ID::OVER_HERT_FONT_SPRITE);

	sprite.Load("SelectSceneTexBack.png", SPRITE_ID::TEX_BACK_SPRITE);

	sprite.Load("SelectSceneTexBackUp.png", SPRITE_ID::TEX_BACK_UP_SPRITE);

	sprite.Load("test.png", SPRITE_ID::TEST_SPRITE);



	/* フェード */
	//sprite.Load("blackscreen.png", SPRITE_ID::BLACK_SCREEN);

	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// ３Ｄモデルを読み込む
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("res/Model/");

	model.Load("Player/Player1.mv1", MODEL_ID::PLAYER1_MODEL, async);
	model.Load("Player/Player2.mv1", MODEL_ID::PLAYER2_MODEL, async);
	model.Load("Player/Player3.mv1", MODEL_ID::PLAYER3_MODEL, async);
	model.Load("Player/Player4.mv1", MODEL_ID::PLAYER4_MODEL, async);

	model.Load("SkyDemo/sky_dome_11.X", MODEL_ID::SKY_DEMO_MODEL, async);
	model.Load("SkyDemo/sky_dome_11.X", MODEL_ID::SKY_DEMO_MODEL, async);
	model.Load("DefPlate/Plate.mv1", MODEL_ID::DEFAULT_PLATE_MODEL, async);
	model.Load("Bullet/playerBullet.mv1", MODEL_ID::PLAYER_BULLET_MODEL, async);
	model.Load("RespawnPoint/RespawnPoint01.mv1", MODEL_ID::RESPAWNPOINT01_MODEL, async);
	model.Load("RespawnPoint/RespawnPoint02.mv1", MODEL_ID::RESPAWNPOINT02_MODEL, async);
	model.Load("RespawnPoint/RespawnPoint03.mv1", MODEL_ID::RESPAWNPOINT03_MODEL, async);
	model.Load("RespawnPoint/RespawnPoint04.mv1", MODEL_ID::RESPAWNPOINT04_MODEL, async);
	model.Load("Tree/Tree.mv1", MODEL_ID::TREE_MODEL, async);
	model.Load("TestModel.mqo", MODEL_ID::TEST_MODEL, async);
	model.Load("Line/Line.mv1", MODEL_ID::LINE_MODEL, async);
	model.Load("Particle/Particle.mv1", MODEL_ID::PARTICLE_MODEL, async);
	model.Load("Stage/Stage01.mqo", MODEL_ID::STAGE01_MODEL, async);
	model.Load("Pool/Pool.mv1", MODEL_ID::POOL_MODEL, async);
	model.Load("NoBreakPlate/NoBreakPlate.mv1", MODEL_ID::NOBREAKPLATE_MODEL, async);

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

void Content::LoadShader()
{
	LoadPixelShader("res/Shader/vs.vso");
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