#include "GameManager.h"

GameManager::GameManager()
{
	mPads.clear();
}
GameManager::~GameManager()
{
}
void GameManager::Initialize()
{
	mPlayerRank.clear();
}

int GameManager::GetRaundCount()
{
	return mRaund;
}

void GameManager::SetRaundCount(int raundCount)
{
	mRaund = raundCount;
}

void GameManager::SetPlayerNum(int num)
{
	mPlayerNum = num;
}

int GameManager::GetPlayerNum()
{
	return mPlayerNum;
}

void GameManager::SetPlayerPad(std::vector<int> pads)
{
	mPads = pads;
}

std::vector<int> GameManager::GetPlayerPad()
{
	return mPads;
}

void GameManager::SetPlayerRank(std::list<PLAYER_NUMBER> playerRank)
{
	mPlayerRank = playerRank;
}

std::list<PLAYER_NUMBER> GameManager::GetPlayerRank()
{
	return mPlayerRank;
}


