#include "FogActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../game/Random.h"
#include "../camera/Camera.h"
#include "../time/Time.h"
#include "../math/Math.h"
#include "../sound/Sound.h"

static const float LengthMax = 12000.0f;
static const float FogSettingValue = 0.1f;
static const float RangeMax = 10.0f;
static const float AngleSettingValue = 18.0f;

//sandstorm��se���������͂��߂�A���_����̋���
static const float SandStormStartLength = 6000.0f;
//�ő�ɂȂ鋗��
static const float SandStormLengthMax = 8000.0f;

FogActor::FogActor(IWorld& world,Camera camera) :
Actor(world),
mCamera(camera),
position(Vector3::Zero),
fogTotalPower(0.0f),
angle(0.0f),
fogStartAngle(70.0f)
{
	parameter.isDead = false;
	parameter.id = ACTOR_ID::FOG_ACTOR;
	SetFogEnable(TRUE);
	SetFogColor(180, 180, 200);
}
FogActor::~FogActor()
{
	SetFogEnable(FALSE);
}

float Length;

void FogActor::Update()
{
	position = mCamera.Position.Get();
	//���_����̋���
	float length = position.Length();
	Length = length;
	//�J�����̑O����
	Vector3 front = Vector3::Normalize(mCamera.Target.Get() - mCamera.Position.Get());
	//���_�֌���������
	Vector3 toOrigin = Vector3::Normalize(-position);
	if (Vector3::Dot(front, front) == Vector3::Dot(toOrigin, toOrigin)) return;
	//�O�ƌ��_�����̂Ȃ��p
	angle = Vector3::Inner(front, toOrigin);
	
	Vector3 cross = Vector3::Cross(front, toOrigin);

	//length = Math::Clamp(length, 1.0f, 2000.0f) * 1.0f;
	//float anglePower = angle - fogStartAngle;
	//anglePower = Math::Clamp(anglePower, 1.0f, 90.0f) * 6.0f;
	//float fogPower = length * anglePower;
	//float fogMaxPower = 2000.0f * 180.0f * 400.0f;

	//fogTotalPower = fogMaxPower / fogPower;
	//fogTotalPower = Math::Clamp(fogTotalPower, 10.0f, 2000.0f);

	length = Math::Clamp(length, 1.0f, LengthMax) * FogSettingValue;
	float anglePower = angle - fogStartAngle;
	anglePower = Math::Clamp(anglePower, 1.0f, fogStartAngle) *AngleSettingValue;
	float fogPower = length * anglePower;
	float fogMaxPower = LengthMax * 180.0f * 400.0f;

	fogTotalPower = fogMaxPower / fogPower;
	fogTotalPower = Math::Clamp(fogTotalPower, 10.0f, LengthMax);

	SetFogStartEnd(0.0f, fogTotalPower);
}
void FogActor::Draw() const
{
	//DrawFormatString(900, 10, Vector3::Black.ToColor(), "fogTotalPower : %f", Length);
}
void FogActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}
