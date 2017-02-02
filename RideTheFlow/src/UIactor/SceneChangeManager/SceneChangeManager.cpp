#include "SceneChangeManager.h"
#include <memory>
#include "ChangeParticle\ChangeParticle.h"
#include "../../game/Random.h"
#include "../../input/Keyboard.h"
#include "../../actor/ID.h"
#include "ChangeBlock\ChangeBlock.h"
#include "../../Def.h"
SceneChangeManager::SceneChangeManager(IWorld & world, const Vector2&position) :
	UIActor(world),
	mPosition(position)
{
	parameter.isDead = false;

	Vector2 qsize = Sprite::GetInstance().GetSize(SPRITE_ID::TEST_SPRITE);
	for (int x = 0; x <= 1280 / 16; x++) {
		for (int y = 0; y <= 720 / 16; y++) {
			TexState state;
			state.toPos = Vector2(x * 16, y * 16)+Vector2(8,8);
			state.randAngle = Random::GetInstance().Range(-360, 360);
			state.texHandle = DerivationGraph(16*x, 16*y, 16, 16, Sprite::GetInstance().GetIndex(SPRITE_ID::TEST_SPRITE));
			int randSide = Random::GetInstance().Range(0, 4);
			switch (randSide)
			{
			case 0: {
				state.randPos = Vector2(Random::GetInstance().Range(-150, -100), Random::GetInstance().Range(-100, WINDOW_HEIGHT+100));
				break;
			}
			case 1: {
				state.randPos = Vector2(Random::GetInstance().Range(WINDOW_WIDTH+100, WINDOW_WIDTH + 150), Random::GetInstance().Range(-100, WINDOW_HEIGHT+150));
				break;
			}
			case 2: {
				state.randPos = Vector2(Random::GetInstance().Range(-100, WINDOW_WIDTH+100), Random::GetInstance().Range(-150, -100));
				break;
			}
			case 3: {
				state.randPos = Vector2(Random::GetInstance().Range(-100, WINDOW_WIDTH + 100), Random::GetInstance().Range(WINDOW_HEIGHT+100,WINDOW_HEIGHT+150));
				break;
			}
			}

			world.UIAdd(UI_ID::CHANGE_BLOK_UI, std::make_shared<ChangeBlock>(world,state));
		}
	}
}

SceneChangeManager::~SceneChangeManager()
{
}

void SceneChangeManager::Update(PLAYER_NUMBER playerNumber)
{
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G)) {
	//	Vector2 randVec = Vector2(Random::GetInstance().Range(-300, -10), Random::GetInstance().Range(-30, 30));
	//	float randAngle = Random::GetInstance().Range(-100, 100);
	//	float randDeadTime = 5.0f;
	//	float randSize = Random::GetInstance().Range(0.2f, 0.4f);
	//	world.UIAdd(UI_ID::PARTICLE_UI, std::make_shared<ChangeParticle>(world, mPosition, randVec, randAngle, randDeadTime,randSize));
	//}



}

void SceneChangeManager::Draw() const
{
}

void SceneChangeManager::ChangeJudge(bool flag)
{

}
