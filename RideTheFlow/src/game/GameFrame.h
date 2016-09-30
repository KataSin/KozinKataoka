#pragma once

class GameFrame
{
public:
	GameFrame() = default;
	~GameFrame() = default;

	void Run();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
	virtual bool IsWait() const
	{
		return false;
	}

	bool IsEnd();

	///<summary>
	/// �Q�[�����I������
	///</summary>
	static void GameEnd();

private:
	static bool mIsEnd;

};