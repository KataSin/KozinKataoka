#include "Collision.h"
#include "../math/Math.h"

// ���Ɣ��̓����蔻��
CollisionParameter Collisin::SegmentBoxAABB(const Line& line, const Box& box) const {
	CollisionParameter colpara;
	HITRESULT_LINE result;

	result = HitCheck_Line_Cube(
		line.startPos.ToVECTOR(), line.endPos.ToVECTOR(), 
		box.min, box.max);
	if (result.HitFlag > 0) colpara.colFlag = true;
	colpara.colPos = result.Position;

	return colpara;
}
// ���Ƌ��̓����蔻��
CollisionParameter Collisin::SegmentSphere(const Line& line, const Sphere& s) const {
	CollisionParameter colpara;
	
	int result = HitCheck_Line_Sphere(
		line.startPos.ToVECTOR(), line.endPos.ToVECTOR(),
		s.position.ToVECTOR(), s.radius);
	if (result > 0) colpara.colFlag = true;
	
	return colpara;
}

// ���Ƌ��̂����蔻��
CollisionParameter Collisin::SphereSphere(const Sphere& s1, const Sphere& s2) const {
	CollisionParameter colpara;

	int result = HitCheck_Sphere_Sphere(
		s1.position.ToVECTOR(), s1.radius,
		s2.position.ToVECTOR(), s2.radius);
	if (result > 0) colpara.colFlag = true;

	return colpara;
}
// ���ƃJ�v�Z���̓����蔻��
CollisionParameter Collisin::SphereCapsule(const Sphere& s, const Capsule& c) const{
	CollisionParameter colpara;

	int result = HitCheck_Sphere_Capsule(
		s.position.ToVECTOR(), s.radius,
		c.startPos.ToVECTOR(), c.endPos.ToVECTOR(), c.radius);
	if (result > 0) colpara.colFlag = true;

	return colpara;
}

// �J�v�Z���ƃJ�v�Z���̓����蔻��
CollisionParameter Collisin::CapsuleCapsule(const Capsule& c1, const Capsule& c2) const{
	CollisionParameter colpara;

	int result = HitCheck_Capsule_Capsule(
		c1.startPos.ToVECTOR(), c1.endPos.ToVECTOR(), c1.radius,
		c2.startPos.ToVECTOR(), c2.endPos.ToVECTOR(), c2.radius);
	if (result > 0) colpara.colFlag = true;

	return colpara;
}
// �J�v�Z���Ɠ_�̓����蔻��
CollisionParameter Collisin::CapsulePoint(const Capsule& c, const Vector3& p) const{
	CollisionParameter colpara;

	float length = Segment_Point_MinLength(c.startPos.ToVECTOR(), c.endPos.ToVECTOR(), p);
	if (length <= c.radius) colpara.colFlag = true;

	return colpara;
}

// �J�v�Z����AABB�̓����蔻��	�i�J�v�Z���̔��a���ӂ̊Ԋu�������ꍇ�͖��� ��Tornado�̍������قږ����Ƃ���j
//CollisionParameter Collisin::CapsuleAABBSegment(const Actor& other)const
//{
//	CollisionParameter colpara;
//
//	/* CapsuleData */
//	Capsule c;
//	c.startPos = Matrix4::GetPosition(parameter.mat) * Vector3(1, 0, 1) - Vector3::Up * 100;
//	c.endPos = c.startPos + Matrix4::GetScale(parameter.mat) * Vector3::Up * 100;
//	c.radius = parameter.radius;
//
//	/* BoxData */
//	// ��2�������ē����蔻��̂����܂������Ă����i45�x��]��z��j
//	Vector3 min, max;
//	min = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1)) / 2 * sqrtf(2);
//	max = Matrix4::GetPosition(other.parameter.mat) + (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 2, 1)) / 2 * sqrtf(2);
//	Vector3 sideData[4];
//	sideData[0] = Vector3::Zero;
//	sideData[1] = Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 0) * sqrtf(2);
//	sideData[2] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 1, 0) * sqrtf(2);
//	sideData[3] = Matrix4::GetScale(other.parameter.mat) * Vector3(0, 0, 1) * sqrtf(2);
//
//	Vector3 v, v2;
//	float length;
//	for (int i = 1; i <= 3; i++)
//	{
//		v = max - sideData[i];
//
//		length =
//			Segment_Segment_MinLength(
//			c.startPos, c.endPos,
//			max, v);
//
//		if (length <= parameter.radius)
//		{
//			colpara.colFlag = true;
//			break;
//		}
//	}
//
//	if (!colpara.colFlag)
//	{
//		for (int i = 0; i <= 3; i++)
//		{
//			for (int j = 1; j <= 3; j++)
//			{
//				if (colpara.colFlag) break;
//
//				if (i != j)
//				{
//					v = min + sideData[i];
//					v2 = v + sideData[j];
//					length =
//						Segment_Segment_MinLength(
//						c.startPos, c.endPos,
//						v, v2);
//
//					if (length <= parameter.radius)
//						colpara.colFlag = true;
//				}
//			}
//		}
//	}
//
//	return colpara;
//}

// ���f���Ɛ����̓����蔻��
CollisionParameter Collisin::ModelLine(const ModelData& model, const Line& line) const{
	CollisionParameter colpara;
	MV1_COLL_RESULT_POLY HitPoly;

	HitPoly = MV1CollCheck_Line(
		model.MHandle, model.MFrameIndex,
		line.startPos.ToVECTOR(), line.endPos.ToVECTOR());
	if (HitPoly.HitFlag)
	{
		colpara.colFlag = true;
		colpara.colPos  = HitPoly.HitPosition;
		colpara.colVelosity = HitPoly.Normal;
	}
	return colpara;
}

// ���f���Ƌ��̓����蔻��
CollisionParameter Collisin::ModelSphere(const ModelData& model, const Sphere& s) const {
	CollisionParameter colpara;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;

	HitPolyDim = MV1CollCheck_Sphere(
		model.MHandle, model.MFrameIndex,
		s.position.ToVECTOR(), s.radius);
	if (HitPolyDim.HitNum >= 1){
		colpara.colPos = HitPolyDim.Dim[0].Normal;
		colpara.colFlag = true;
	}

	MV1CollResultPolyDimTerminate(HitPolyDim);
	return colpara;
}

// ���f���ƃJ�v�Z���̓����蔻��
CollisionParameter Collisin::ModelCapsule(const ModelData& model, const Capsule& c) const{
	CollisionParameter colpara;
	MV1_COLL_RESULT_POLY_DIM HitPolyDim;

	HitPolyDim = MV1CollCheck_Capsule(
		model.MHandle, model.MFrameIndex,
		c.startPos.ToVECTOR(), c.endPos.ToVECTOR(), c.radius);
	if (HitPolyDim.HitNum > 0) colpara.colFlag = true;

	MV1CollResultPolyDimTerminate(HitPolyDim);
	return colpara;
}

// �~���Ɣ��̓����蔻��
//CollisionParameter Collisin::CylinderBox(const Actor& other) const{
//	CollisionParameter colpara;
//
//	/* �~���f�[�^ */
//	// �~���̎��ƒ�ʂ̌�������Q�_
//	Vector3 TopPos = Matrix4::GetPosition(parameter.mat) + Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
//	Vector3 BottomPos = Matrix4::GetPosition(parameter.mat) - Matrix4::GetScale(parameter.mat) * Vector3(0.0f, 0.5f, 0.0f);
//	// �Q�_�Ԃ̃x�N�g��
//	float L = Vector3::Distance(TopPos, BottomPos);
//
//	/* ���f�[�^ */
//	// ���̑傫�����擾
//	Vector3 BoxScale = Matrix4::GetScale(other.parameter.mat);
//	// ��]�p���擾
//	Vector3 rotate = Matrix4::GetRotate(other.parameter.mat);
//	rotate = rotate * 180 / PI;
//
//	// ���̕��������Z�o
//	Vector3 split;
//	split.x = (int)(BoxScale.x / parameter.radius) + 1;
//	split.z = (int)(BoxScale.z / parameter.radius) + 1;
//	split.y = (int)(BoxScale.y / L) + 1;
//	if (split.x <= 1) split.x = 2;
//	if (split.y <= 1) split.y = 2;
//	if (split.z <= 1) split.z = 2;
//
//	// �ӂ̒�����ݒ�
//	Vector3 side;
//	side.x = BoxScale.x / split.x;
//	side.y = BoxScale.y / split.y;
//	side.z = BoxScale.z / split.z;
//
//	// ��_
//	//Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) / 2);						// �I�u�W�F�N�g�̒��S�iUnity�����j
//	Vector3 p = Matrix4::GetPosition(other.parameter.mat) - (Matrix4::GetScale(other.parameter.mat) * Vector3(1, 0, 1) / 2);	// ���f���̒�ʒ��S
//
//	// ���̓_�̕ۑ�
//	std::list<Vector3> points;
//	for (int z = 0; z <= split.z; z++)
//	{
//		for (int y = 0; y <= split.y; y++)
//		{
//			for (int x = 0; x <= split.x; x++)
//			{
//				if ((x == 0 || x == split.x) || (y == 0 || y == split.y) || (z == 0 || z == split.z))
//				{
//					Vector3 point = p + Vector3(side.x * x, side.y * y, side.z * z);
//
//					Vector3 aaa = point - Matrix4::GetPosition(other.parameter.mat);
//
//					// ���W�ϊ�
//					auto temp =
//						Matrix4::Translate(-aaa) *
//						Matrix4::RotateZ(rotate.z) *
//						Matrix4::RotateX(rotate.x) *
//						Matrix4::RotateY(rotate.y) *
//						Matrix4::Translate(Matrix4::GetPosition(other.parameter.mat));
//
//					points.push_back(Matrix4::GetPosition(temp));
//				}
//			}
//		}
//	}
//
//	// ���_�Ɖ~���̓����蔻��
//	for each (Vector3 p in points)
//	{
//		float S1 = Vector3::Distance(TopPos, p);
//		float S2 = Vector3::Distance(BottomPos, p);
//
//		float l = (S1 * S1 - L * L - S2 * S2) / (-2 * L);
//
//		if (!(l < 0.0f || l > L))
//		{
//			// ���a�Ɛ������r
//			auto qq = S2 * S2 - l * l;
//			if (qq <= parameter.radius * parameter.radius)	colpara.colFlag = true;
//		}
//	}
//
//	points.clear();
//	return colpara;
//}

// ���ƃJ�v�Z���̉����߂��i�J�v�Z���͐Î~�j
CollisionParameter Collisin::PushedBack_SphereCapsule(const Sphere& s, const Capsule& c) const{
	CollisionParameter colpara;
	colpara.colFlag = false;
	
	Vector3 v = c.endPos - c.startPos;
	Vector3 v1 = s.position - c.startPos;
	float t = Vector3::Dot(v, v1) / Vector3::Dot(v, v);
	float radius = s.radius + c.radius;
	float r2 = radius * radius;

	if (t < 0 && v1.Length() * v1.Length() <= r2)
	{
		Vector3 vr = Vector3::Normalize(v1) * radius;
		colpara.colPos = c.startPos + vr;
		colpara.colFlag = true;
		return colpara;
	}

	Vector3 v2 = s.position - c.endPos;
	if (t > 1 && v2.Length() * v2.Length() <= r2)
	{
		Vector3 vr = Vector3::Normalize(v2) * radius;
		colpara.colPos = c.endPos + vr;
		colpara.colFlag = true;
		return colpara;
	}

	Vector3 vn = v1 - t * v;
	if ((0 <= t && t <= 1) && (vn.Length() * vn.Length() < r2))
	{
		Vector3 vr = radius * Vector3::Normalize(vn);
		colpara.colPos = c.startPos + t * v + vr;
		colpara.colFlag = true;
		return colpara;
	}

	return colpara;
}

// �J�v�Z���ƃJ�v�Z���̉����߂�
Vector3 Collisin::PushedBack_CapsuleCapsule(const Capsule& c1, const Capsule& c2) const{
	Vector3 pushedPosition;

	Vector3 a = c1.endPos - c1.startPos;
	Vector3 b = c2.endPos - c2.startPos;
	Vector3 c = c2.startPos - c1.startPos;
	float D = c1.radius + c2.radius;

	Vector3 n = Vector3::Normalize(Vector3::Cross(a, b));
	float L = Vector3::Dot(c, n);

	Vector3 vd;
	if (L > 0)	vd = n * D;
	else		vd = -n * D;

	Vector3 p = c1.startPos - n * L;

	pushedPosition = p + vd;

	return pushedPosition;
}

//���Ƌ��̉����߂�
CollisionParameter Collisin::PushedBack_SphereSphere(const Sphere& s1, const Sphere& s2) const
{
	CollisionParameter colpara;
	int result = HitCheck_Sphere_Sphere(
		s1.position.ToVECTOR(), s1.radius,
		s2.position.ToVECTOR(), s2.radius);
	if (result > 0)
	{
		Vector3 vec = (s2.position - s1.position).Normalized();
		float backRadius = s1.radius + s2.radius;
		colpara.colPos = vec*backRadius;
		colpara.colFlag = true;
	}
	return colpara;
}