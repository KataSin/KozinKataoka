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
	//�u�����h��
	float animBlend = 0.0f;
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
	void addAnim(ANIMATION anim);
	//�A�j���[�V�����f�^�b�`
	void deleteAnim(ANIMATION anim);
	//�����Ă���Ƃ��̃A�j���[�V�����u�����h(�v���C���[�̑��x)
	void runAnimationBlend(Vector3 velocity);
	//���ݍĐ����̃��[�V����
	int getMotion() const;
	//�{�[������Ԃ�
	int getBoneCount() const;
	//�I�����Ԃ�Ԃ�
	int getEndTime() const;

private:
	//�A�j���[�V����������MODELID
	int mModel;
	//���݂̃A�j���[�V����
	ANIMATION mAnimation;
	//�O��̃A�j���[�V����
	ANIMATION mPreAnimation;
	//�A�j���[�V�����A�^�b�`�ԍ�
	int mAtatti;
	//�A�^�b�`���
	std::map<ANIMATION, AnimationState> attachAnimes;
	//�A�N�^�[���
	Actor* mActor;

	//�u�����h�e�X�g
	float blendNum;
};

