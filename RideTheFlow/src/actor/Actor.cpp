#include "Actor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "PlayerBullet\TargetRay.h"
#include "CameraActor\CameraActor.h"
#include "../math/Math.h"
#include <list>
#include <vector>

#include "../graphic/Model.h"
#include "Player\Player.h"
#include "StageLine\StageLine.h"

const Vector3 MinPlate = Vector3(-12.0f, -0.5f, -12.0f);
const Vector3 MaxPlate = Vector3(12.0f, 1.5f, 12.0f);

Actor::Actor(IWorld& world_) :world(world_)
{
	parameter.isDead = false;
	//colFunc[COL_ID::SPHERE_SPHERE_COL] = std::bind(&Actor::SphereSphere, this, std::placeholders::_1);
	//colFunc[COL_ID::CAPSULE_CAPSULE_COL] = std::bind(&Actor::CapsuleCapsule, this, std::placeholders::_1);
	//colFunc[COL_ID::CAPSULE_AABB_COL] = std::bind(&Actor::CapsuleAABBSegment, this, std::placeholders::_1);
	colFunc[COL_ID::PLATE_BULLET_COL] = std::bind(&Actor::Bullet_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::PLATE_PLAYER_COL] = std::bind(&Actor::Player_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_SNIPERLINE_COL] = std::bind(&Actor::Player_vs_SniperLine, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYERBULLET_PLAYER_COL] = std::bind(&Actor::Player_vs_Player, this, std::placeholders::_1);
	colFunc[COL_ID::BULLET_RESPAENPOINT_COL] = std::bind(&Actor::Bullet_vs_RespawnPoint, this, std::placeholders::_1);
	colFunc[COL_ID::BULLET_TREE_COL] = std::bind(&Actor::Bullet_vs_Tree, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_TREE_COL] = std::bind(&Actor::Player_vs_Tree, this, std::placeholders::_1);
	colFunc[COL_ID::PLATE_GUNRAY_COL] = std::bind(&Actor::GunRay_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::CAMERARAY_PLATE_COL] = std::bind(&Actor::CameraRay_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::CAMERA_PLATE_COL] = std::bind(&Actor::Camera_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::SNIPERLINE_PLATE_COL] = std::bind(&Actor::SniperLine_vs_Plate, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_GUNLINE_COL] = std::bind(&Actor::Player_vs_GunLine, this, std::placeholders::_1);
	colFunc[COL_ID::PLAYER_STAGELINE_COL] = std::bind(&Actor::Player_vs_StageLine, this, std::placeholders::_1);
}

Actor::~Actor()
{
	parent = nullptr;
}

void Actor::Collide(COL_ID id, Actor& other) {
	CollisionParameter colpara = colFunc[id](other);
	if (colpara.colFlag)
	{
		OnCollide(other, colpara);
		other.OnCollide(*this, colpara);
	}
}

ActorParameter Actor::GetParameter() const
{
	return parameter;
}

CollisionParameter Actor::Bullet_vs_Plate(const Actor & other) const
{
	//丸とボックスのあたり判定がないので線で代用
	CollisionParameter colpara;
	Line bullet;
	Vector3 pos = other.parameter.mat.GetPosition();
	float radius = other.parameter.radius;
	bullet.startPos = pos - Vector3(radius, 0.0f, 0.0f);
	bullet.endPos = pos + Vector3(radius, 0.0f, 0.0f);

	Box plate;
	plate.max = parameter.mat.GetPosition() + MaxPlate;
	plate.min = parameter.mat.GetPosition() + MinPlate;

	colpara = Collisin::GetInstace().SegmentBoxAABB(bullet, plate);
	colpara.colID = COL_ID::PLATE_BULLET_COL;
	if (colpara.colFlag)
		return colpara;

	bullet.startPos = pos - Vector3(0.0f, radius, 0.0f);
	bullet.endPos = pos + Vector3(0.0f, radius, 0.0f);

	colpara = Collisin::GetInstace().SegmentBoxAABB(bullet, plate);
	colpara.colID = COL_ID::PLATE_BULLET_COL;
	if (colpara.colFlag)
		return colpara;

	bullet.startPos = pos - Vector3(0.0f, 0.0f, radius);
	bullet.endPos = pos + Vector3(0.0f, 0.0f, radius);
	colpara = Collisin::GetInstace().SegmentBoxAABB(bullet, plate);
	colpara.colID = COL_ID::PLATE_BULLET_COL;
	
	return colpara;
}

CollisionParameter Actor::Player_vs_Plate(const Actor & other) const
{
	CollisionParameter colpara;
	Line player;
	player.startPos = other.parameter.mat.GetPosition();
	player.endPos = other.parameter.mat.GetPosition() + Vector3(0.0f, 0.25f, 0.0f);

	Box plate;
	plate.max = parameter.mat.GetPosition() + MaxPlate;
	plate.min = parameter.mat.GetPosition() + MinPlate;

	colpara = Collisin::GetInstace().SegmentBoxAABB(player, plate);

	colpara.colID = COL_ID::PLATE_PLAYER_COL;
	return colpara;
}

CollisionParameter Actor::Player_vs_Player(const Actor & other) const
{
	CollisionParameter colpara;
	Sphere bullet;
	bullet.position = parameter.mat.GetPosition();
	bullet.radius = parameter.radius;

	Capsule player;
	player.startPos = other.parameter.mat.GetPosition();
	player.endPos = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.height, 0.0f);
	player.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SphereCapsule(bullet, player);
	colpara.colID = COL_ID::PLAYERBULLET_PLAYER_COL;

	//自分の出した弾だったら当たっていない か　リスポーン中は当たらない
	if (other.parameter.playNumber == parameter.playNumber ||
		other.parameter.isRespawn)
		colpara.colFlag = false;

	return colpara;
}

CollisionParameter Actor::Player_vs_SniperLine(const Actor & other) const
{
	CollisionParameter colpara;
	//線とカプセルのあたり判定ではない
	Sphere player;
	player.position = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.height / 2.0f, 0.0f);
	player.radius = other.parameter.radius*1.5f;
	Line line;
	line.startPos = dynamic_cast<TargetRay*>(const_cast<Actor*>(this))->GetSniperLine().startPos;
	line.endPos = parameter.mat.GetPosition();
	colpara = Collisin::GetInstace().SegmentSphere(line, player);
	colpara.colID = COL_ID::PLAYER_SNIPERLINE_COL;
	//同じだったら当たらない
	if (other.parameter.playNumber == parameter.playNumber ||
		other.parameter.isRespawn || parameter.isRespawn)
		colpara.colFlag = false;
	return colpara;
}
//ここが全てのターゲットと自分の線とプレイヤーのあたり判定
CollisionParameter Actor::Player_vs_GunLine(const Actor & other) const
{
	CollisionParameter colpara;
	Sphere player;
	//プレイヤーの高さの1/2の半径
	player.position = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.radius/ 1.5f, 0.0f);
	player.radius = other.parameter.radius/1.5f;

	Line line;
	//どの武器を今使っているか
	if (dynamic_cast<TargetRay*>(const_cast<Actor*>(this))->GetState() == PlayerAttackState::MACHINE_GUN)
		line = dynamic_cast<TargetRay*>(const_cast<Actor*>(this))->GetLine();
	else
		line = dynamic_cast<TargetRay*>(const_cast<Actor*>(this))->GetSniperLine();

	colpara = Collisin::GetInstace().SegmentSphere(line, player);
	colpara.colID = COL_ID::PLAYER_GUNLINE_COL;

	//同じだったら当たらない
	if ((other.parameter.playNumber == parameter.playNumber) ||
		(other.parameter.isRespawn || parameter.isRespawn))
		colpara.colFlag = false;

	colpara.colFlagSub = dynamic_cast<TargetRay*>(const_cast<Actor*>(this))->colFlag();
	return colpara;
}

CollisionParameter Actor::Player_vs_Tree(const Actor & other) const
{
	CollisionParameter colpara;
	Capsule tree;
	tree.startPos = parameter.mat.GetPosition();
	tree.endPos = parameter.mat.GetPosition() + (parameter.mat.GetUp().Normalized()*parameter.height);
	tree.radius = parameter.radius;

	Sphere player;
	player.position = other.parameter.mat.GetPosition();
	player.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().PushedBack_SphereCapsule(player, tree);
	//押し返し位置取得
	colpara.colID = COL_ID::PLAYER_TREE_COL;
	return colpara;
}

CollisionParameter Actor::Bullet_vs_RespawnPoint(const Actor & other) const
{
	CollisionParameter colpara;
	//Sphere bullet;
	//bullet.position = parameter.mat.GetPosition();
	//bullet.radius = parameter.radius;

	//Sphere rePoint;
	//rePoint.position = other.parameter.mat.GetPosition();
	//rePoint.radius = other.parameter.radius;

	//colpara = Collisin::GetInstace().SphereSphere(bullet, rePoint);
	//colpara.colID = COL_ID::BULLET_RESPAENPOINT_COL;
	////同じだったら当たらない
	//if (other.parameter.playNumber == parameter.playNumber)
	colpara.colFlag = false;

	return colpara;
}

CollisionParameter Actor::Bullet_vs_Tree(const Actor & other) const
{
	CollisionParameter colpara;
	Capsule tree;
	tree.startPos = parameter.mat.GetPosition();
	tree.endPos = parameter.mat.GetPosition() + (parameter.mat.GetUp().Normalized()*parameter.height);
	tree.radius = parameter.radius;

	Sphere bullet;
	bullet.position = other.parameter.mat.GetPosition();
	bullet.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SphereCapsule(bullet, tree);

	if (!colpara.colFlag)
	{
		Sphere treeTop;
		treeTop.position = parameter.mat.GetPosition() + (parameter.mat.GetUp().Normalized()*parameter.height);
		treeTop.radius = parameter.radius*2.0f;
		colpara = Collisin::GetInstace().SphereSphere(bullet, treeTop);
	}
	//当たった瞬間のポジションを取る
	colpara.colPos = other.parameter.mat.GetPosition();
	colpara.colID = COL_ID::BULLET_TREE_COL;
	return colpara;
}

CollisionParameter Actor::GunRay_vs_Plate(const Actor & other) const
{
	CollisionParameter colpara;
	TargetRay* target = dynamic_cast<TargetRay*>(const_cast<Actor*>(this));
	Line line;
	line = target->GetLine();

	Box plate;
	plate.max = other.parameter.mat.GetPosition() + MaxPlate;
	plate.min = other.parameter.mat.GetPosition() + MinPlate;

	colpara = Collisin::GetInstace().SegmentBoxAABB(line, plate);
	colpara.colID = COL_ID::PLATE_GUNRAY_COL;
	return colpara;
}

CollisionParameter Actor::CameraRay_vs_Plate(const Actor & other) const
{
	CollisionParameter colpara;
	CameraActor* camera = dynamic_cast<CameraActor*>(const_cast<Actor*>(this));
	Line line;
	line = camera->GetCameraLine();
	Box plate;
	plate.max = other.parameter.mat.GetPosition() + Vector3(-2.25f, -0.225f, -2.25f);
	plate.min = other.parameter.mat.GetPosition() + Vector3(2.25f, 0.225f, 2.25f);

	colpara = Collisin::GetInstace().SegmentBoxAABB(line, plate);
	colpara.colID = COL_ID::CAMERARAY_PLATE_COL;
	return colpara;

}

CollisionParameter Actor::Camera_vs_Plate(const Actor & other) const
{
	CollisionParameter colpara;
	Line camera;
	camera = dynamic_cast<CameraActor*>(const_cast<Actor*>(this))->GetCameraLine();
	Box plate;
	plate.max = other.parameter.mat.GetPosition() + MaxPlate;
	plate.min = other.parameter.mat.GetPosition() + MinPlate;

	colpara = Collisin::GetInstace().SegmentBoxAABB(camera, plate);
	colpara.colID = COL_ID::CAMERA_PLATE_COL;
	return colpara;
}

CollisionParameter Actor::SniperLine_vs_Plate(const Actor & other) const
{
	CollisionParameter colpara;
	TargetRay* target = dynamic_cast<TargetRay*>(const_cast<Actor*>(this));
	Line line;
	line = target->GetSniperLine();

	Box plate;
	plate.max = other.parameter.mat.GetPosition() + MaxPlate;
	plate.min = other.parameter.mat.GetPosition() + MinPlate;

	colpara = Collisin::GetInstace().SegmentBoxAABB(line, plate);
	colpara.colID = COL_ID::SNIPERLINE_PLATE_COL;

	return colpara;
}

CollisionParameter Actor::Player_vs_StageLine(const Actor & other) const
{
	CollisionParameter colpara;

	Line line = dynamic_cast<StageLine*>(const_cast<Actor*>(this))->GetLine();

	Sphere player;
	player.position = other.parameter.mat.GetPosition() + Vector3(0.0f, other.parameter.height / 2.0f, 0.0f);
	player.radius = other.parameter.radius;

	colpara = Collisin::GetInstace().SegmentSphere(line, player);

	colpara.colID = COL_ID::PLAYER_STAGELINE_COL;
	return colpara;
}

