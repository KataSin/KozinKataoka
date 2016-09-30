#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>
#include "../../math/Vector4.h"
#include "../ID.h"
class DefaultPlate :public Actor, public std::enable_shared_from_this<DefaultPlate>
{
public:
	DefaultPlate(IWorld& world,Vector3 position);
	~DefaultPlate();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	//�ς��F
	float clor;
	//�v���[�g�̐F
	Vector4 plateClor;
	//�|�W�V����
	Vector3 mPosition;
	//���O�ɂ��������e�̏��
	PLAYER_NUMBER playerNum;
	//���X�|�[���J�E���g
	float respawnCount;
	//���񂾂��H
	bool mIsDead;
};