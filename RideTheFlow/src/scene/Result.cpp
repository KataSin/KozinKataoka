#include "Result.h"
#include "../input/Keyboard.h"
Result::Result(GameManager & gameManager):
	mGameManager(&gameManager),
	mIsEnd(false)
{
}

Result::~Result()
{
}

void Result::Initialize()
{
	mIsEnd = false;
}

void Result::Update()
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
		mIsEnd = true;
	}
}

void Result::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ƒŠƒUƒ‹ƒg");
	DrawFormatString(0, 64, GetColor(255, 255, 255), "Ÿ‚¿,%d",(int)(mGameManager->GetPlayerRank().front()));
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
