#include "LMTimer.h"

LMTimer::LMTimer()
{
	m_duration = 0.0f;
	m_elapsed = 0.0f;
	m_state = timerInitial;
}

LMTimer::LMTimer(float duration, bool autostart)
{
	m_duration = duration;
	m_elapsed = 0.0f;

	if (autostart)  m_state = timerStarted;
	else m_state = timerInitial;
}

LMTimer::~LMTimer()
{

}

void LMTimer::Update(float deltaTime)
{
	if (m_state == timerStarted)
	{
		m_elapsed += deltaTime;
	}

	if (m_state != timerFinished)
	{
		if (m_elapsed >= m_duration) m_state = timerFinished;
	}
}

void LMTimer::Start()
{
	if (m_state != timerFinished)
	{
		m_state = timerStarted;
	}
}

void LMTimer::Stop()
{
	if (m_state != timerFinished)
	{
		m_state = timerStopped;
	}
}

void LMTimer::RestartWithDuration(float duration, bool autostart)
{
	m_elapsed = 0.0f;
	m_duration = duration;

	if (autostart) m_state = timerStarted;
	else m_state = timerInitial; 

}