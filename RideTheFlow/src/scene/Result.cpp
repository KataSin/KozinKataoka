#include "Result.h"
#include "../input/Keyboard.h"
#include "../camera/Camera.h"
#include "../graphic/Model.h"
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
	Vector3 testPos = Vector3(30, 0, 30);
	Camera::GetInstance().Position.Set(Vector3::Zero);
	Camera::GetInstance().Target.Set(testPos);

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
	Model::GetInstance().Draw(MODEL_ID::PLAYER1_MODEL, Vector3(30, 0, 30));
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
