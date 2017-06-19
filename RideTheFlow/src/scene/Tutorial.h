#pragma once
#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>

class  Tutorial : public IScene
{

public:
	//�R���X�g���N�^ 
	Tutorial();
	//�f�X�g���N�^
	~Tutorial();

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
	//���̃V�[��
	Scene mNextScene;
	//�G���h�t���O
	bool  mIsEnd;
	//���[���h
	World wo;
	//���l�v���C���[�����邩
	int mPlayerNum;
};