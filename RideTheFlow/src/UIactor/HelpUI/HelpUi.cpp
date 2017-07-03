#include "HelpUi.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
HelpUi::HelpUi(IWorld & world):
UIActor(world)
{
	parameter.isDead = false;

	mResPagePos = Vector2(0.0f, 0.0f);

	mPagePos.push_back(Vector2::Zero);
	mPagePos.push_back(Vector2(1280.0f, 0.0f));

	mPage = 0;
}
HelpUi::~HelpUi()

{
}

void HelpUi::Update(PLAYER_NUMBER playerNumber)
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT) ||
		GamePad::GetInstance().POVTriggerDown() == 90) {
		mPage++;
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT) ||
		GamePad::GetInstance().POVTriggerDown() == 270) {
		mPage--;
	}

	mPage = Math::Clamp(mPage, 0, 1);

	mResPagePos = Vector2(1280.0f * -mPage, 0.0f);

	Vector2::Spring(mPagePos[0], mPageVelo, mResPagePos, 0.2f, 0.5f, 2.0f);

	mPagePos[1] += mPageVelo;


}

void HelpUi::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::HELP_1_SPRITE, mPagePos[0]);
	Sprite::GetInstance().Draw(SPRITE_ID::HELP_2_SPRITE, mPagePos[1]);
}
