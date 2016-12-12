#pragma once
#include "../Actor.h"

class Pool :public Actor
{
public:
	Pool(IWorld& world, Vector3& pos1,Vector3& pos2);
	~Pool();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
private:
	//�|�[���̍��W
	Vector3 mPos1;
	Vector3 mPos2;
	//line�̃|�W�V����
	Vector3 mLinePosition;
	//�o���^�C�}�[
	float mTimer;

};