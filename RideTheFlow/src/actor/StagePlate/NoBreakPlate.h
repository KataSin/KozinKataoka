#pragma once
#include "../Actor.h"
#include "../../math/Vector3.h"
#include <memory>
#include "../../math/Vector4.h"
#include "../ID.h"
class NoBreakPlate :public Actor, public std::enable_shared_from_this<NoBreakPlate>
{
public:
	NoBreakPlate(IWorld& world, const Vector3& position);
	~NoBreakPlate();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	Vector3 mPosition;

};