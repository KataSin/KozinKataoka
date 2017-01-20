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
	//€‚Ê‚Ü‚Å‚ÌŠÔ
	float mDeadTimer;
	//“§–¾‚É‚È‚Á‚Ä‚­ŠÔ
	float mAlphaTimer;
	//“§–¾“x
	float mAlpha;
	//lineÀ•W
	Vector3 mPosition;
	//‰ñ“]Y
	float mRotateY;
	//ƒ‰ƒCƒ“
	Line mLine;
};