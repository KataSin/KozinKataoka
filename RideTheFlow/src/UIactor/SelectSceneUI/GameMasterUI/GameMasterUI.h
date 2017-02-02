#pragma once
#include "../../UIActor.h"
#include <vector>

class GameMasterUI : public UIActor
{
	struct SpriteState
	{
		SPRITE_ID spriteID;
		Vector2 spriteSize;
		Vector2 position;
	};
public:
	GameMasterUI(IWorld& world);
	~GameMasterUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;
private:
	//�|�W�V����
	Vector2 mPosition;
	//�e�L�X�g�̏��
	std::vector<SpriteState> mTexs;
	//�ǂ̂��炢�e�L�X�g�����܂�����
	int texNum;
	//�e�L�X�g�}�b�N�X�T�C�Y
	int texMaxSize;

	SpriteState mTexBackUp;
	SpriteState mTexBack;
};
