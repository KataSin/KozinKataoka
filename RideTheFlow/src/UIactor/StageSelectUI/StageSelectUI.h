#pragma once
#include "../UIActor.h"
#include "../../actor/Actor.h"
#include "../../actor/ActorPtr.h"
#include <vector>
class StageSelectUI :public UIActor
{
public:
	enum SelectState
	{
		BACK,
		PLAYER_NUM,
		RAUND,
		NEXT
	};
	struct CursorState
	{
		//�J�[�\���\���̈ʒu
		Vector2 position;
		//�ǂ̏��
		SelectState state;
		//�������
		int num = 0;
		//�t���O���
		bool flag = false;
	};
public:
	StageSelectUI(IWorld& world);
	~StageSelectUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//�����擾
	std::vector<CursorState> GetCursorStates();
private:
	//�v���C���[����
	std::vector<ActorPtr> mPlayers;
	//���ݑI������Ă�����
	SelectState mSelectState;
	//�J�[�\�����d�˂�����̏��
	std::vector<CursorState> mStates;
	//���݂̃J�[�\���|�W�V����
	Vector2 mCursorPosition;
	//���֍s����
	bool mIsNextFlag;
	//�߂邪
	bool mIsBackFlag;
	//�{�^���̒��S���W
	Vector2 mButtonSize;
	//�J�[�\��
	Vector2 mCursorSize;
	
	//�J�[�\����Ԍn
	Vector3 mCursorVec;
	Vector3 mResCursorPos;
};