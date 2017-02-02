#pragma once
#include "../world/IWorld.h"
#include "../actor/ID.h"
#include <list>
#include <map>
class GamePlayManager {
public:
	GamePlayManager(IWorld& world);
	~GamePlayManager();
	//そのラウンドで勝ったプレイヤーを返す
	PLAYER_NUMBER IsWinPlayer();
	//勝った人を返す
	std::list<PLAYER_NUMBER> IsFinalWinPlayer();
	//最後の一人になったらtrueを返す
	bool EndRaund();
	//タイムアップの場合Trueを返す
	bool TimeUp();
	//勝ち数を返す
	std::map<PLAYER_NUMBER, int> GetWinCount();
	//プレイ人数を取得
	int GetPlayNum();
	//プレイ人数を設定
	void SetPlayNum(int num);
	//勝ち数をリセットする
	void ResetWin();
private:
	IWorld& mWorld;
	int mRaundCount;
	int mEndRaundCount;
	std::map<PLAYER_NUMBER, int> mWinCount;
	int mPlayerNum;

};