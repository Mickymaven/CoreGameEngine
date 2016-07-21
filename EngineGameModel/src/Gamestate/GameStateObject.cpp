#include "GameStateObject.h"

GameStateObject::GameStateObject()
{
	m_loadProgress = 0;
	m_loadSize = 0;
}

GameStateObject::~GameStateObject()
{

}

InitMessage GameStateObject::UpdateLoadProgress()
{
	//if (!InitSelectedPhase(m_loadProgress)) return initMessageAbort;

	InitDebugPrint(GetInitPhaseString(m_loadProgress));

	m_loadProgress++;

	if (m_loadProgress == m_loadSize) return initMessageComplete;

	return initMessageContinue;
}

bool GameStateObject::InitSelectedPhase(int initPhase)
{
	return false;
}

string GameStateObject::GetInitPhaseString(int initPhase)
{
	return "base class string";
}

void GameStateObject::InitDebugPrint(string s)
{
	QueryPerformanceCounter(&m_initCurrent);
	sprintf_s(m_initBuffer, "seconds %f \n %s \n ", ((m_initCurrent.QuadPart - m_initStart.QuadPart) / (float)m_init_tFrequency.QuadPart), s.c_str());
	OutputDebugString(m_initBuffer);
}

int * GameStateObject::GetLoadProgress()
{
	return &m_loadProgress;
}

int * GameStateObject::GetLoadSize()
{
	return &m_loadSize;
}

void GameStateObject::SetLoadProgress(int loadProgress)
{
	m_loadProgress = loadProgress;
}

void GameStateObject::SetLoadSize(int loadSize)
{
	m_loadProgress = loadSize;
}