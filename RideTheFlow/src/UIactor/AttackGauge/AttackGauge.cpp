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
		//�X�N���[�����W��
		mPosition = Vector3::ToVECTOR(ConvWorldPosToScreenPos
			(Vector3::ToVECTOR(mPosition)));
		//�ʂ�ʂ�Q�[�W������
		Spring(mOverHertCount, mManager->GetOverHertCount(), 0.2f, 0.5f, 2.0f);
	}
}

void AttackGauge::Draw() const
{
	//�Q�[�W���g
	Sprite::GetInstance().DrawGauge(SPRITE_ID::ATTACK_GAUGE_IN_SPRITE,Vector2(mPosition.x,mPosition.y-256.0f),Vector2(1),1,mOverHertCount);
	//�Q�[�W�O��
	Sprite::GetInstance().Draw(SPRITE_ID::ATTACK_GAUGE_OUT_SPRITE, Vector2(mPosition.x, mPosition.y - 256.0f));
}

void AttackGauge::Spring(float& num, float resNum, float stiffness, float friction, float mass)
{
	// �o�l�̐L�ы���v�Z
	float stretch = (num - resNum);
	// �o�l�̗͂��v�Z
	float force = -stiffness * stretch;
	// �����x��ǉ�
	float acceleration = force / mass;
	// �ړ����x���v�Z
	velo = friction * (velo + acceleration);
	// ���W�̍X�V
	num += velo;
}
