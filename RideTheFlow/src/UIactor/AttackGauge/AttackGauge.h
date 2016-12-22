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
	//�Q�[�W�ړ��p�p�o�l
	void Spring(float& num, float resNum, float stiffness, float friction, float mass);
private:
	//�v���C���[
	Player* mPlayer;
	//�v���C���[�i���o�[
	PLAYER_NUMBER mPlayerNumber;
	//���W
	Vector2 mPosition;
	//�J���[
	Vector4 mColor;
	//�I�[�o�[�q�[�g�J�E���g
	float mOverHertCount;
	//��ԑ��x
	float velo;
	//�A�^�b�N�}�l�[�W���[
	PlayerAttackManager* mManager;
	//���l
	float mAlpha;
	//���^�C�}�[
	float mAlphaTimer;
	//���t���O
	float mAlphaFlag;
};