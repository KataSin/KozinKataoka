#pragma once
#include "../actor/ID.h"
#include <vector>
class GameManager
{
public:
	GameManager();
	~GameManager();
	//プレイヤーのランクをセット
	void SetPlayerRank(std::vector<PLAYER_NUMBER> playerRank);
	//プレイヤーのランクを取得
	std::vector<PLAYER_NUMBER> GetPlayerRank();
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
	//何プレイヤーかセット（パッドセット）
	void SetPlayerPad(std::vector<int> pads);
	//何プレイヤーか取得（パッドゲット）
	std::vector<int> GetPlayerPad();

private:
	std::vector<PLAYER_NUMBER> mPlayerRank;
	std::vector<int>mPads;
	int mRaund;
	int mPlayerNum;
};