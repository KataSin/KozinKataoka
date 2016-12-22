#pragma once
#include "../Actor.h"
#include "../ID.h"
#include <memory>
class ParticleManager:public Actor
{
public:
	//�����E����@���[���h�A���W�A�p�[�e�B�N���͈́A�F�A�p�[�e�B�N����(���͂�2��)�A�����ŏ��̒l�A�����ő�̒l
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
	//�ʒu
	Vector3 mPosition;
	//�����x
	Vector3 mInitialVelocity;
};