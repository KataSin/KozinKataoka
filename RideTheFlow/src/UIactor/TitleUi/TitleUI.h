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
	};
public:
	TitleUI(IWorld& world);
	~TitleUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

private:
	//���ݑI������Ă�����
	SelectState mSelectState;
	//�J�[�\�����d�˂�����̏��
	std::vector<CursorState> mStates;
	//���݂̃J�[�\���|�W�V����
	Vector2 mCursorPosition;
};