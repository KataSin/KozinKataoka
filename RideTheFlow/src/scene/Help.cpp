#include "Help.h"
#include "../UIactor/HelpUI/HelpUi.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../sound/Sound.h"
#include "../graphic/Movie.h"
Help::Help()
{

}

Help::~Help()
{
}

void Help::Initialize()
{
	mIsEnd = false;
	mScene = Scene::Select;
	Movie::GetInstance().Load(MOVIE_ID::MACHINE_GUN_HELP, "res/Movie/HelpMachineGun.wmv");
	Movie::GetInstance().Load(MOVIE_ID::SHOT_GUN_HELP, "res/Movie/HelpShotGun.wmv");
	Movie::GetInstance().Load(MOVIE_ID::SNIPER_GUN_HELP, "res/Movie/HelpSniperGun.wmv");

	Sound::GetInstance().PlayBGM(BGM_ID::HELP_BGM, DX_PLAYTYPE_LOOP);
	wo.UIAdd(UI_ID::HELP_UI, std::make_shared<HelpUi>(wo));
}

void Help::Update()
{
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)||
		GamePad::GetInstance().AllTriggerDown()) {
		mIsEnd = true;
	}
}

void Help::Draw()
{
	wo.Draw();
	wo.UIDraw();
}

bool Help::IsEnd() const
{
	return mIsEnd;
}

Scene Help::Next() const
{
	return Scene::Title;
}

void Help::End()
{
	Movie::GetInstance().Clear();
	Sound::GetInstance().StopBGM();
}

bool Help::GetGameEndFlag()
{
	return false;
}
