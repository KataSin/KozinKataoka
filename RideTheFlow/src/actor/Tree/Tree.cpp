#include "Tree.h"
#include "../../math/Vector3.h"
#include "../Collision.h"
#include "../../world/IWorld.h"
#include "../ID.h"
#include "../../math/Math.h"
#include "../../math/Quaternion.h"
#include "../../game/Random.h"
#include "../../time/Time.h"
#include "../../graphic/Model.h"
Tree::Tree(IWorld & world, Vector3 position) :
	Actor(world),
	downMat(Matrix4::Identity),
	downSeveMat(Matrix4::Identity),
	mPosition(position),
	mVec(Vector3::Zero),
	mRotate(Vector3::Zero),
	isColPos(Vector3::Zero),
	downFlag(false),
	downVelo(0.0f),
	count(0.0f),
	alpha(1.0f)
{
	//パラメーター初期化
	parameter.isDead = false;
	parameter.playNumber = PLAYER_NUMBER::PLAYER_NULL;
	parameter.height = 20.0f;
	parameter.HP = 10;
	parameter.radius = 4.0f;
	parameter.mat =
		Matrix4::Scale(1.0f)*
		Matrix4::RotateX(0.0f)*
		Matrix4::RotateY(0.0f)*
		Matrix4::RotateZ(0.0f)*
		Matrix4::Translate(position);
}

Tree::~Tree()
{
}

void Tree::Update()
{
	//あたり判定
	if (parameter.HP > 0)
	{
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_BULLET_ACTOR, COL_ID::BULLET_TREE_COL);
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_TREE_COL);
		//パラメーター更新
		parameter.mat =
			Matrix4::Scale(1.0f)*
			Matrix4::RotateX(0.0f)*
			Matrix4::RotateY(0.0f)*
			Matrix4::RotateZ(0.0f)*
			Matrix4::Translate(mPosition);
	}
	else
	{
		//world.SetCollideSelect(shared_from_this(), ACTOR_ID::PLAYER_ACTOR, COL_ID::PLAYER_TREE_COL);
		if (!downFlag)
		{
			//弾が当たった場所から木が倒れる場所のマトリクスを生成
			Vector3 frontVec, leftVec, UpVec;
			UpVec = ((parameter.mat.GetPosition() - isColPos)*Vector3(1, 0, 1)).Normalized();
			frontVec = Vector3::Cross(UpVec, Vector3::Left).Normalized();
			leftVec = Vector3::Cross(frontVec, UpVec).Normalized();
			downMat.SetFront(frontVec);
			downMat.SetLeft(leftVec);
			downMat.SetUp(UpVec);
			downMat.SetPosition(mPosition);

			downFlag = true;
			//マトリックスを保存
			downSeveMat = parameter.mat;
		}
		downVelo += 0.01f*Time::DeltaTime;
		count += downVelo;
	    count = Math::Clamp(count, 0.0f, 1.0f);
		parameter.mat = Matrix4::Slerp(downSeveMat, downMat, count);

		if (count >= 1.0f)
			alpha -= 0.5f*Time::DeltaTime;
	}
}

void Tree::Draw() const
{
	Model::GetInstance().Draw(MODEL_ID::TREE_MODEL, parameter.mat,alpha);
	DrawCapsule3D(Vector3::ToVECTOR(parameter.mat.GetPosition()),
		Vector3::ToVECTOR(parameter.mat.GetPosition() + (parameter.mat.GetUp().Normalized()*parameter.height)),
		parameter.radius, 20, 1, 1, FALSE);
	DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetPosition() + (parameter.mat.GetUp().Normalized()*parameter.height)),
		parameter.radius * 2.0f, 10, 1, 1, FALSE);
}

void Tree::OnCollide(Actor & other, CollisionParameter colpara)
{
	if (colpara.colID == COL_ID::BULLET_TREE_COL)
	{
		isColPos = colpara.colPos;
		parameter.HP--;
	}
}
