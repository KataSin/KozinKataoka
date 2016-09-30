#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include "ID.h"
#include <memory>
#include "../camera/Camera.h"
class RespawnPoint :public Actor, public std::enable_shared_from_this<RespawnPoint>
{
public:
	RespawnPoint(IWorld& word,Vector3 position,float rotateY,PLAYER_NUMBER player);
	~RespawnPoint();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;
	PLAYER_NUMBER mPlayerNum;
};