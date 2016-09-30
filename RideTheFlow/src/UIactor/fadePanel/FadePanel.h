#pragma once
#include "../../math/Vector2.h"

enum FADE_STATUS
{
	STANDBY	= 0,
	FadeIn	= 1,
	FadeOut = 2
};

class FadePanel
{
private:
	FadePanel() = default;
	~FadePanel() = default;

public:
	static FadePanel &GetInstance(){
		static FadePanel f;
		return f;
	}

	void Initialize();
	void Update();
	void Draw() const;
	void FadeIn();
	void FadeOut(float maxAlpha = 1.0f);
	// �ψْ����H
	bool IsAction() const;
	// ��ʂ��^���Â��H
	bool IsFullBlack() const;
	// ��ʂ������Ȃ����H
	bool IsFullClear() const;

	float GetInTime(){ return inTime; }
	void  SetInTime(float sec){ inTime = sec; }
	float GetOutTime(){ return outTime; }
	void  SetOutTime(float sec){ outTime = sec; }

private:
	FADE_STATUS status;

	float	actionTime;
	float	alpha;
	float	maxAlpha;
	bool	isAction;
	float	inTime;
	float	outTime;
};