#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>
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
	MODEL_ID mModelId;
	float mRotateY;
};