#include "TitleScene.h"
#include "../AllInclude.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"

#include "../math/Math.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../UIactor/TitleUi/TitleUI.h"
#include "../actor/RotateStage/RotateStage.h"
//コンストラクタ
TitleScene::TitleScene()
{

}

//デストラクタ
TitleScene::~TitleScene()
{

}

//開始
void TitleScene::Initialize()
{
	mIsEnd = false; 
	mGameEndFlag = false;
	mTitleUi = std::make_shared<TitleUI>(wo);
	wo.UIAdd(UI_ID::TITLE_UI, mTitleUi);
	mScene = Scene::Select;
	Sound::GetInstance().PlayBGM(BGM_ID::GAME_TITLE_BGM,DX_PLAYTYPE_LOOP);

}

void TitleScene::Update()
{	
	auto state = static_cast<TitleUI*>(mTitleUi.get())->GetCursorStates();
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);

	for (const auto& i : state) {
		if (i.flag&&!mIsEnd) {
			if (i.state == TitleUI::SelectState::START)
				mScene = Scene::Select;
			else if (i.state == TitleUI::SelectState::HELP)
				mScene = Scene::Help;
			else
				mGameEndFlag = true;
			mIsEnd = true;
			break;
		}
	}
}

//描画
void TitleScene::Draw()
{
	wo.Draw();
	wo.UIDraw();

	DrawFormatString(0, 368, GetColor(255, 255, 255), "タイトルシーン");
}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return mScene;
}

void TitleScene::End()
{
	Sound::GetInstance().StopBGM();
	wo.Clear();
}

bool TitleScene::GetGameEndFlag()
{
	return mGameEndFlag;
}
