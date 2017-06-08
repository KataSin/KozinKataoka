#include "ChangeBlock.h"
#include "../../../game/Random.h"
#include "../../../time/Time.h"
#include "../../../math/Math.h"
#include "../SceneChangeManager.h"
ChangeBlock::ChangeBlock(IWorld & world, const TexState& state,UIActor& manager) :
	UIActor(world),
	mPosition(state.randPos),
	mCurPosition(state.randPos),
	mToPositon(state.toPos),
	mAngle(state.randAngle),
	mCurAngle(state.randAngle),
	mToAngle(0.0f),
	mTime(0.0f),
	mHandle(state.texHandle),
	mManager(&manager)
{
	mCenter = Sprite::GetInstance().GetSize(mHandle) / 2;
	parameter.isDead = false;
}

ChangeBlock::~ChangeBlock()
{
}

void ChangeBlock::Update(PLAYER_NUMBER playerNumber)
{
	//ê¸å`ï€ä«Ç≈ìÆÇ©Ç∑
	mTime = static_cast<SceneChangeManager*>(mManager)->GetTime();
	mLeapTime = Math::Sin(Math::Lerp(0.0f, 90.0f, mTime));
	mPosition = Vector2::Lerp(mCurPosition, mToPositon, mLeapTime);
	mAngle = Math::Lerp(mCurAngle, mToAngle, mTime);

}

void ChangeBlock::Draw() const
{
	Sprite::GetInstance().Draw(mHandle, mPosition, mCenter, Vector2(1), mAngle, true, false);
}

void ChangeBlock::Dead()
{
	parameter.isDead = true;
}
