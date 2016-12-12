#include "AttackGauge.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
AttackGauge::AttackGauge(IWorld & world,Vector2 position, Actor* manager) :
	UIActor(world),
	mPosition(position),
	playerMat(Matrix4::Identity),
	mColor(255,255,255,1),
	velo(0.0f)
{
	parameter.isDead = false;
	mPlayerNumber = manager->GetParameter().playNumber;
	mManager = dynamic_cast<PlayerAttackManager*>(manager);
	mOverHertCount = mManager->GetOverHertCount();
}

AttackGauge::~AttackGauge()
{
}

void AttackGauge::Update(PLAYER_NUMBER playerNumber)
{
	//ぬるぬるゲージが動く
	Spring(mOverHertCount, mManager->GetOverHertCount(), 0.1f, 0.5f, 2.0f);
	float leap = Math::Lerp(0.0f, 255.0f, mOverHertCount/100.0f);
	mColor = Vector4(255.0f - leap, leap, 0.0f, 0.0f);
}

void AttackGauge::Draw() const
{

	Sprite::GetInstance().DrawGaugeCircle
		(SPRITE_ID::ATTACK_GAUGE_IN_SPRITE, mPosition, mColor, Math::Lerp(0.0f, 75.0f, mOverHertCount / 100.0f));
	Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE, mPosition);
}

void AttackGauge::Spring(float& num, float resNum, float stiffness, float friction, float mass)
{
	// バネの伸び具合を計算
	float stretch = (num - resNum);
	// バネの力を計算
	float force = -stiffness * stretch;
	// 加速度を追加
	float acceleration = force / mass;
	// 移動速度を計算
	velo = friction * (velo + acceleration);
	// 座標の更新
	num += velo;
}



