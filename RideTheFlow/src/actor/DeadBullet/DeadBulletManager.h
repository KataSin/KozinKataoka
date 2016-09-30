#pragma once
#include "../Actor.h"
#include <memory>
#include "../ID.h"

class DeadBulletManager :public Actor
{
public:
	DeadBulletManager(IWorld& world,Vector3 position,PLAYER_NUMBER player);
	~DeadBulletManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

};