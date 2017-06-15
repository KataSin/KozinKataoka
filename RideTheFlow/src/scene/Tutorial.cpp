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
	//�t���O������
	mIsEnd = false;


	wo.SetPlayerNum(mPlayerNum);

	//�����Q�[���v���C�Ɉڍs
	mNextScene = Scene::GamePlay;
	//�X�e�[�W��ǉ�
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));

	//�Q�[���t���[����ǉ�
	wo.UIAdd(UI_ID::GAMEFRAME_UI, std::make_shared<GameFrameUI>(wo, Vector2::Zero, mPlayerNum));
	auto font = std::make_shared<GamePlayFontUI>(wo);
	//�t�H���g�}�l�[�W���[��ǉ�
	wo.UIAdd(UI_ID::FONT_UI, font);

	//�v���C���[����s�\
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
