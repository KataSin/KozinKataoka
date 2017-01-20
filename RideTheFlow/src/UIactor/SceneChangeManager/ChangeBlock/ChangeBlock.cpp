#include "ChangeBlock.h"
#include "../../../game/Random.h"
#include "../../../time/Time.h"
#include "../../../math/Math.h"
ChangeBlock::ChangeBlock(IWorld & world, const TexState& state) :
	UIActor(world),
	mPosition(state.randPos),
	mCurPosition(state.randPos),
	mToPositon(state.toPos),
	mAngle(state.randAngle),
	mCurAngle(state.randAngle),
	mToAngle(0.0f),
	mTime(0.0f),
	mDownFlag(false),
	mHandle(state.texHandle)
{
	mCenter = Sprite::GetInstance().GetSize(mHandle) / 2;
	parameter.isDead = false;
}

ChangeBlock::~ChangeBlock()
{
}

void ChangeBlock::Update(PLAYER_NUMBER playerNumber)
{
	mTime += 0.02f;
	mLeapTime = Math::Sin(Math::Lerp(0.0f, 90.0f, mTime));
	mPosition = Vector2::Lerp(mCurPosition, mToPositon, mLeapTime);

	mAngle = Math::Lerp(mCurAngle, mToAngle, mTime);

	mTime = Math::Clamp(mTime, 0.0f, 1.0f);

}

void ChangeBlock::Draw() const
{
	Sprite::GetInstance().Draw(mHandle, mPosition, mCenter, Vector2(1),mAngle, true,false);
}

void ChangeBlock::BlockDown()
{
	mDownFlag = true;
}
