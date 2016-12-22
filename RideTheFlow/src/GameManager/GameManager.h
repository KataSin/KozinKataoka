#pragma once
#include "../world/IWorld.h"
#include "../actor/ID.h"
#include <vector>
#include <map>
class GameManager {
public:
	GameManager(IWorld& world);
	~GameManager();
	//そのラウンドで勝ったプレイヤーを返す
	PLAYER_NUMBER IsWinPlayer();
	//最終的な勝っているプレイヤーを返す
	std::vector<PLAYER_NUMBER> IsFinalWinPlayer();
	//最後の一人になったらtrueを返す
	bool EndRaund();
	//タイムアップの場合Trueを返す
	bool TimeUp();
	

private:
	IWorld& mWorld;
	std::map<PLAYER_NUMBER, int> mWinCount;

};