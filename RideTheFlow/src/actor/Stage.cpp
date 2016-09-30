#include "Stage.h"
#include "Collision.h"
#include "../graphic/Model.h"
#include "../actor/StagePlate/DefaultPlate.h"
#include"../world/IWorld.h"
#include "RespawnPoint.h"
#include "Tree\Tree.h"
static const int MODEL_SIZE = 240;

Stage::Stage(IWorld& world) :
Actor(world),
skyMat(Matrix4::Identity){
	parameter.isDead = false;

	skyMat = 
		Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);
	//デフォルトパネルの設置
	for (int x = 0; x <= 20; x++)
	{
		for (int y = 0; y <= 20; y++)
		{
			world.Add(ACTOR_ID::PLATE_ACTOR, std::make_shared<DefaultPlate>(world,
				Vector3(4.5f*x,0.0f,4.5f*y)));
		}
	}
	//プレイヤーがスポーンするポイントを生成
	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3::Zero,
		315.0f,
		PLAYER_NUMBER::PLAYER_1));

	world.Add(ACTOR_ID::RESPAWNPOINT_ACTOR, std::make_shared<RespawnPoint>(world,
		Vector3(90,0,90),
		135.0f,
		PLAYER_NUMBER::PLAYER_2));

	//木の追加
	world.Add(ACTOR_ID::TREE_ACTOR, std::make_shared<Tree>(world,
		Vector3(15,0,15)));
}
Stage::~Stage(){
	parent = nullptr;
}

void Stage::Update(){
}
void Stage::Draw() const{
	//ステージの描写
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL,skyMat);
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara){

}