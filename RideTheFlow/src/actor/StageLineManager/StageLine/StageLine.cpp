#include "StageLine.h"
#include "../../../world/IWorld.h"

#include "../../../math/Math.h"
#include "../../../time/Time.h"

#include "../../../input/GamePad.h"
#include "../../../input/Keyboard.h"
#include "../../../graphic/Model.h"
#include "../../Collision.h"
#include "../../../sound/Sound.h"
StageLine::StageLine(IWorld & world, Matrix4& mat, Line& line) :
	Actor(world),
	mAlpha(1.0f),
	mAlphaTimer(0.0f),
	mDeadTimer(0.0f),
	mPosition(mat.GetPosition()),
	mLine(line)
{
	parameter.mat = mat;
	mRotateY = mat.GetRotate().y;
	parameter.isDead = false;
}

StageLine::~StageLine()
{
}

void StageLine::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_STAGELINE_COL);

	mPosition.y += 4.0f * Time::GetInstance().deltaTime();
	mAlphaTimer += Time::GetInstance().deltaTime();
	if (mAlphaTimer >= 1.8f) {
		mAlpha -= 1.0f*Time::GetInstance().deltaTime();
		//透明になったら死ぬ
		if (mAlpha <= 0.0f)
			parameter.isDead = true;
	}
	//Lineを更新
	mLine.startPos.y = mPosition.y;
	mLine.endPos.y = mPosition.y;
	parameter.mat.SetPosition(mPosition);
}

void StageLine::Draw() const
{
	//ライトの影響を受けない
	SetLightEnable(false);
	Model::GetInstance().Draw(MODEL_ID::LINE_MODEL, parameter.mat, mAlpha, Vector4(255, 0, 0, 1));
	SetLightEnable(true);
}

void StageLine::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::PLAYER_STAGELINE_COL&&!other.GetParameter().isRespawn) {
		Sound::GetInstance().PlaySE(SE_ID::PLAYER_STAGE_OUT_SE, DX_PLAYTYPE_BACK);
	}
}
