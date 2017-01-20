#include "ResultUI.h"
#include "../../Def.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
ResultUI::ResultUI(IWorld & world, GamePlayManager & gamePlayManager, PLAYER_NUMBER winPlayer) :
	UIActor(world),
	mAlpha(0.0f),
	mSize(1.5f),
	mTrophyAlpha(0.0f)
{
	parameter.isDead = false;
	//�����Ń��U���g�������������l�����
	mWinPlayer = winPlayer;
	mWinCount = gamePlayManager.GetWinCount();
	mTexSize = Sprite::GetInstance().GetSize(SPRITE_ID::KEKKA_SPRITE);
	mTrophyAllPos = (Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2 - mTexSize / 2)+Vector2(128,96);
	mTrophyPos = Vector2(mWinCount[mWinPlayer] * 32, (int)mWinPlayer * 32)-Vector2(16,16);
}

ResultUI::~ResultUI()
{
}

void ResultUI::Update(PLAYER_NUMBER playerNumber)
{
	//���ʂ̃��𑫂��Ă�
	mAlpha += Time::DeltaTime;
	//�N�����v
	mAlpha = Math::Clamp(mAlpha, 0.0f, 1.0f);
	//���ʂ��\�����I�������g���t�B�[��������
	if (mAlpha >= 1.0f) {
		mTrophyAlpha += 0.3f*Time::DeltaTime;
		mSize = Math::Lerp(1.5f, 1.0f, mTrophyAlpha);
	}

}

void ResultUI::Draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::KEKKA_SPRITE, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2, mTexSize / 2, mAlpha, Vector2(mAlpha), true, false);
	//�������l�͌�Ńg���t�B�[��������̂ŏ�����-1�ɂ��Ă���
	for (const auto& i : mWinCount) {
		int loop = i.second;
		if (i.first == mWinPlayer) loop--;
		for (int j = 0; j < loop; j++) {
			Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + Vector2(j * 32, ((int)i.first - 1) * 32));
		}
	}
	//������g���t�B�[�\��
	Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + mTrophyPos,Vector2(16,16),mTrophyAlpha,Vector2(mSize),0,true,false);

}
