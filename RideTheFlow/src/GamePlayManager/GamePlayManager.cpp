#include "GamePlayManager.h"
#include "../actor/Collision.h"
#include "../actor/Player.h"
#include "../UIactor/GameTimer/GameTimerUI.h"
GamePlayManager::GamePlayManager(IWorld & world):
	mWorld(world)
{
	//初期化
	mWinCount[PLAYER_NUMBER::PLAYER_1] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_2] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_3] = 0;
	mWinCount[PLAYER_NUMBER::PLAYER_4] = 0;
}

GamePlayManager::~GamePlayManager()
{
}

PLAYER_NUMBER GamePlayManager::IsWinPlayer()
{
	std::vector<Player*> players;
	for (const auto& i : mWorld.GetActors(ACTOR_ID::PLAYER_ACTOR)) {
		//リスポーンしてなかったら入れる
		if(!i.get()->GetParameter().isRespawn)
		players.push_back(dynamic_cast<Player*>(i.get()));
	}
	//最後の一人になってたら
	if (players.size() == 1) {
		PLAYER_NUMBER win = players.front()->GetParameter().playNumber;
		//勝ち数1プラス
		mWinCount[win] += 1;
		return win;
	}
	//勝負が終わってない
	return PLAYER_NUMBER::PLAYER_NULL;
}

std::vector<PLAYER_NUMBER> GamePlayManager::IsFinalWinPlayer()
{
	PLAYER_NUMBER win;
	int winCount=0;
	//引き分けの場合があるため
	std::vector<PLAYER_NUMBER>winPlayers;
	for (const auto& i : mWinCount) {
		//勝ってたら全部消してまた入れる
		if (winCount < i.second) {
			winPlayers.clear();
			winCount = i.second;
			winPlayers.push_back(i.first);
		}
		//同点の場合追加するだけ
		else if (winCount == i.second) {
			winPlayers.push_back(i.first);
		}
	}
	return winPlayers;
}

bool GamePlayManager::EndRaund()
{
	std::vector<Player*> players;
	for (const auto& i : mWorld.GetActors(ACTOR_ID::PLAYER_ACTOR)) {
		//リスポーンしてなかったら入れる
		if (!i.get()->GetParameter().isRespawn)
			players.push_back(dynamic_cast<Player*>(i.get()));
	}
	if (players.size() == 1 || players.size() == 0) {
		//ラウンド数をプラス
		mRaundCount++;
		return true;
	}
	return false;
}

bool GamePlayManager::TimeUp()
{
	float time = dynamic_cast<GameTimerUI*>(mWorld.GetUIActors(UI_ID::GAMETIMER_UI).front().get())->mGameTimer;
	if (time <= 0)
		return true;
	return false;
}

std::map<PLAYER_NUMBER, int> GamePlayManager::GetWinCount()
{
	return mWinCount;
}

int GamePlayManager::GetPlayNum()
{
	return mPlayerNum;
}

void GamePlayManager::SetPlayNum(int num)
{
	mPlayerNum = num;
}

void GamePlayManager::ResetWin()
{
	mWinCount.clear();
}
