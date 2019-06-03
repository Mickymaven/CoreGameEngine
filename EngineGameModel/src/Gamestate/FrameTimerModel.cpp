#include "FrameTimerModel.h"

FrameTimerModel::FrameTimerModel()
{
	m_frameTimeSize = 60;
	m_frameTimes.resize(m_frameTimeSize, 0.0f);
	m_thisFrameIndex = 0;
}

FrameTimerModel::~FrameTimerModel()
{
}

void FrameTimerModel::Update(float deltaTime)
{
	m_frameTimes.at(m_thisFrameIndex) = deltaTime;

	if (m_thisFrameIndex == m_frameTimeSize-1) m_thisFrameIndex = 0;
	else m_thisFrameIndex++;
}


float FrameTimerModel::GetFrameTimeAverage()
{
	float tempAverage = 0.0f;

	for (int i = 0; i < m_frameTimes.size(); i++)
	{
		tempAverage += m_frameTimes.at(i);
	}


	tempAverage = tempAverage /= m_frameTimeSize;

	if (m_thisFrameIndex == 0 || m_thisFrameIndex == 20 || m_thisFrameIndex == 40) m_frameTimeAverage = tempAverage;
	return m_frameTimeAverage;
}

float FrameTimerModel::GetFPSAverage()
{
	GetFrameTimeAverage();

	/*
	
	18fps = 0.92 frametime
	60fps 0.275 frametime
	25fps 0.65 frametime

	0.0009
	
	
	*/
	


	return 1000.0f / (m_frameTimeAverage * 1000);
}







