#include "GameManager.h"
#include "../actor/Collision.h"
#include "../actor/Player.h"
GameManager::GameManager(IWorld & world):
	mWorld(world)
{
	//������
	mWinCount[PLAYER_NUMBER::PLAYER_1] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_2] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_3] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_4] = 0;
}

GameManager::~GameManager()
{
}

PLAYER_NUMBER GameManager::IsWinPlayer()
{
	std::vector<Player*> players;
	for (const auto& i : mWorld.GetActors(ACTOR_ID::PLAYER_ACTOR)) {
		//���X�|�[�����ĂȂ�����������
		if(!i.get()->GetParameter().isRespawn)
		players.push_back(dynamic_cast<Player*>(i.get()));
	}
	//�Ō�̈�l�ɂȂ��Ă���
	if (players.size() == 1) {
		PLAYER_NUMBER win = players.front()->GetParameter().playNumber;
		//������1�v���X
		mWinCount[win] += 1;
		return win;
	}
	//�������I����ĂȂ�
	return PLAYER_NUMBER::PLAYER_NULL;
}

std::vector<PLAYER_NUMBER> GameManager::IsFinalWinPlayer()
{
	PLAYER_NUMBER win;
	int winCount=0;
	//���������̏ꍇ�����邽��
	std::vector<PLAYER_NUMBER>winPlayers;
	for (const auto& i : mWinCount) {
		//�����Ă���S�������Ă܂������
		if (winCount < i.second) {
			winPlayers.clear();
			winCount = i.second;
			winPlayers.push_back(i.first);
		}
		//���_�̏ꍇ�ǉ����邾��
		else if (winCount == i.second) {
			winPlayers.push_back(i.first);
		}
	}
	return winPlayers;
}

bool GameManager::EndRaund()
{
	return false;
}

bool GameManager::TimeUp()
{
	return false;
}