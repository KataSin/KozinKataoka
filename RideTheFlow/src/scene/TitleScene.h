#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>
#include "../UIactor/NumberTexture/NumberTexture.h"

class  TitleScene : public IScene
{

public:
	//�R���X�g���N�^ 
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();

	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update()override;
	//�`�揈��
	virtual void Draw()override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;

	virtual bool GetGameEndFlag()override;
private:
	bool  mIsEnd;
	World wo;
	//�^�C�g����UI
	UIActorPtr mTitleUi;
	//���̃V�[��
	Scene mScene;
	//�Q�[���I��邩�ǂ���
	bool mGameEndFlag;
};