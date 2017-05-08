#include "SelectScenePlayer.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../Collision.h"
#include "../../graphic/Model.h"
#include "../../graphic/AnimetionClass.h"
#include "../../time/Time.h"
SelectScenePlayer::SelectScenePlayer(IWorld& word, const Vector3& position, const MODEL_ID& player):
	Actor(world),
	mPosition(position-Vector3(500,0)),
	mStartPos(mPosition),
	mEndPos(position),
	mLerpCount(0.0f)
{
	//����łȂ���
	parameter.isDead = false;
	//�}�g���N�X����
	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(-90)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(position);
	//�A�j���[�V�����N���X�̐���
	mAnime = new AnimationClass(this, ANIMATION::PLAYER_RUN1_ANIM, player);
}

SelectScenePlayer::~SelectScenePlayer()
{
}

void SelectScenePlayer::Update()
{
	mLerpCount += Time::GetInstance().deltaTime();
	mPosition = Vector3::Lerp(mStartPos, mEndPos, mLerpCount);

	parameter.mat =
		Matrix4::Scale(1)*
		Matrix4::RotateX(0)*
		Matrix4::RotateY(-90)*
		Matrix4::RotateZ(0)*
		Matrix4::Translate(mPosition);
	//�A�j���[�V�����A�b�v�f�[�g
	mAnime->update();
}

void SelectScenePlayer::Draw() const
{
	//�A�j���[�V�����`��
	mAnime->draw();
}

void SelectScenePlayer::OnCollide(Actor & other, CollisionParameter colpara)
{
}
