#pragma once

#include "ISceneMediator.h"

#include"IScenePtr.h"
#include <unordered_map>
#include "../UIactor/UIActorPtr.h"
#include "../world/World.h"
enum class Scene;

class SceneManager : public ISceneMediator{
public:
	static const int MaxStageCount;

public:
	//�R���X�g���N�^
	SceneManager();
	//�X�V�O������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�I��������
	void End();

	void Change();

	//�V�[���̒ǉ�
	void Add(Scene name, const IScenePtr& scene);
	void SetScene(Scene name);
	template<typename T, typename... Args> 
	void Add(Scene name, Args&&... arg)
	{
		Add(name, std::make_shared<T>(arg...));
	}
	//�V�[���̕ύX
	virtual void Change(Scene name) override;
	// ���������w�肷��
	virtual void Init(Scene name) override;
	// �I���������w�肷��
	virtual void Final(Scene name) override;

	virtual int GetStageCount() const override
	{
		return mStageCount;
	}
	virtual void SetStageCount(int n) override;

	virtual void SetChangeUi()override;

	__declspec(property(get = GetStageCount, put = SetStageCount)) int StageCount;

	virtual bool GetEndFlag()override;
	//���̃V�[���Ɉڍs���邽�߂̐ݒ�
	void ChangeSceneSet(Scene scene);
private:
	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;
private:
	//�V�[��
	std::unordered_map<Scene, IScenePtr> mScenes;
	//���݂̃V�[��
	IScenePtr mCurrentScene;
	int mStageCount;

	//�V�[���`�F���W�p��world
	World wo;
	UIActorPtr mChangeUi;

	const float SCENE_END_TIME = 60.0f * 3;

	//�Q�[�����̏I�������
	bool mIsGameEnd;
};
