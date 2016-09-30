#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>

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

private:
	bool  mIsEnd;
	World wo;
};