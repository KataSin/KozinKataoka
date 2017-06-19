#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include"../world/IWorld.h"
#include "RespawnPoint.h"
#include "Tree\Tree.h"
#include "Pool\Pool.h"
#include "../actor/StagePlate/NoBreakPlate.h"
#include "../actor/AnimActor/AnimActor.h"
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

			if ((x == 1 && y == 1) ||
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


	//ポールの追加
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20, 0, 20) + Vector3(-15, 0, -15), Vector3(20 * 11, 0, 20) + Vector3(15, 0, -15)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20 * 11, 0, 20) - Vector3(-15, 0, 15), Vector3(20 * 11, 0, 20 * 11) + Vector3(15, 0, 15)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20 * 11, 0, 20 * 11) + Vector3(15, 0, 15), Vector3(20, 0, 20 * 11) + Vector3(-15, 0, 15)));
	world.Add(ACTOR_ID::POOL_ACTOR, std::make_shared<Pool>(world, Vector3(20, 0, 20 * 11) + Vector3(-15, 0, 15), Vector3(20, 0, 20) + Vector3(-15, 0, -15)));

	//観客の追加
	SetKankyaku();
	for (const auto& i : mKankyakuMats)
	{
		world.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<AnimActor>(world, i.mat, i.modelId, i.animId));
	}



	//プレイヤーがスポーンするポイントを生成
	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f * 1, 1.5f, 20.0f * 1),
		225.0f,
		PLAYER_NUMBER::PLAYER_1));

	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f * 11, 1.5f, 20.0f * 1),
		135.0f,
		PLAYER_NUMBER::PLAYER_2));
	if (world.GetPlayerNum() == 2) return;
	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f * 11, 1.5f, 20.0f * 11),
		45.0f,
		PLAYER_NUMBER::PLAYER_3));
	if (world.GetPlayerNum() == 3) return;
	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(20.0f * 1, 1.5f, 20.0f * 11),
		315.0f,
		PLAYER_NUMBER::PLAYER_4));



	////木の追加
	//world.Add(ACTOR_ID::TREE_ACTOR, std::make_shared<Tree>(world,
	//	Vector3(100, 0, 100)));
}
Stage::~Stage() {
	parent = nullptr;
}

void Stage::Update() {
}
void Stage::Draw() const {
	//ステージの描写
	SetLightEnable(false);
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, skyMat);
	SetLightEnable(true);
	Matrix4 mat;
	mat = Matrix4::Scale(5.0f)*
		Matrix4::Translate(mStagePos);
	Model::GetInstance().Draw(MODEL_ID::STAGE01_MODEL, mat);
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara) {

}

void Stage::SetKankyaku()
{
	//一人目
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(-90)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(-90, 5, 240));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_MIRU_1_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_1_MODEL;
		mKankyakuMats.push_back(state);
	}
	//二人目
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(-90)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(-30, -5, -30));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_MIRU_2_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_2_MODEL;
		mKankyakuMats.push_back(state);
	}

	//三人目
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(0)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(70.0f, 4.5f, 365.0f));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_OUEN_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_5_MODEL;
		mKankyakuMats.push_back(state);
	}
	//四人目
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(90)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(265.0f, -1.5f, 153.0f));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_HAND_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_3_MODEL;
		mKankyakuMats.push_back(state);
	}
	//五人目
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(180)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(200.0f, -0.5f, -95.0f));
		state.mat = mat;
		state.animId = ANIMATION::KANKYAKU_MIRU_1_ANIM;
		state.modelId = MODEL_ID::KANKYAKU_4_MODEL;
		mKankyakuMats.push_back(state);
	}
	//ゲームマスター
	{
		Matrix4 mat;
		KankyakuState state;
		mat =
			Matrix4::Scale(0.4f)*
			Matrix4::RotateX(0)*
			Matrix4::RotateY(180-45)*
			Matrix4::RotateZ(0)*
			Matrix4::Translate(Vector3(410.0f, 120.0f, -165.0f));
		state.mat = mat;
		state.animId = ANIMATION::GAMEMASTER_DNACE_1_ANIM;
		state.modelId = MODEL_ID::GAME_MASTER_MODEL;
		mKankyakuMats.push_back(state);
	}
}