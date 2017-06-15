#include "Tutorial.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"

#include "../math/Math.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../game/Random.h"

#include "../actor/Stage.h"
#include "../actor/ParticleManager/ParticleManager.h"
#include "../actor/ID.h"
#include "../UIactor/GameTimer/GameTimerUI.h"
#include "../UIactor/GameFrameUI/GameFrameUI.h"
#include "../UIactor/ResultUI/ResultUI.h"
#include "../UIactor/GamePlayFontUI/GamePlayFontUI.h"


Tutorial::Tutorial():
	mIsEnd(false)
{
}

Tutorial::~Tutorial()
{
}

void Tutorial::Initialize()
{
	//フラグ初期化
	mIsEnd = false;


	wo.SetPlayerNum(mPlayerNum);

	//次もゲームプレイに移行
	mNextScene = Scene::GamePlay;
	//ステージを追加
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));

	//ゲームフレームを追加
	wo.UIAdd(UI_ID::GAMEFRAME_UI, std::make_shared<GameFrameUI>(wo, Vector2::Zero, mPlayerNum));
	auto font = std::make_shared<GamePlayFontUI>(wo);
	//フォントマネージャーを追加
	wo.UIAdd(UI_ID::FONT_UI, font);

	//プレイヤー操作不能
	wo.SetInputPlayer(false);
}

void Tutorial::Update()
{
}

void Tutorial::Draw()
{
}

bool Tutorial::IsEnd() const
{
	return false;
}

Scene Tutorial::Next() const
{
	return Scene();
}

void Tutorial::End()
{
}
