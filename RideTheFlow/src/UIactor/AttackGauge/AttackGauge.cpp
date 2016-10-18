#include "AttackGauge.h"
#include "../../world/IWorld.h"
AttackGauge::AttackGauge(IWorld & world, Actor* manager) :
	UIActor(world),
	mPosition(Vector3::Zero),
	playerMat(Matrix4::Identity),
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
	if (mPlayerNumber == playerNumber)
	{
		playerMat = world.GetPlayer(mPlayerNumber)->GetParameter().mat;
		mPosition = playerMat.GetLeft()*3.0f + playerMat.GetPosition();
		//スクリーン座標に
		mPosition = Vector3::ToVECTOR(ConvWorldPosToScreenPos
			(Vector3::ToVECTOR(mPosition)));
		//ぬるぬるゲージが動く
		Spring(mOverHertCount, mManager->GetOverHertCount(), 0.2f, 0.5f, 2.0f);
	}
}

void AttackGauge::Draw() const
{
	//ゲージ中身
	Sprite::GetInstance().DrawGauge(SPRITE_ID::ATTACK_GAUGE_IN_SPRITE,Vector2(mPosition.x,mPosition.y-256.0f),Vector2(1),1,mOverHertCount);
	//ゲージ外側
	Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE, Vector2(mPosition.x, mPosition.y - 256.0f));
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
