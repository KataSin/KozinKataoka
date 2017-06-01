#include "EndResult.h"
#include "../../world/IWorld.h"
#include "../../camera/Camera.h"
#include "../../actor/ResultPlayer/ResultPlayer.h"
#include "../../graphic/Model.h"
#include "../../graphic/Sprite.h"
EndResultUI::EndResultUI(IWorld & world, GameManager& gameManager) :
	UIActor(world),
	mGameManager(&gameManager)
{
	parameter.isDead = false;

	//�}�g���N�X�ݒ�
	mStageMat =
		Matrix4::Scale(10)*
		Matrix4::Translate(Vector3::Zero);
	mDaiMat =
		Matrix4::Scale(10)*
		Matrix4::Translate(Vector3(30, 10, 0));
	mSkyMat =
		Matrix4::Scale(5)*
		Matrix4::Translate(Vector3::Zero);

	//�T�C�Y�擾
	int size = mGameManager->GetPlayerRank().size();
	//�����v���C���[����
	for (int i = 0; i <= size - 1; i++) {
		Vector3 pos;
		if (size == 1)
			pos = Vector3(30, 80, 0);
		else if (size == 2)
			pos = Vector3(20 + (20 * i), 80, 0);
		else if (size == 3)
			pos = Vector3(15 + (15 * i), 80, 0);
		else if (size == 4)
			pos = Vector3(15 + (10 * i), 80, 0);
		//����
		world.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<ResultPlayer>
			(world, pos, mGameManager->GetPlayerRank()[i], ANIMATION::PLAYER_BUKI_IDLE_ANIM));
	}
	//���ԏ�����
	mActionTime = 0.0f;

	//�J�����ݒ�
	Camera::GetInstance().Position.Set(Vector3(30, 90, -300));
	Camera::GetInstance().Target.Set(Vector3(30, 80, 0));
	Camera::GetInstance().Update();
	//�J�����������n
	mResCameraPos = Vector3(30, 90, -300);
	mCameraPos = mResCameraPos;
	mCameraVelo = Vector3::Zero;
}

EndResultUI::~EndResultUI()
{
}

void EndResultUI::Update(PLAYER_NUMBER playerNumber)
{
	mActionTime = 0.0f;


}

void EndResultUI::Draw() const
{

	Model::GetInstance().Draw(MODEL_ID::RUN_STAGE_MODEL, mStageMat);
	Model::GetInstance().Draw(MODEL_ID::DAI_MODEL, mDaiMat);
	//�X�J�C�{�b�N�X
	Model::GetInstance().Draw(MODEL_ID::SKY_DEMO_MODEL, mSkyMat);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���U���g");
	DrawFormatString(128, 0, GetColor(255, 255, 255), "����");
	for (int i = 0; i <= mGameManager->GetPlayerRank().size() - 1; i++) {
		DrawFormatString(196 + (i * 64), 0, GetColor(255, 255, 255), "%dP", (int)mGameManager->GetPlayerRank()[i]);
	}

}
