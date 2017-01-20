#pragma once
#include "../UIActor.h"
#include "../../GamePlayManager/GamePlayManager.h"
#include <vector>
class ResultUI : public UIActor
{
public:
	ResultUI(IWorld& world,GamePlayManager& gameManager,PLAYER_NUMBER winPlayer );
	~ResultUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//���ʃe�N�X�`���T�C�Y
	Vector2 mTexSize;
	//�g���t�B�[��������|�W�V����
	Vector2 mTrophyPos;
	//�S�g���t�B�[�̃|�W�V����
	Vector2 mTrophyAllPos;
	//������
	std::map<PLAYER_NUMBER, int> mWinCount;
	//�������v���C���[
	PLAYER_NUMBER mWinPlayer;
	//���ʃ�
	float mAlpha;
	//�g���t�B�[��
	float mTrophyAlpha;
	//�g���t�B�[�T�C�Y
	float mSize;
};