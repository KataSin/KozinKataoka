#pragma once
#include "../UIActor.h"
#include "../../actor/Player.h"
class TitleUI : public UIActor
{
public:
	enum SelectState
	{
		START,
		HELP,
		END
	};
	struct CursorState
	{
		//�J�[�\���\���̈ʒu
		Vector2 position;
		//�ǂ̏��
		SelectState state;
		//�摜ID
		SPRITE_ID id;
		//�摜�T�C�Y
		Vector2 textureSize;
		//���O���
		bool flag = false;
	};
public:
	TitleUI(IWorld& world);
	~TitleUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//�����擾
	std::vector<CursorState> GetCursorStates();
private:
	//���ݑI������Ă�����
	SelectState mSelectState;
	//�J�[�\�����d�˂�����̏��
	std::vector<CursorState> mStates;
	//���݂̃J�[�\���|�W�V����
	Vector3 mCursorPosition;
	Vector2 mCursorSize;
	//�J�[�\����Ԍn
	Vector3 mCursorVec;
	Vector3 mResCursorPos;
	//�{�^����������
	bool mIsPushButton;

	Vector2 mButtonStartSize;
	//�v�b�V���{�^���̃��l
	float mButtonAlpha;
	float mButtonAlphaCount;
	//���j���[�̃��l
	float mMenuAlpha;
};