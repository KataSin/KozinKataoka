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
//�R���X�g���N�^
TitleScene::TitleScene()
{

}

//�f�X�g���N�^
TitleScene::~TitleScene()
{

}

//�J�n
void TitleScene::Initialize()
{
	mIsEnd = false;
	//wo.UIAdd(UI_ID::PARTICLE_UI, std::make_shared<SceneChangeManager>(wo, Vector2(800, 500)));
}

void TitleScene::Update()
{	
	wo.Update();
	wo.UpdateUI(PLAYER_NUMBER::PLAYER_1);
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}
}

//�`��
void TitleScene::Draw()
{
	wo.Draw();
	wo.UIDraw();
	DrawFormatString(0, 368, GetColor(255, 255, 255), "�^�C�g���V�[��");
}

//�I�����Ă��邩�H
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene TitleScene::Next() const
{
	return Scene::Select;
}

void TitleScene::End()
{
	wo.Clear();
}