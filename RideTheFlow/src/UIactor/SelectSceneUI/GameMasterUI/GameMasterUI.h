#pragma once
#include "../../UIActor.h"
#include <vector>

class AnimetionClass;
class MessageText;
class GameMasterUI : public UIActor
{
public:
	GameMasterUI(IWorld& world);
	~GameMasterUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
public:
	//���Ԗڂ𒝂点�邩
	void SetMasterText(int num);
	//���Ԗڂ𒝂��Ă��邩
	int GetMasterText();
private:
	//�e�L�X�g�̌��̂���摜���W
	Vector2 mTextBackPos;
	//�e�L�X�g���̉摜�T�C�Y
	Vector2 mTextBackSize;
	//���b�Z�[�W
	MessageText* mMessageText;
	//�Q�[���}�X�^�[���ǂ��𒝂��Ă��邩
	int mMessageCount;
	AnimetionClass* mGameMasterAnim;
};
