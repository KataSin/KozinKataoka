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
	//�\�����錋�ʂ�ݒ�
	switch (winPlayer)
	{
	case PLAYER_NUMBER::PLAYER_1: {
		mWinTexId = SPRITE_ID::KEKKA1_SPRITE;
		break;
	}
	case PLAYER_NUMBER::PLAYER_2: {
		mWinTexId = SPRITE_ID::KEKKA2_SPRITE;

		break;
	}
	case PLAYER_NUMBER::PLAYER_3: {
		mWinTexId = SPRITE_ID::KEKKA3_SPRITE;
		break;
	}
	case PLAYER_NUMBER::PLAYER_4: {
		mWinTexId = SPRITE_ID::KEKKA4_SPRITE;
		break;
	}
	}

	mTexSize = Sprite::GetInstance().GetSize(mWinTexId);
	mTrophyAllPos = (Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2 - mTexSize / 2) + Vector2(128, 90);
	mTrophyPos = Vector2(mWinCount[mWinPlayer] * 32, (int)mWinPlayer * 35) - Vector2(16, 16);

	//��̏�����
	std::map<SPRITE_ID, SPRITE_ID> kao1;
	kao1[SPRITE_ID::PLAYER1_KAO_E] = SPRITE_ID::PLAYER1_KAO_M;
	std::map<SPRITE_ID, SPRITE_ID> kao2;
	kao2[SPRITE_ID::PLAYER2_KAO_E] = SPRITE_ID::PLAYER2_KAO_M;
	std::map<SPRITE_ID, SPRITE_ID> kao3;
	kao3[SPRITE_ID::PLAYER3_KAO_E] = SPRITE_ID::PLAYER3_KAO_M;
	std::map<SPRITE_ID, SPRITE_ID> kao4;
	kao4[SPRITE_ID::PLAYER4_KAO_E] = SPRITE_ID::PLAYER4_KAO_M;
	mKaos[PLAYER_NUMBER::PLAYER_1] = kao1;
	mKaos[PLAYER_NUMBER::PLAYER_2] = kao2;
	//�v���C�l���ɂ���ĕς���
	if (world.GetPlayerNum() == 2)return;
	mKaos[PLAYER_NUMBER::PLAYER_3] = kao3;
	if (world.GetPlayerNum() == 3) return;
	mKaos[PLAYER_NUMBER::PLAYER_4] = kao4;
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
	Sprite::GetInstance().Draw(mWinTexId, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) / 2, mTexSize / 2, mAlpha, Vector2(mAlpha), true, false);
	//�������l�͌�Ńg���t�B�[��������̂ŏ�����-1�ɂ��Ă���
	for (const auto& i : mWinCount) {
		int loop = i.second;
		if (i.first == mWinPlayer) loop--;
		for (int j = 0; j < loop; j++) {
			Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + Vector2(j * 32, ((int)i.first - 1) * 36));
		}
	}
	//������g���t�B�[�\��
	Sprite::GetInstance().Draw(SPRITE_ID::TROPHY_SPRITE, mTrophyAllPos + mTrophyPos, Vector2(16, 16), mTrophyAlpha, Vector2(mSize), 0, true, false);

	for (const auto& i : mKaos) {
		SPRITE_ID id = i.second.begin()->second;
		if (mWinPlayer == i.first) id = i.second.begin()->first;
		Sprite::GetInstance().Draw(id, mTrophyAllPos + Vector2(-32, ((int)i.first - 1) * 35));
	}
}
