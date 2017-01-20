#pragma once
#include "../../Actor.h"
#include <memory>
#include "../../Collision.h"
class StageLine :public Actor, public std::enable_shared_from_this<StageLine>
{
public:
	StageLine(IWorld& world, Matrix4& mat,Line& line);
	~StageLine();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

	Line GetLine() {
		return mLine;
	}
private:
	//���ʂ܂ł̎���
	float mDeadTimer;
	//�����ɂȂ��Ă�����
	float mAlphaTimer;
	//�����x
	float mAlpha;
	//line���W
	Vector3 mPosition;
	//��]Y
	float mRotateY;
	//���C��
	Line mLine;
};