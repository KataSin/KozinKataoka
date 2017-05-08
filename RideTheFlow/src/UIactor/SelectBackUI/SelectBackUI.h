#pragma once
#include "../UIActor.h"
#include <vector>

enum BackUiMove {
	UIMOVE_START,
	UIMOVE_END,
	UIMOVE_STOP
};
class SelectBackUI : public UIActor
{
public:
	SelectBackUI(IWorld& world);
	~SelectBackUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//�ړ�������id�ύX
	void SetSpriteID(const SPRITE_ID& id);
	//�ǂ̈ړ��������邩
	void SetMove(const BackUiMove& state);
	//�ԍ������
	void SetNumber(int num);
private:
	//SpriteID
	SPRITE_ID mId;
	//���݂̈ړ����
	BackUiMove mMove;
	//�X�P�[��
	float mScale;


	//��ԗp�^�C��
	float mLerpTimer;
	//�s���悤���
	Vector2 mStartStartPos;
	Vector2 mStartEndPos;
	//�A��悤���
	Vector2 mEndStartPos;
	Vector2 mEndEndPos;
	//�\�����鐔��
	int mNum;
};
