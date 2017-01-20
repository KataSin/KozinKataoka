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
	//死ぬまでの時間
	float mDeadTimer;
	//透明になってく時間
	float mAlphaTimer;
	//透明度
	float mAlpha;
	//line座標
	Vector3 mPosition;
	//回転Y
	float mRotateY;
	//ライン
	Line mLine;
};