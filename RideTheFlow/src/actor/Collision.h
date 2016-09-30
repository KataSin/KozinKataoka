#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"
#include "../actor/Actor.h"

//�����蔻��̃p�����[�^
struct CollisionParameter{
	bool		colFlag	= false;				//���������ǂ����̃t���O		//�G����̍U���i㩁j���H
	bool        colAll = false;
	int			colID;
	Vector3		colPos = Vector3::Zero;			// ���������|�W�V����
	Vector3		colVelosity = Vector3::Zero;
};

// ����
struct Line{
	Vector3 startPos	= Vector3::Zero;	// �n�_
	Vector3 endPos		= Vector3::Zero;	// �I�_
};
// ��
struct Box{
	Vector3 min	= Vector3::Zero;			// ���̒��_
	Vector3 max = Vector3::Zero;			// ���̑Ίp�ɂ��钸�_
};
// ��
struct Sphere{
	Vector3	position = Vector3::Zero;	// ���̈ʒu
	float	radius = 0;					// ���̔��a
};
// �J�v�Z��
struct  Capsule{
	Vector3	startPos	= Vector3::Zero;	// �J�v�Z���̎n�_
	Vector3 endPos		= Vector3::Zero;	// �J�v�Z���̏I�_
	float	radius		= 0;				// ���a
};
// ���f��
struct ModelData{
	int		MHandle		= 0;
	int		MFrameIndex	= -1;
};

class Collisin{
	public:
	static Collisin &GetInstace(){
		static Collisin c;
		return c;
	}

	// ���Ɣ��̓����蔻��
	CollisionParameter SegmentBoxAABB(const Line& line, const Box& box) const;
	// ���Ƌ��̓����蔻��
	CollisionParameter SegmentSphere(const Line& line, const Sphere& s) const;

	// ���Ƌ��̂����蔻��
	CollisionParameter SphereSphere(const Sphere& s1, const Sphere& s2) const;
	// ���ƃJ�v�Z���̓����蔻��
	CollisionParameter SphereCapsule(const Sphere& s, const Capsule& c) const;

	// �J�v�Z���ƃJ�v�Z���̓����蔻��
	CollisionParameter CapsuleCapsule(const Capsule& c1, const Capsule& c2) const;
	// �J�v�Z���Ɠ_�̓����蔻��
	CollisionParameter CapsulePoint(const Capsule& c, const Vector3& p) const;
	// �J�v�Z����AABB�̓����蔻��
	//CollisionParameter CapsuleAABBSegment(const Actor& other)const;

	// ���f���Ɛ����̓����蔻��
	CollisionParameter ModelLine(const ModelData& model, const Line& line) const;
	// ���f���Ƌ��̓����蔻��
	CollisionParameter ModelSphere(const ModelData& model, const Sphere& s) const;
	// ���f���ƃJ�v�Z���̓����蔻��
	CollisionParameter ModelCapsule(const ModelData& model, const Capsule& c) const;

	// �~���Ɣ��̓����蔻��
	//CollisionParameter CylinderBox(const Actor& other)const;

	//
	CollisionParameter PushedBack_SphereCapsule(const Sphere& s, const Capsule& c) const;
	//
	Vector3 PushedBack_CapsuleCapsule(const Capsule& c1, const Capsule& c2) const;

	CollisionParameter PushedBack_SphereSphere(const Sphere& s1, const Sphere& s2) const;
};
