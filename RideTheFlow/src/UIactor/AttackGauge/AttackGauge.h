#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
class AttackGauge : public UIActor
{
public:
	AttackGauge(IWorld& world,Vector2 position,Actor& manager);
	~AttackGauge();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//ゲージ移動用用バネ
	void Spring(float& num, float resNum, float stiffness, float friction, float mass);
private:
	//プレイヤー
	Player* mPlayer;
	//プレイヤーナンバー
	PLAYER_NUMBER mPlayerNumber;
	//座標
	Vector2 mPosition;
	//カラー
	Vector4 mColor;
	//オーバーヒートカウント
	float mOverHertCount;
	//補間速度
	float velo;
	//アタックマネージャー
	PlayerAttackManager* mManager;
	//α値
	float mAlpha;
	//αタイマー
	float mAlphaTimer;
	//αフラグ
	float mAlphaFlag;
};