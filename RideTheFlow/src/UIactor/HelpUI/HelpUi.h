#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player/Player.h"
#include <vector>
class HelpUi : public UIActor
{
public:
	HelpUi(IWorld& world);
	~HelpUi();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	int mPage;

	Vector2 mResPagePos;
	std::vector<Vector2> mPagePos;
	std::vector<Vector2> mMoviePos;
	Vector2 mPageVelo;
};