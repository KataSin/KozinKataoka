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
	//変わる色
	float clor;
	//プレートの色
	Vector4 plateClor;
	//ポジション
	Vector3 mPosition;
	//直前にあたった弾の情報
	PLAYER_NUMBER playerNum;
	//リスポーンカウント
	float respawnCount;
	//死んだか？
	bool mIsDead;
};