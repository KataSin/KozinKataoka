#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GameManager/GameManager.h"

class  SelectScene : public IScene
{
public:
	//�R���X�g���N�^ 
	SelectScene(GameManager& gameManager);
	//�f�X�g���N�^
	~SelectScene();
	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update()override;
	//�`�揈��
	virtual void Draw() override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;

	virtual bool GetGameEndFlag()override;

private:
	//�Q�[���}�l�[�W���[
	GameManager* mGameManager;
	//�Z���N�gUI(����������ԊǗ����Ă���)
	UIActorPtr mSelectUi;
	//�I�������
	bool  mIsEnd;
	//���[���h
	World wo;
	Light light;
	std::vector<int> mPads;
	//�V�[��
	Scene mScene;
};