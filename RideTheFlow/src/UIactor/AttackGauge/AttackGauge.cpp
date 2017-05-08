#include "AttackGauge.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
AttackGauge::AttackGauge(IWorld & world, Vector2 position, Actor& manager) :
	UIActor(world),
	mPosition(position),
	mColor(255, 255, 255, 1),
	velo(0.0f),
	mAlpha(0.0f),
	mAlphaTimer(0.0f),
	mAlphaFlag(false)
{
	mPlayerNumber = manager.GetParameter().playNumber;
	mManager = dynamic_cast<PlayerAttackManager*>(&manager);
	mOverHertCount = mManager->GetOverHertCount();
	parameter.isDead = false;
	parameter.playerNum = mManager->GetParameter().playNumber;

}

AttackGauge::~AttackGauge()
{
}

void AttackGauge::Update(PLAYER_NUMBER playerNumber)
{
	mPlayer = dynamic_cast<Player*>(world.GetPlayer(parameter.playerNum).get());
	for (auto i : world.GetUIActors(UI_ID::TARGET_UI)) {
		if (i->GetParameter().playerNum == parameter.playerNum) {
			mPosition = i->GetParameter().position + Vector2(50.0f, 0.0f);
		}
	}
	//攻撃してないときは透明に
	if (mManager->GetIsAttack()) mAlphaFlag = true;
	else if (!mManager->GetIsAttack() && mAlpha >= 0.7f) mAlphaFlag = false;
	//α値処理
	if (mAlphaFlag) {
		mAlpha += Time::GetInstance().deltaTime();
		mAlphaTimer = 0.0f;
	}
	else {
		mAlphaTimer += Time::GetInstance().deltaTime();
		if (mAlphaTimer >= 15.0f)
			mAlpha -= Time::GetInstance().deltaTime();
	}
	//ぬるぬるゲージが動く
	Spring(mOverHertCount, mManager->GetOverHertCount(), 0.1f, 0.5f, 2.0f);
	float leap = Math::Lerp(0.0f, 255.0f, mOverHertCount / 100.0f);
	mColor = Vector4(255.0f - leap, leap, 0.0f, 0.0f);
	//α値クランプ
	mAlpha = Math::Clamp(mAlpha, 0.0f, 0.7f);
}

void AttackGauge::Draw() const
{
	//リスポーン中は表示しない
	if (mPlayer->GetPlayerState() == PlayerState::PLAYERRESPAWN) return;
	Vector2 texSizeIn = Sprite::GetInstance().GetSize(SPRITE_ID::ATTACK_GAUGE_IN_SPRITE);
	Sprite::GetInstance().DrawGauge
		(SPRITE_ID::ATTACK_GAUGE_IN_SPRITE, mPosition - texSizeIn / 2, mColor, Vector2(1, 1), mAlpha, Math::Lerp(0.0f, 100.0f, mOverHertCount / 100.0f));
	Vector2 texSizeOut = Sprite::GetInstance().GetSize(SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE);
	Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE, mPosition - texSizeOut / 2, mAlpha);
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



