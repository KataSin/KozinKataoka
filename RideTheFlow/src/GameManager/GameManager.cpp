#include "GameManager.h"

GameManager::GameManager()
{
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

void GameManager::SetPlayerRank(std::list<PLAYER_NUMBER> playerRank)
{
	mPlayerRank = playerRank;
}

std::list<PLAYER_NUMBER> GameManager::GetPlayerRank()
{
	return mPlayerRank;
}


