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
#include "../game/Random.h"
#include "../UIactor/SceneChangeManager/SceneChangeManager.h"
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
}

void TitleScene::Update()
{	
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_NULL);
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}
}

//描画
void TitleScene::Draw()
{
	wo.Draw();
	wo.UIDraw();
	Vector2 titlePos = Vector2(WINDOW_WIDTH / 2.0f, 120.0f);
	Vector2 titleSize = Sprite::GetInstance().GetSizeVector(SPRITE_ID::TITLE_SPRITE);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_SPRITE, titlePos, titleSize / 2.0f, Vector2(1.3f,1.3f), true, false);
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
	return Scene::Select;
}

void TitleScene::End()
{
	wo.Clear();
}