#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include"../world/IWorld.h"
#include "RespawnPoint.h"
#include "Tree\Tree.h"
#include "Pool\Pool.h"
#include "../actor/StagePlate/NoBreakPlate.h"
static const int MODEL_SIZE = 240;

Stage::Stage(IWorld& world) :
	Actor(world),
	skyMat(Matrix4::Identity) {
	parameter.isDead = false;

	skyMat =
		Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);
	//デフォルトパネルの設置
	for (int x = 1; x <= 11; x++)
	{
		for (int y = 1; y <= 11; y++)
		{

			if ((x == 1 && y == 1 )||
				(x == 1 && y == 11) ||
				(x == 11 && y == 1) ||
				(x == 11 && y == 11)) {
				world.Add(ACTOR_ID::PLATE_ACTOR, std::make_shared<NoBreakPlate>(world,
					Vector3(20.0f*x, 0.0f, 20.0f*y)));
			}
			else
			world.Add(ACTOR_ID::PLATE_ACTOR, std::make_shared<DefaultPlate>(world,
				Vector3(20.0f*x, 0.0f, 20.0f*y)));

			//中心に
			if (y == 5 && x == 5)
				mStagePos = Vector3(20.0f*x, 0.0f, 20.0f*y + 40.0f) - Vector3(0, 330, 0);
		}
	}
	//プレイヤーがスポーンするポイントを生成
	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f*1, 1.5f, 20.0f*1),
		225.0f,
		PLAYER_NUMBER::PLAYER_1));

	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f*11, 1.5f, 20.0f*1),
		135.0f,
		PLAYER_NUMBER::PLAYER_2));

	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f*11, 1.5f, 20.0f*11),
		45.0f,
		PLAYER_NUMBER::PLAYER_3));

	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f*2, 1.5f, 20.0f*2),
		315.0f,
		PLAYER_NUMBER::PLAYER_4));

	//ポールの追加
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20, 0, 20) + Vector3(-10, 0, -10), Vector3(20 * 11, 0, 20) + Vector3(10, 0, -10)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20 * 11, 0, 20) - Vector3(-10, 0, 10), Vector3(20 * 11, 0, 20 * 11) + Vector3(10, 0, 10)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20 * 11, 0, 20 * 11) + Vector3(10, 0, 10), Vector3(20, 0, 20 * 11) + Vector3(-10, 0, 10)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20, 0, 20 * 11) + Vector3(-10, 0, 10), Vector3(20, 0, 20) + Vector3(-10, 0, -10)));

	//木の追加
	world.Add(ACTOR_ID::TREE_ACTOR, std::make_shared<Tree>(world,
		Vector3(100, 0, 100)));
}
Stage::~Stage() {
	parent = nullptr;
}

void Stage::Update() {
}
void Stage::Draw() const {
	//ステージの描写
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, skyMat);
	Matrix4 mat;
	mat = Matrix4::Scale(5.0f)*
		Matrix4::Translate(mStagePos);
	Model::GetInstance().Draw(MODEL_ID::STAGE01_MODEL, mat);
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara) {

}