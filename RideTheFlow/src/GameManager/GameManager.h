#pragma once
#include "../actor/ID.h"
#include <list>
class GameManager
{
public:
	GameManager();
	~GameManager();
	//�v���C���[�̃����N���Z�b�g
	void SetPlayerRank(std::list<PLAYER_NUMBER> playerRank);
	//�v���C���[�̃����N���擾
	std::list<PLAYER_NUMBER> GetPlayerRank();
	//�v���C���[�̏�����������
	void Initialize();
	//���E���h�����擾
	int GetRaundCount();
	//���E���h����ݒ�
	void SetRaundCount(int raundCount);
	//�v���C����l����ݒ�
	void SetPlayerNum(int num);
	//�v���C����l�����擾
	int GetPlayerNum();

private:
	std::list<PLAYER_NUMBER> mPlayerRank;
	int mRaund;
	int mPlayerNum;
};