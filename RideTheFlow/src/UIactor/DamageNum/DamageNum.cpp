//#include "DamageNum.h"
//#include "../../world/World.h"
//#include "../Collision.h"
//#include "../../time/Time.h"
//#include "../../graphic/Sprite.h"
//#include "../../game/Random.h"
//#include "../../actor/Player.h"
//#include "../../UIactor/NumberTexture/NumberTexture.h"
//
//DamageNum::DamageNum(IWorld & word, int damage) :
//	Actor(world)
//{
//	parameter.isDead = false;
//	mDamageNum = damage;
//	mPosition = actor.GetParameter().mat.GetPosition() + Vector3(0, 5, 0);
//	mPlayer = &actor;
//}
//DamageNum::~DamageNum()
//{
//}
//
//void DamageNum::Update()
//{
//	mPosition.y += Time::GetInstance().deltaTime();
//}
//
//void DamageNum::Draw() const
//{
//	NumberTexture num = NumberTexture(SPRITE_ID::SUUZI_SPRITE, 32, 64);
//	num.draw()
//}
//
//void DamageNum::OnCollide(Actor & other, CollisionParameter colpara)
//{
//}
