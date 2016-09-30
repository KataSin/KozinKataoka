#pragma once

#include <Dxlib.h>
#include "Vector3.h"
#include "Vector4.h"
#include <string>

class Matrix4
{
public:
	float m[4][4];

public:
	/// <summary>
	/// �[���s���Ԃ�
	/// </summary>
	static Matrix4 Zero;
	/// <summary>
	/// �P�ʍs���Ԃ�
	/// </summary>
	static Matrix4 Identity;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix4();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix4(
		float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Matrix4(Vector3 scale, float rotateX, float rotateY, float rotateZ, Vector3 pos);

public:
	/// <summary>
	/// ���g�̍��W��Ԃ�
	/// </summary>
	Vector3 GetPosition() const;
	/// <summary>
	/// ���g�̉���Ԃ�
	/// </summary>
	Vector3 GetLeft() const;
	/// <summary>
	/// ���g�̏��Ԃ�
	/// </summary>
	Vector3 GetUp() const;
	/// <summary>
	/// ���g�̑O��Ԃ�
	/// </summary>
	Vector3 GetFront() const;
	/// <summary>
	/// ���g�̃X�P�[����Ԃ�
	/// </summary>
	Vector3 GetScale() const;
	/// <summary>
	/// ���g�̊e���̉�]�ʂ����W�A���ŕԂ�
	/// </summary>
	Vector3 GetRotate() const;
	/// <summary>
	/// ���g�̊e���̉�]�ʂ��p�x�ŕԂ�
	/// </summary>
	Vector3 GetRotateDegree() const;
	/// <summary>
	/// ���W���Z�b�g����
	/// </summary>
	void SetPosition(const Vector3& position);
	/// <summary>
	/// �����Z�b�g����
	/// </summary>
	void SetLeft(const Vector3& left);
	/// <summary>
	/// ����Z�b�g����
	/// </summary>
	void SetUp(const Vector3& up);
	/// <summary>
	/// �O���Z�b�g����
	/// </summary>
	void SetFront(const Vector3& front);

public:
	/// <summary>
	/// �g��k���s��
	/// </summary>
	static Matrix4 Scale(const Vector3& s);
	/// <summary>
	/// ��]�s��X
	/// </summary>
	static Matrix4 RotateX(float angle);
	/// <summary>
	/// ��]�s��Y
	/// </summary>
	static Matrix4 RotateY(float angle);
	/// <summary>
	/// ��]�s��Z
	/// </summary>
	static Matrix4 RotateZ(float angle);
	/// <summary>
	/// ���s�ړ��s��
	/// </summary>
	static Matrix4 Translate(const Vector3& pos);
	/// <summary>
	/// �}�g���b�N�X���쐬���� �X�P�[���@X���@Y���@Z���@�ړ���
	/// </summary>
	static Matrix4 CreateMatrix(const Vector3& s = Vector3::One, const float& rototeXangle = 0, const float& rotateYangle = 0, const float& rotateZangle = 0, const Vector3& pos = Vector3::Zero);
	/// <summary>
	/// �}�g���b�N�X���쐬����
	/// </summary>
	static Matrix4 CreateMatrix(const Matrix4& scale_ = Identity, const Matrix4& rotateX_ = Identity, const Matrix4& rotateY_ = Identity, const Matrix4& rotateZ_ = Identity, const Matrix4& translate_ = Identity);
	/// <summary>
	/// ���W�ϊ�(�x�N�g���ƍs��̐�)
	/// </summary>
	static Vector3 Transform(const Vector3& v, const Matrix4& m);
	/// <summary>
	/// ���W�ϊ�(��]�̂�)
	/// </summary>
	static Vector3 TransformRotateOnly(const Vector3& v, const Matrix4& m);
	/// <summary>
	/// �]�u�s��
	/// </summary>
	static Matrix4 Transpose(const Matrix4& m);
	static Matrix4 TransposeRotateOnly(const Matrix4& m);
	/// <summary>
	/// �t�s��(�g�k����)
	/// </summary>
	static Matrix4 InverseFast(const Matrix4& m);
	/// <summary>
	/// �t�s��
	/// </summary>
	static Matrix4 Inverse(const Matrix4& m);

public:
	/// <summary>
	/// ����ϊ��s��
	/// </summary>
	static Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
	/// <summary>
	/// �����ϊ��s����쐬����
	/// </summary>
	static Matrix4 Perspective(float fov, float aspect, float zn, float zf);
	/// <summary>
	/// �X�N���[�����W�ϊ��s����쐬����
	/// </summary>
	static Matrix4 Screen(float x, float y, float width, float height);

public:
	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	static Vector3 GetPosition(const Matrix4& m);
	/// <summary>
	/// ����Ԃ�
	/// </summary>
	static Vector3 GetLeft(const Matrix4& m);
	/// <summary>
	/// ���Ԃ�
	/// </summary>
	static Vector3 GetUp(const Matrix4& m);
	/// <summary>
	/// �O��Ԃ�
	/// </summary>
	static Vector3 GetFront(const Matrix4& m);
	/// <summary>
	/// �X�P�[����Ԃ�
	/// </summary>
	static Vector3 GetScale(const Matrix4& m);
	/// <summary>
	/// �e���̉�]�ʂ����W�A���Ԃ�
	/// </summary>
	static Vector3 GetRotate(const Matrix4& m);
	/// <summary>
	/// �e���̉�]�ʂ��p�x�ŕԂ�
	/// </summary>
	static Vector3 GetRotateDegree(const Matrix4& m);
	/// <summary>
	/// ���W���Z�b�g�����s���Ԃ�
	/// </summary>
	static Matrix4 SetPosition(Matrix4& m, const Vector3& position);
	/// <summary>
	/// �����Z�b�g�����s���Ԃ�
	/// </summary>
	static Matrix4 SetLeft(Matrix4& m, const Vector3& left);
	/// <summary>
	/// ����Z�b�g�����s���Ԃ�
	/// </summary>
	static Matrix4 SetUp(Matrix4& m, const Vector3& up);
	/// <summary>
	/// �O���Z�b�g�����s���Ԃ�
	/// </summary>
	static Matrix4 SetFront(Matrix4& m, const Vector3& front);
	/// <summary>
	/// ���ʐ��`���
	/// </summary>
	static Matrix4 Slerp(const Matrix4& start, const Matrix4& end, float t);
	/// <summary>
	/// ���`���
	/// </summary>
	static Matrix4 Lerp(const Matrix4& start, const Matrix4& end, float t);
	/// <summary>
	/// �s�b�`�p(���E���A�㉺������]��)�����߂�
	/// </summary>
	static float Pitch(const Matrix4& m);
	/// <summary>
	/// ���[�p(�㉺���A�O�������]��)�����߂�
	/// </summary>
	static float Yaw(const Matrix4& m);
	/// <summary>
	/// ���[���p(�O�㎲�A���E������]��)�����߂�
	/// </summary>
	static float Roll(const Matrix4& m);

	/// <summary>
	/// �X�N���[���ϊ�
	/// </summary>
	static Vector3 Project(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);
	/// <summary>
	/// ��ʂ̍��W���烍�[�J�����W�����߂�
	/// </summary>
	static Vector3 UnProject(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);
	/// <summary>
	/// ��]�s��̐��K��
	/// </summary>
	static Matrix4 NormalizeRotate(const Matrix4& m);

public:
	///<summary>
	/// Matrix4�^��MATRIX�^�ɕϊ����ĕԂ�
	///</summary>
	static MATRIX ToMATRIX(const Matrix4& m);
	///<summary>
	/// ���g��MATRIX�^�ɕϊ��������̂�Ԃ�
	///</summary>
	MATRIX ToMATRIX() const;
	static Matrix4 ToMatrix4(const MATRIX& m);

public:
	Matrix4& operator = (const Matrix4& m_);
	operator std::string() const;
};

Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);
Matrix4 operator * (const Matrix4& m1, const Matrix4& m2);
Vector3 operator * (const Vector3& v, const Matrix4& m);