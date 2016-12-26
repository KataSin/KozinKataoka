#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GameManager/GameManager.h"

class  Result : public IScene
{

public:
	//�R���X�g���N�^ 
	Result(GameManager& gameManager);
	//�f�X�g���N�^
	~Result();

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

private:
	GameManager* mGameManager;
	bool  mIsEnd;
	World wo;
	Light light;

	int test;
};