#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../graphic/Light.h"
#include <array>
#include "../GamePlayManager/GamePlayManager.h"
#include "../GameManager/GameManager.h"

class  GamePlay : public IScene
{

public:
	//�R���X�g���N�^ 
	GamePlay(GameManager& gameManager);
	//�f�X�g���N�^
	~GamePlay();

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
	typedef std::shared_ptr<GamePlayManager>GamePlayManagerPtr;
	GamePlayManagerPtr mGamePlayManager;
	GameManager* mGameManager;
	Scene mNextScene;
	bool  mIsEnd;
	World wo;
	Light light;

	int test;

	int mRandCount;
	int mEndRaundCount;
};