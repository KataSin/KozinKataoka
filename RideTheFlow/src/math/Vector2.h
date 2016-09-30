#pragma once

#include <Dxlib.h>
#include <string>
class Point;

class Vector2
{
public:
	float x;
	float y;
public:
	/// <summary>
	/// (0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Zero;
	/// <summary>
	/// (1, 1)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 One;
	/// <summary>
	/// (-1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Left;
	/// <summary>
	/// (1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Right;
	/// <summary>
	/// (0, -1)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Up;
	/// <summary>
	/// (0, 1)�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Down;
	/// <summary>
	/// ��ʒ����̍��W�ŏ��������ꂽ�x�N�g����Ԃ�
	/// </summary>
	static Vector2 Center();
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(float x, float y);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(int x, int y);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(const Vector2& vec);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(const VECTOR& vec);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(float s);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Vector2(int s);
public:
	/// <summary>
	/// ���g�̃x�N�g���̑傫���i�����j��Ԃ�
	/// </summary>
	float Length() const;
	/// <summary>
	/// ���g�̃x�N�g���̑傫���i�����j�̓���Ԃ�
	/// </summary>
	float LengthPow2() const;
	/// <summary>
	/// �Q�_�Ԃ̋�����Ԃ�
	/// </summary>
	float Distance(const Vector2& other) const;
	/// <summary>
	/// �Q�_�Ԃ̋����̓���Ԃ�
	/// </summary>
	float DistancePow2(const Vector2& other) const;
	/// <summary>
	/// ���g�̃x�N�g���𐳋K������
	/// </summary>
	void Normalize();
	/// <summary>
	/// ���g�̐��K�����ꂽ�x�N�g����Ԃ�
	/// </summary>
	Vector2 Normalized() const;
	/// <summary>
	/// ���g�Ƒ���̃x�N�g���̓��ς�Ԃ�
	/// </summary>
	float Dot(const Vector2& v) const;
	/// <summary>
	/// ���g�Ƒ���̃x�N�g���̂Ȃ��p��Ԃ�
	/// </summary>
	float Inner(const Vector2& v) const;
public:
	/// <summary>
	/// �x�N�g���𐳋K������
	/// </summary>
	static Vector2 Normalize(const Vector2& v);
	/// <summary>
	/// �Q�_�Ԃ̋�����Ԃ�
	/// </summary>
	static float Distance(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// �Q�_�Ԃ̋����̓���Ԃ�
	/// </summary>
	static float DistancePow2(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// �Q�̃x�N�g���̓��ς�Ԃ�
	/// </summary>
	static float Dot(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// �Q�̃x�N�g���̂Ȃ��p��Ԃ�
	/// </summary>
	static float Inner(const Vector2& v1, const Vector2& v2);
	/// <summary>
	/// ��̃x�N�g���̊O�ς�Ԃ�
	/// </summary>
	static float Cross(const Vector2& v1, const Vector2& v2);
	///<summary>
	/// ��̃x�N�g���Ԃ̐��`��Ԃ���
	///</summary>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float amount);
	
public:
	///<summary>
	/// Vector2�^��Point�^�ɕϊ����ĕԂ�
	///</summary>
	static Point ToPoint(const Vector2& v);
	///<summary>
	/// ���g��VECTOR�^�ɕϊ��������̂�Ԃ�
	///</summary>
	Point ToPoint() const;

public:
	Vector2& operator = (const Vector2& v);
	operator std::string() const;
};

Vector2 operator + (const Vector2& v1, const Vector2& v2);
Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2 operator - (const Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2 operator * (const Vector2& v, const float f);
Vector2 operator * (const float f, const Vector2& v);
Vector2& operator *= (Vector2& v, const float f);
Vector2& operator *= (const float f, Vector2& v);
Vector2 operator / (const Vector2& v, const float f);
Vector2 operator / (const float f, const Vector2& v);
Vector2& operator /= (Vector2& v, const float f);
Vector2 operator - (const Vector2& v);