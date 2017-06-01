#pragma once
#include "../actor/ID.h"
#include <vector>
class GameManager
{
public:
	GameManager();
	~GameManager();
	//�v���C���[�̃����N���Z�b�g
	void SetPlayerRank(std::vector<PLAYER_NUMBER> playerRank);
	//�v���C���[�̃����N���擾
	std::vector<PLAYER_NUMBER> GetPlayerRank();
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
	//���v���C���[���Z�b�g�i�p�b�h�Z�b�g�j
	void SetPlayerPad(std::vector<int> pads);
	//���v���C���[���擾�i�p�b�h�Q�b�g�j
	std::vector<int> GetPlayerPad();

private:
	std::vector<PLAYER_NUMBER> mPlayerRank;
	std::vector<int>mPads;
	int mRaund;
	int mPlayerNum;
};