#include "Buff.h"

Buff::Buff() {}
Buff::~Buff() {}

bool Buff::Init(int buffClass, float duration)
{
	m_buffClass = buffClass;

	m_timer = LMTimer(duration, true);
	
	
	m_isCurve = false;
	m_hpToCurve = 0.0f;

	hpAdded = 0.0f;

	lastElapsed = 0.0f;
	hpAddedExact = 0.0f;
	hpAddedOnLastElapsed = 0.0f;
	
	return true;
}

void Buff::Update(float deltaTime)
{
	if (m_isCurve == true)
	{
		HP(deltaTime);
	}

	m_timer.Update(deltaTime);

	if (m_timer.GetState() == timerFinished)
	{

		if (m_isCurve == true)
		{
			HP(deltaTime);
			sprintf_s(buffer, "hpAdded %f \n", hpAdded);
			OutputDebugString(buffer);

			sprintf_s(buffer, "HP EXACT %Lf with final elapsed %f \n", hpAddedExact, m_timer.GetElapsed());
			OutputDebugString(buffer);
		}
	}
}

void Buff::HP(float deltaTime)
{
	//float peak = 6.0f;
	//float a = 0.01f * peak * m_timer.GetTimerDuration();
	//float b = 0.1f * peak * m_timer.GetTimerDuration();
	//float x = m_timer.GetElapsed();
	//m_statsToChange->m_healthRegen = (-a*(x*x)) + (b*x);


	double hp = m_hpToCurve;
	double time = m_timer.GetTimerDuration();
	double elapsed = m_timer.GetElapsed();//0 -> 10

	//integral
	// 1/3*a*x^3 + 1/2*b*x^2 + c*x

	//a*time^3 + b*time^2 = 0
	double aFactor = -time;//float aFactor = -(time*time*time) / (time*time);

	//solve for a
	//(1.0f / 3.0f*time*time*time) * a + (1.0f / 2.0f * time*time) * b = hp
	// ((time*time*time/ hp) / 3.0f) * a + (((time*time/hp) / 2.0f) * b = 1

	//((time*time*time / hp) / 3.0f) * a + ((aFactor*(time*time / hp)) / 2.0f) * a = 1

	//( ( (time*time*time / hp)*(aFactor*(time*time / hp)) ) / (3.0f * 2.0f) ) * a = 1



	//is  ( ( ( (time*time*time) / hp)*(aFactor*( (time*time) / hp)) ) / (3.0f * 2.0f) ) * a = 1

	//((3.0f * 2.0f)/((time*time*time / hp)*(aFactor*(time*time / hp)))) = a / 1
	//is  ( (3.0f * 2.0f) / ( ( (time*time*time) / hp)*(aFactor*( (time*time) / hp)) )  ) = a



	double a = ((3.000f * 2.000f) / (((time*time*time) / hp)*(aFactor*((time) / hp))));

	//double a = -6.0000f * hp / (time * time * time);

	double b = -time * a;// float b = aFactor * a;
	
	//finally
	m_statsToChange.m_healthRegen = (a * elapsed*elapsed) + (b * elapsed);


	hpAdded += m_statsToChange.m_healthRegen * deltaTime;


	double e = elapsed;
	double hpThisDelta = (1.000000f / 3.000000f)*a*e*e*e + (1.0000f / 2.000000f)*b*e*e;
	double computed = hpThisDelta - hpAddedOnLastElapsed;
	hpAddedExact += computed;

	hpAddedOnLastElapsed = hpThisDelta; //hpAddedOnLastElapsed value sticks around for next update
	lastElapsed = elapsed;


	sprintf_s(buffer, "a: %f, b: %f, y (at %f) = %f.. hpAdded %f \n", a, b, elapsed, (a * elapsed*elapsed + b * elapsed), hpAdded);
	OutputDebugString(buffer);
}

const int & Buff::GetBuffClass()
{
	return m_buffClass;
}

LMTimer * Buff::GetTimer()
{
	return &m_timer;
}

StatChangeObject * Buff::GetStatChangeObject()
{
	return &m_statsToChange;
}

StatChangeObject * Buff::stat()
{
	return &m_statsToChange;
}

void Buff::SetHPCurve(bool isCurve, float hp) { m_isCurve = isCurve; m_hpToCurve = hp; }