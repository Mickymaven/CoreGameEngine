#if !defined(OPENGL46TESTCONTROLLER_H)
#define OPENGL46TESTCONTROLLER_H

#include <windows.h>

#include "../../../EngineGameModuleOpenGL46/src/Application/GlobalsOGL46.h"


#include "TimestepController.h"
#include "../Application/MsgParams.h"
#include "../../../EngineGamePlatform/src/Application/Globals.h"

class OpenGL46TestController : public TimestepController
{
private:
	//bool firstQuit;

protected:
	float m_gameElapsedTime;
	LARGE_INTEGER m_gameStartTime;
	LARGE_INTEGER m_gameCurrentTime;
	float m_FrequencyQuadPart;

public:
	OpenGL46TestController();
	virtual ~OpenGL46TestController();
	
	INT Run();

	void Update(float deltaTime);
	void Render();

	void RenderBegin();
	void RenderEnd();

	bool ProcessMessages();
	void Shutdown();

};

#endif