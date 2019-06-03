#include "BasicGameState.h"


BasicGameState::BasicGameState() : GameState()
{
	m_frameTimerModel = nullptr;
}

BasicGameState::~BasicGameState()
{

}

void BasicGameState::UpdateGameTime()
{
	QueryPerformanceCounter(&m_gameCurrentTime);
	m_gameElapsedTime = (m_gameCurrentTime.QuadPart - m_gameStartTime.QuadPart) / m_FrequencyQuadPart;
}


float * BasicGameState::GetGameElapsedTime()
{
	return & m_gameElapsedTime;
}

LARGE_INTEGER * BasicGameState::GetGameStartTime()
{
	return & m_gameStartTime;
}

LARGE_INTEGER * BasicGameState::GetGameCurrentTime()
{
	return & m_gameCurrentTime;
}


FrameTimerModel * BasicGameState::GetFrameTimerModel()
{
	return m_frameTimerModel;
}

void BasicGameState::SetGameElapsedTime(float elapsed)
{
	m_gameElapsedTime = elapsed;
}

void BasicGameState::SetGameStartTime(LARGE_INTEGER start)
{
	m_gameStartTime = start;
}

void BasicGameState::SetGameCurrentTime(LARGE_INTEGER current)
{
	m_gameCurrentTime = current;
}

void BasicGameState::SetFrameTimerModel(FrameTimerModel * frameTimerModel)
{
	m_frameTimerModel = frameTimerModel;
}
