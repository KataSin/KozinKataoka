#pragma once

class Time
{
public:
	Time();

	///<summary>
	/// �X�V����
	///</summary>
	void Update();

	///<summary>
	/// �O�t���[���ƍ��t���[���̎��ԍ�
	///</summary>
	static float DeltaTime;

private:
	int savetime;// �O�t���[���̎��Ԃ�ۑ�
};