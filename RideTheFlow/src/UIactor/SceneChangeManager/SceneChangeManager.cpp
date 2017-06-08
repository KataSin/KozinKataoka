#include "SceneChangeManager.h"
#include <memory>
#include "ChangeParticle\ChangeParticle.h"
#include "../../game/Random.h"
#include "../../input/Keyboard.h"
#include "../../actor/ID.h"
#include "ChangeBlock\ChangeBlock.h"
#include "../../Def.h"
#include "../../time/Time.h"
SceneChangeManager::SceneChangeManager(IWorld & world) :
	UIActor(world),
	mFlag(false),
	mTime(0.0f),
	mTimeCount(0.0f)
{
	parameter.isDead = false;
	mBlocks.clear();
	SpriteSet(SPRITE_ID::SCENE_CHANGE_STAGE_SELECT_SPRITE);
}

SceneChangeManager::~SceneChangeManager()
{
}

void SceneChangeManager::Update(PLAYER_NUMBER playerNumber)
{
	if (mFlag)
		mTime += Time::GetInstance().deltaTime();
	else
		mTime -= Time::GetInstance().deltaTime();

	mTime = Math::Clamp(mTime, 0.0f, 1.0f);
	if (mTime == 1.0f)
		mTimeCount += Time::GetInstance().deltaTime();
	else
		mTimeCount = 0.0f;
}

void SceneChangeManager::Draw() const
{
}

void SceneChangeManager::ChangeJudge(bool flag)
{
	mFlag = flag;
}

float SceneChangeManager::GetTime()
{
	return mTime;
}

bool SceneChangeManager::GetNoBlockFlag()
{
	return mTime == 0.0f ? true : false;
}

bool SceneChangeManager::GetYesBlockFlag()
{
	return mTime >= 1.0f ? true : false;
}

void SceneChangeManager::SpriteSet(const SPRITE_ID & id)
{
	//Š®‘S‚É‚Í‚¯‚Ä‚¢‚È‚¢‚Æ”­“®‚µ‚È‚¢
	if (mTime != 0.0f&&mNowId == id)return;
	//‘O‚Ì‚à‚Ì‚Ííœ
	if (mBlocks.size() != 0) {
		for (auto& i : mBlocks) {
			static_cast<ChangeBlock*>(i.get())->Dead();
		}
		mBlocks.clear();
	}

	//•ªŠ„‰æ‘œ‚ğ¶¬•’Ç‰Á
	Vector2 qsize = Sprite::GetInstance().GetSize(id);
	for (int x = 0; x <= 1280 / 32; x++) {
		for (int y = 0; y <= 720 / 32; y++) {
			TexState state;
			int textureSize = 32;
			state.toPos = Vector2(x * textureSize, y * textureSize) + Vector2(textureSize / 2, textureSize / 2);
			state.randAngle = Random::GetInstance().Range(-360, 360);
			state.texHandle = DerivationGraph(textureSize*x, textureSize*y, textureSize, textureSize, Sprite::GetInstance().GetIndex(id));
			int randSide = Random::GetInstance().Range(0, 4);
			switch (randSide)
			{
			case 0: {
				state.randPos = Vector2(Random::GetInstance().Range(-150, -100), Random::GetInstance().Range(-100, WINDOW_HEIGHT + 100));
				break;
			}
			case 1: {
				state.randPos = Vector2(Random::GetInstance().Range(WINDOW_WIDTH + 100, WINDOW_WIDTH + 150), Random::GetInstance().Range(-100, WINDOW_HEIGHT + 150));
				break;
			}
			case 2: {
				state.randPos = Vector2(Random::GetInstance().Range(-100, WINDOW_WIDTH + 100), Random::GetInstance().Range(-150, -100));
				break;
			}
			case 3: {
				state.randPos = Vector2(Random::GetInstance().Range(-100, WINDOW_WIDTH + 100), Random::GetInstance().Range(WINDOW_HEIGHT + 100, WINDOW_HEIGHT + 150));
				break;
			}
			}
			UIActorPtr ui = std::make_shared<ChangeBlock>(world, state, *this);
			world.UIAdd(UI_ID::CHANGE_BLOK_UI, ui);
			mBlocks.push_back(ui);
			mNowId = id;
		}
	}
}

