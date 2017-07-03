#include "Help.h"
#include "../UIactor/HelpUI/HelpUi.h"
#include "../input/Keyboard.h"
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

	wo.UIAdd(UI_ID::HELP_UI, std::make_shared<HelpUi>(wo));
}

void Help::Update()
{
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
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
}

bool Help::GetGameEndFlag()
{
	return false;
}
