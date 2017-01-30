#pragma once
#include "../UIActor.h"
#include "../../actor/PlayerAttack/PlayerAttackManager/PlayerAttackManager.h"
#include "../../actor/Player.h"
#include <map>
#include "../../actor/ID.h"
class GamePlayFontUI : public UIActor
{
	struct FontState
	{
		//���l
		float mAlpha=0.0f;
		//�T�C�Y
		float mScale=0.0f;
		//�J�E���g
		float mCount=0.0f;
		//�ǂ̂��炢�\�������邩
		float mFontTime = 0.0f;
		//�����ƕ\�����邩�ǂ���
		bool mFlag=false;
	};
public:
	GamePlayFontUI(IWorld& world);
	~GamePlayFontUI();
	virtual void Update(PLAYER_NUMBER playerNumber) override;
	virtual void Draw() const override;

public:

	//�t�H���g���\�����I����������擾
	bool GetEndFont(const SPRITE_ID& font);
	//�t�H���g�̍Đ����X�^�[�g
	void StartFont(const SPRITE_ID& font,float timer=15.0f, bool flag=false);
private:
	//�t�H���gmap
	std::map<SPRITE_ID, FontState> mFonts;

};