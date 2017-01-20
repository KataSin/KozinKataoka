#pragma once
#include "../AllInclude.h"
#include "ID.h"
#include "../graphic/Sprite.h"
#include <map>
#include <functional>
#include "../math/Matrix4.h"

class IWorld;
struct CollisionParameter;

struct ActorParameter
{
	ACTOR_ID id;
	bool isDead;
	bool isRespawn=false;
	float radius;
	Matrix4 mat;
	float   HP;
	float height;
	PLAYER_NUMBER playNumber;
};

class Actor{
public:
	Actor(IWorld& world_);
	virtual ~Actor();
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	void Collide(COL_ID id, Actor& other);
	virtual bool IsDead() const{ return parameter.isDead; }
	void SetIsDead(bool flag){ parameter.isDead = flag; }
	ActorParameter GetParameter() const;

private:
	std::map<COL_ID, std::function<CollisionParameter(const Actor&)>> colFunc;
	CollisionParameter Bullet_vs_Plate(const Actor& other)const;
	CollisionParameter Player_vs_Plate(const Actor& other)const;
	CollisionParameter Player_vs_Player(const Actor& other)const;
	CollisionParameter Player_vs_SniperLine(const Actor& other)const;
	CollisionParameter Player_vs_GunLine(const Actor& other)const;
	CollisionParameter Player_vs_Tree(const Actor& other) const;
	CollisionParameter Bullet_vs_RespawnPoint(const Actor& other)const;
	CollisionParameter Bullet_vs_Tree(const Actor& other) const;
	CollisionParameter GunRay_vs_Plate(const Actor& other)const;
	CollisionParameter CameraRay_vs_Plate(const Actor& other)const;
	CollisionParameter Camera_vs_Plate(const Actor& other)const;
	CollisionParameter SniperLine_vs_Plate(const Actor& other)const;

	CollisionParameter Player_vs_StageLine(const Actor& other)const;
	//弾とトルネードのあたり判定
	//CollisionParameter Bullet_vs_Tornad(const Actor& other)const;

protected:
	virtual void OnCollide(Actor& other, CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;

public:
	Actor* parent = nullptr;
};