#include "Result.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../UIactor/EndResultUI/EndResult.h"
Result::Result(GameManager & gameManager) :
	mGameManager(&gameManager),
	mIsEnd(false)
{


}

Result::~Result()
{
}

void Result::Initialize()
{
	mResultUi = std::make_shared<EndResultUI>(wo, *mGameManager);
	wo.UIAdd(UI_ID::END_RESULT_UI, mResultUi);
	mIsEnd = false;
}

void Result::Update()
{
	if (static_cast<EndResultUI*>(mResultUi.get())->GetIsEnd() &&
		(GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) ||
		GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))) {
		mIsEnd = true;
	}
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

}

void Result::Draw()
{
	wo.Draw();
	wo.UIDraw();
}

bool Result::IsEnd() const
{
	return mIsEnd;
}
Scene Result::Next() const
{
	return Scene::Title;
}

void Result::End()
{
	mGameManager->Initialize();
}
