#pragma once

#include "../math/Vector3.h"
#include "../actor/ID.h"
class Camera
{
private:
	Camera() {};
	~Camera() = default;

public:
	static Camera &GetInstance(){
		static Camera c;
		return c;
	}

	///<summary>
	/// �J�����̎��_���W�֌W
	///</summary>
	class CPosition
	{
	private:
		Vector3 m_position;
	public:
		Vector3 Get() const { return m_position; }
		void Set(Vector3 position){ m_position = position; }
	};

	///<summary>
	/// �J�����̒����_���W�֌W
	///</summary>
	class CTarget
	{
	private:
		Vector3 m_target;

	public:
		Vector3 Get() const { return m_target; }
		void Set(Vector3 target){ m_target = target; }
	};

	///<summary>
	/// �J�����̏�����֌W
	///</summary>
	class CUp
	{
	private:
		Vector3 m_up;
	public:
		Vector3 Get() const { return m_up; }
		void Set(Vector3 up){ m_up = up; }
	};


	///<summary>
	/// �J�����̍X�V����
	///</summary>
	void Update();

	///<summary>
	/// �J�����̕`�拗����ݒ肷��i��O�����A�������j
	///</summary>
	void SetRange(float Near, float Far);

	///<summary>
	/// �J�����̉�]�p�x��ݒ肷��i���W�A������]�p�x�E������]�p�x�E�P���]�p�x�j
	///</summary>
	void SetRotation(Vector3 rotate);

	///<summary>
	/// �w�肵�����W���J�����̎��E�ɓ����Ă��邩�ۂ�
	///</summary>
	int IsCheckView(Vector3 position);

	///<summary>
	/// �J�����̎���p��ݒ肷��
	///</summary>
	void SetViewAngle(float degree);

	void Draw();
public:
	CPosition Position;// ���_�̍��W
	CTarget Target;	// �����_�̍��W
	CUp Up;			// �����
};