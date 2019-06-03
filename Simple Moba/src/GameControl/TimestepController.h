#if !defined(TIMESTEPCONTROLLER_H)
#define TIMESTEPCONTROLLER_H

#include <Windows.h>

#include "../../../EngineGameModel/src/Gamestate/FrameTimerModel.h"

class TimestepController
{
protected:
	LARGE_INTEGER tFrequency;
	LARGE_INTEGER tLastCount;
	LARGE_INTEGER tCurrentCount;
	float timeElapsed;

	FrameTimerModel m_frameTimer;

	bool isDone;
	bool firstQuit;

	LARGE_INTEGER m_initStart;
	LARGE_INTEGER m_initCurrent;

public:
	TimestepController();
	~TimestepController();




};


#endif