#pragma once
#include "../UIActor.h"
#include "../../world/IWorld.h"
#include "../../math/Math.h"

class SceneChangeManager :public UIActor {

public:
	SceneChangeManager(IWorld& world, const Vector2&position);
	~SceneChangeManager();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
	//�V�[���`�F���W�������ꍇ�͂������Ă�(true:�V�[���`�F���W����,false:�V�[���`�F���W���Ă�)
	void ChangeJudge(bool flag);
private:
	Vector2 mPosition;
};