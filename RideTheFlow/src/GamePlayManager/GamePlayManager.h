#pragma once
#include "../world/IWorld.h"
#include "../actor/ID.h"
#include <list>
#include <map>
class GamePlayManager {
public:
	GamePlayManager(IWorld& world);
	~GamePlayManager();
	//���̃��E���h�ŏ������v���C���[��Ԃ�
	PLAYER_NUMBER IsWinPlayer();
	//�������l��Ԃ�
	std::list<PLAYER_NUMBER> IsFinalWinPlayer();
	//�Ō�̈�l�ɂȂ�����true��Ԃ�
	bool EndRaund();
	//�^�C���A�b�v�̏ꍇTrue��Ԃ�
	bool TimeUp();
	//��������Ԃ�
	std::map<PLAYER_NUMBER, int> GetWinCount();
	//�v���C�l�����擾
	int GetPlayNum();
	//�v���C�l����ݒ�
	void SetPlayNum(int num);
	//�����������Z�b�g����
	void ResetWin();
private:
	IWorld& mWorld;
	int mRaundCount;
	int mEndRaundCount;
	std::map<PLAYER_NUMBER, int> mWinCount;
	int mPlayerNum;

};