#pragma once

class Time {
public:
	Time();
	static Time &GetInstance();
	void update();
	float deltaTime();
	float refreshRate();
	float correctionTime();
	void draw_fps();
private:
	float m_LastFrame;
	float m_LastTime;
	float m_RealtimeSinceStartup;
	float m_FrameCount;
	float m_DeltaTime;
private:
	int counter;
	int FpsTime[2];
	int FpsTime_i;
	double Fps;
};