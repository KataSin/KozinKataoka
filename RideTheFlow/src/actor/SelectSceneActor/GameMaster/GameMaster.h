#pragma once
#include "../../Actor.h"
#include "../../ID.h"
#include <memory>
#include "../../../GameManager/GameManager.h"
#include <vector>
class GameMasterUI;
class SelectBackUI;
class GameMaster :public Actor
{
public:
	GameMaster(IWorld& world,GameManager& manager);
	~GameMaster();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
public:
	//マスターの気が済んだか
	bool GetMasterIsEnd();
private:
	void PadSetUp();
	void AddPlayer(int size);
private:
	//スクリーン座標(Z座標は奥行き)
	Vector3 mScreenPos;
	//位置
	Vector3 mPosition;
	//マスターテキスト
	GameMasterUI* mMasterText;
	//ラウンド数
	int mRaund;
	//アニメーション

	//パッド入力フラグ
	bool mPlayer2Flag;
	bool mPlayer3Flag;
	bool mPlayer4Flag;
	//メッセージを流すことができるかどうか
	bool mTextSkipFlag;
	//表示しているメッセージ
	int mTextNum;
	//ゲームマスターのすべきことがすべて終わったかどうか
	bool mMasterIsEnd;
	//パッド情報
	std::vector<int>mPads;
	//ゲームマネージャー
	GameManager* mManager;
	//ラウンドとかのUI
	SelectBackUI* mBackUi;
};