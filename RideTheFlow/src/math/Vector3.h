#pragma once

#include <Dxlib.h>
#include <string>

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3();
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(float s);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(float x, float y);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(float x, float y, float z);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(int s);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(int x, int y);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(int x, int y, int z);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(const Vector3& vector);
	///<summary>
	/// �R���X�g���N�^
	///</summary>
	Vector3(const VECTOR& vector);

public:
	///<summary>
	/// (0,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Zero;
	///<summary>
	/// (1,1,1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 One;
	///<summary>
	/// (0,1,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Up;
	///<summary>
	/// (0,-1,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Down;
	///<summary>
	/// (-1,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Left;
	///<summary>
	/// (1,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Right;
	///<summary>
	/// (0,0,-1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Forward;
	///<summary>
	/// (0,0,1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Backward;

	//�F
	static Vector3 White;
	static Vector3 Black;
	static Vector3 Blue;
	static Vector3 Red;
	static Vector3 Green;

public:
	///<summary>
	/// ���g�̃x�N�g���̑傫���i�����j��Ԃ�
	///</summary>
	float Length() const;
	///<summary>
	/// ���g�̃x�N�g���𐳋K������
	///</summary>
	void Normalize();
	///<summary>
	/// ���g�̐��K�����ꂽ�x�N�g����Ԃ�
	///</summary>
	Vector3 Normalized() const;

public:
	///<summary>
	/// �x�N�g���̑傫���i�����j��Ԃ�
	///</summary>
	static float Length(const Vector3& v);
	///<summary>
	/// �Q�_�Ԃ̋�����Ԃ�
	///</summary>
	static float Distance(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// �x�N�g���𐳋K�����ĕԂ�
	///</summary>
	static Vector3 Normalize(const Vector3& v);
	///<summary>
	/// �Q�̃x�N�g���̓��ς�Ԃ�
	///</summary>
	static float Dot(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// �Q�̃x�N�g���̊O�ς�Ԃ�
	///</summary>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// �Q�̃x�N�g���̂Ȃ��p��Ԃ�
	///</summary>
	static float Inner(const Vector3& v1, const Vector3& v2);
	///<summary>
	/// �O�̃x�N�g����Ԃ�(���W�A��]��)
	///</summary>
	static Vector3 FrontVec(Vector3& position, Vector3& rotation);
	///<summary>
	/// ��̃x�N�g���Ԃ̐��`��Ԃ�����
	///</summary>
	static Vector3 Lerp(const Vector3& start, const Vector3& end, float amount);
	///<summary>
	/// �o�l�̗͂�������(���݂̈ʒu,�o�l�̌��݂̈ړ����x,�o�l�̐Î~�ʒu,�o�l�萔,�o�l�̋���,���C��,����)
	///</summary>
	static void Spring(Vector3& position, Vector3& velocity, const Vector3& restPosition, float stiffness, float friction, float mass);
	///<summary>
	/// �s�b�`�����߁A���W�A���ŕԂ�
	///</summary>
	static float Pitch(const Vector3& front);
	///<summary>
	/// ���[�����߁A���W�A���ŕԂ�
	///</summary>
	static float Yaw(const Vector3& front);
	///<summary>
	/// ���W������W�֌������P�ʃx�N�g����Ԃ�
	///</summary>
	static Vector3 Direction(const Vector3& start, const Vector3& end);

public:
	///<summary>
	/// Vector3�^��VECTOR�^�ɕϊ����ĕԂ�
	///</summary>
	static VECTOR ToVECTOR(const Vector3& v);
	///<summary>
	/// ���g��VECTOR�^�ɕϊ��������̂�Ԃ�
	///</summary>
	VECTOR ToVECTOR() const;
	///<summary>
	/// Vector3�^��DWORD�^�ɕϊ��������̂�Ԃ�
	///</summary>
	static DWORD ToColor(const Vector3& v);
	///<summary>
	/// ���g��DWORD�^�ɕϊ��������̂�Ԃ�
	///</summary>
	DWORD ToColor() const;

public:
	Vector3& operator = (const Vector3& v);
	Vector3& operator = (const VECTOR& v);
	operator std::string() const;
	operator VECTOR() const;
};

Vector3 operator + (const Vector3& v1, const Vector3& v2);
Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3 operator - (const Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3 operator * (const Vector3& v, const float f);
Vector3 operator * (const float f, const Vector3& v);
Vector3 operator * (const Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, const float f);
Vector3& operator *= (const float f, Vector3& v);
Vector3 operator / (const Vector3& v, const float f);
Vector3 operator / (const float f, const Vector3& v);
Vector3 operator / (const Vector3& v1, const Vector3& v2);
Vector3& operator /= (Vector3& v, const float f);
Vector3 operator - (const Vector3& v);
bool operator != (const Vector3& v1, const Vector3& v2);

VECTOR& operator += (const VECTOR& v1, const Vector3& v2);