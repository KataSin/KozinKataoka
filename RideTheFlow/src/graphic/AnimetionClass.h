#pragma once
#include "../math/Matrix4.h"
#include "../actor/ID.h"
#include <map>
#include "../actor/Actor.h"
struct AnimationState {
	//�C���f�b�N�X�ԍ�
	int index;
	//�A�j���[�V�����I������
	float animEndTime;
	//�A�j���[�V��������
	float animTimer = 0.0f;
	//�Đ����Ă��邩
	bool animetionFlag = true;
};
class AnimationClass
{
public:
	//�R���X�g���N�^
	AnimationClass(Actor* actor, ANIMATION startAnim, MODEL_ID model);
	~AnimationClass();
	//�X�V
	void update();
	//�`��
	void draw();
	//�A�j���[�V�����̕ύX
	void changeAnim(ANIMATION anim);
	//�A�j���[�V�����A�^�b�`
	void AttachAnim(ANIMATION anim);
	//�A�j���[�V�����f�^�b�`
	void DetachAnim(ANIMATION anim);
	//�u�����h
	void AnimeBlend();

private:
	//�A�j���[�V����������MODELID
	int mModel;
	//���݂̃A�j���[�V����
	ANIMATION mCurAnimation;
	//�O��̃A�j���[�V����
	ANIMATION mPreAnimation;
	//�A�^�b�`���
	std::map<ANIMATION, AnimationState> attachAnimes;
	//�A�N�^�[���
	Actor* mActor;
	//�u�����h����
	float blendTime;
	//�u�����h���Ă��܂�
	bool blendFlag;


	int test;
	float testTimer;

	int indexa;
	int indexRun;
	int indexIdle;
};

