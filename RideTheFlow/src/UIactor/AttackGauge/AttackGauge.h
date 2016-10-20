#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
class AttackGauge : public UIActor
{
public:
	AttackGauge(IWorld& world,Actor* manager);
	~AttackGauge();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//ゲージ移動用用バネ
	void Spring(float& num, float resNum, float stiffness, float friction, float mass);
private:
	PLAYER_NUMBER mPlayerNumber;
	Player* mPlayer;
	Vector3 mPosition;
	Matrix4 playerMat;
	float mOverHertCount;
	float velo;
	PlayerAttackManager* mManager;
};