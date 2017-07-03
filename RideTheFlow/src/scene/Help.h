#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>
#include "../UIactor/NumberTexture/NumberTexture.h"

class  Help : public IScene
{

public:
	//�R���X�g���N�^ 
	Help();
	//�f�X�g���N�^
	~Help();
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
	//���̃V�[��
	Scene mScene;
	//�Q�[���I��邩�ǂ���
	bool mGameEndFlag;
};