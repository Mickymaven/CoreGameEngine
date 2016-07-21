#if !defined(LMTIMER_H)
#define LMTIMER_H

enum TimerState
{
	timerInitial,
	timerStarted,
	timerStopped,
	timerFinished,
	timerStateCount
};

class LMTimer
{

private:
	//bool m_isStarted;

	TimerState m_state;

	float m_duration;
	float m_elapsed;

public:
	LMTimer();
	LMTimer(float duration, bool autostart);
	~LMTimer();

	void Update(float deltaTime);

	TimerState GetState() { return m_state; }
	
	float GetElapsed() { return m_elapsed; }
	float GetRemainder() { return (m_duration - m_elapsed); }
	float GetTimerDuration() { return m_duration; }

	void LMTimer::Start();
	void LMTimer::Stop();

	void RestartWithDuration(float duration, bool autostart);

	// timerInitial,
	// timerStarted,
	// timerStopped,
	// timerFinished,

};

#endif