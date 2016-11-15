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
#include "../UIactor/fadePanel/FadePanel.h"
#include "../game/Random.h"

#include "../UIactor/NumberTexture/NumberTexture.h"
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
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}
}

//描画
void TitleScene::Draw()
{
	wo.Draw();
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
	return Scene::GamePlay;
}

void TitleScene::End()
{
	wo.Clear();
}