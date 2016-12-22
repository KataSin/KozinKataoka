#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>
class ParticleManager:public Actor
{
public:
	//引数右から　ワールド、座標、パーティクル範囲、色、パーティクル数(入力の2乗)、乱数最小の値、乱数最大の値
	ParticleManager(IWorld& world, 
		const Vector3& position, 
		const Vector3& positionPlus, 
		const Vector4& color, 
		int particleNum, 
		const Vector3& maxRand, 
		const Vector3& minRand,
		const Vector3& hosei=Vector3::Zero);
	~ParticleManager();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//位置
	Vector3 mPosition;
	//初速度
	Vector3 mInitialVelocity;
};