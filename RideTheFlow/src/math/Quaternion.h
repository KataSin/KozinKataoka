#pragma once

#include "Vector3.h"
#include "Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Quaternion(const Vector3& v, float angle);
	///<summary>
	/// �R���X�g���N�^(��]�s�񂩂�N�E�H�[�^�j�I�����쐬)
	///</summary>
	Quaternion(const Matrix4& m);

public:
	///<summary>
	/// ���ς�Ԃ�
	///</summary>
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	///<summary>
	/// �傫���i�����j��Ԃ�
	///</summary>
	static float Length(const Quaternion& q);
	///<summary>
	/// ���K��������
	///</summary>
	static Quaternion Normalize(const Quaternion& q);
	///<summary>
	/// ���ʐ��`���
	///</summary>
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
	///<summary>
	/// �N�H�[�^�j�I������]�s��ɂ��ĕԂ�
	///</summary>
	static Matrix4 Rotate(const Quaternion& q);
	///<summary>
	/// �C�ӎ�����̉�]�s���Ԃ�
	///</summary>
	static Matrix4 RotateAxis(const Vector3& v, float angle);
};

// �P�����Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);
// ������Z�q�I�[�o�[���[�h
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);
// �Q�����Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);