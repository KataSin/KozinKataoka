#include "HelpUi.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../graphic/Movie.h"
HelpUi::HelpUi(IWorld & world):
UIActor(world)
{
	parameter.isDead = false;

	mResPagePos = Vector2(0.0f, 0.0f);

	mPagePos.push_back(Vector2::Zero);
	mPagePos.push_back(Vector2(1280.0f, 0.0f));
	mPagePos.push_back(Vector2(2558.0f, 0.0f));

	mMoviePos.push_back(Vector2(1280+1000, 200));
	mMoviePos.push_back(Vector2(1280 + 1150, 330));
	mMoviePos.push_back(Vector2(1280 + 1000, 460));

	Movie::GetInstance().Play(MOVIE_ID::MACHINE_GUN_HELP);
	Movie::GetInstance().Play(MOVIE_ID::SHOT_GUN_HELP);
	Movie::GetInstance().Play(MOVIE_ID::SNIPER_GUN_HELP);


	mPage = 0;
}
HelpUi::~HelpUi()

{
}

void HelpUi::Update(PLAYER_NUMBER playerNumber)
{
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT) ||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD1) == 90||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD2) == 90 ||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD3) == 90 ||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD4) == 90) {
		mPage++;
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT) ||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD1) == 270||
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD2) == 270 || 
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD3) == 270 || 
		GamePad::GetInstance().POVTriggerDown(PADNUM::PAD4) == 270) {
		mPage--;
	}

	mPage = Math::Clamp(mPage, 0, 2);

	mResPagePos = Vector2(1280.0f * -mPage, 0.0f);

	Vector2::Spring(mPagePos[0], mPageVelo, mResPagePos, 0.2f, 0.5f, 2.0f);

	mPagePos[1] += mPageVelo;
	mPagePos[2] += mPageVelo;

	if (!Movie::GetInstance().IsPlay(MOVIE_ID::MACHINE_GUN_HELP)) {
		Movie::GetInstance().Seek(MOVIE_ID::MACHINE_GUN_HELP, 0.0f);
		Movie::GetInstance().Play(MOVIE_ID::MACHINE_GUN_HELP);
	}
	if (!Movie::GetInstance().IsPlay(MOVIE_ID::SNIPER_GUN_HELP)) {
		Movie::GetInstance().Seek(MOVIE_ID::SNIPER_GUN_HELP, 0.0f);
		Movie::GetInstance().Play(MOVIE_ID::SNIPER_GUN_HELP);
	}
	if (!Movie::GetInstance().IsPlay(MOVIE_ID::SHOT_GUN_HELP)) {
		Movie::GetInstance().Seek(MOVIE_ID::SHOT_GUN_HELP, 0.0f);
		Movie::GetInstance().Play(MOVIE_ID::SHOT_GUN_HELP);
	}

	for (auto& i : mMoviePos) {
		i += mPageVelo;
	}
}

void HelpUi::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::HELP_1_SPRITE, mPagePos[0]);
	Sprite::GetInstance().Draw(SPRITE_ID::HELP_2_SPRITE, mPagePos[1]);
	Sprite::GetInstance().Draw(SPRITE_ID::HELP_3_SPRITE, mPagePos[2]);

	Movie::GetInstance().DrawRotaMovie(MOVIE_ID::MACHINE_GUN_HELP, mMoviePos[0],0.8f);
	Movie::GetInstance().DrawRotaMovie(MOVIE_ID::SHOT_GUN_HELP, mMoviePos[1], 0.8f);
	Movie::GetInstance().DrawRotaMovie(MOVIE_ID::SNIPER_GUN_HELP, mMoviePos[2], 0.8f);

}
