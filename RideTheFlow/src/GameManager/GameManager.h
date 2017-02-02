#pragma once
#include "../actor/ID.h"
#include <list>
class GameManager
{
public:
	GameManager();
	~GameManager();
	//プレイヤーのランクをセット
	void SetPlayerRank(std::list<PLAYER_NUMBER> playerRank);
	//プレイヤーのランクを取得
	std::list<PLAYER_NUMBER> GetPlayerRank();
	//プレイヤーの勝ちを初期化
	void Initialize();
	//ラウンド数を取得
	int GetRaundCount();
	//ラウンド数を設定
	void SetRaundCount(int raundCount);
	//プレイする人数を設定
	void SetPlayerNum(int num);
	//プレイする人数を取得
	int GetPlayerNum();

private:
	std::list<PLAYER_NUMBER> mPlayerRank;
	int mRaund;
	int mPlayerNum;
};