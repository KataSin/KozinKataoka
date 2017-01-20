#include "Pool.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
#include "../Player.h"
#include "../StageLineManager/StageLine/StageLine.h"
Pool::Pool(IWorld & world, Vector3& Pos1, Vector3& Pos2) :
	Actor(world),
	mPos1(Pos1),
	mPos2(Pos2),
	mTimer(0.0f)
{
	parameter.isDead = false;
	mPos1 = Pos1;
	mPos2 = Pos2;
}

Pool::~Pool()
{
}

void Pool::Update()
{
	mLinePosition = mPos1+(mPos2-mPos1)/2.0f;

	Matrix4 lineMat;
	lineMat =
		Matrix4::Scale(Vector3(Vector3::Distance(mPos1,mPos2), 1.0f, 1.0f))*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(Vector3::GetAngle2D(mPos1,mPos2))*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(mLinePosition);

	mTimer += Time::DeltaTime;
	if (mTimer >= 1.0f) {
		Line line;
		//LineÇê›íË
		line.startPos = mPos1;
		line.endPos = mPos2;
		world.Add(ACTOR_ID::STAGELINE_ACTOR, std::make_shared<StageLine>(world, lineMat,line));
		mTimer = 0.0f;
	}
}

void Pool::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::POOL_MODEL, mPos1);
	Model::GetInstance().Draw(MODEL_ID::POOL_MODEL, mPos2);
}

void Pool::OnCollide(Actor & other, CollisionParameter colpara)
{

}
