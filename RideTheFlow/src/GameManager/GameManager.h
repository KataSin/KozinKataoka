#pragma once
#include "../world/IWorld.h"
#include "../actor/ID.h"
#include <vector>
#include <map>
class GameManager {
public:
	GameManager(IWorld& world);
	~GameManager();
	//���̃��E���h�ŏ������v���C���[��Ԃ�
	PLAYER_NUMBER IsWinPlayer();
	//�ŏI�I�ȏ����Ă���v���C���[��Ԃ�
	std::vector<PLAYER_NUMBER> IsFinalWinPlayer();
	//�Ō�̈�l�ɂȂ�����true��Ԃ�
	bool EndRaund();
	//�^�C���A�b�v�̏ꍇTrue��Ԃ�
	bool TimeUp();
	

private:
	IWorld& mWorld;
	std::map<PLAYER_NUMBER, int> mWinCount;

};