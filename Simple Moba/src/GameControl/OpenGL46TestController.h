#if !defined(OPENGL46TESTCONTROLLER_H)
#define OPENGL46TESTCONTROLLER_H

#include <windows.h>

#include "../../../EngineGameModuleOpenGL46/src/Application/GlobalsOGL46.h"


#include "TimestepController.h"
#include "../Application/MsgParams.h"
#include "../../../EngineGamePlatform/src/Application/Globals.h"


#include "../../../EngineGameModuleOpenGL46/src/Device/OpenGL4Object.h"
#include "../../../EngineGameModuleOpenGL46/src/Device/OpenGL4ColorShader.h"
#include "../../../EngineGameModuleOpenGL46/src/Device/OpenGL4TextureShader.h"
#include "../../../EngineGameModuleOpenGL46/src/Input/OpenGL4Input.h"

#include "../../../EngineGameModuleOpenGL46/src/Graphics/ModelClass.h"

#include "../../../EngineGameModuleOpenGL46/src/View/CameraClass.h"



#include "../../../EngineGameModuleOpenGL46/src/Shaders/OpenGL4LightShader.h"
#include "../../../EngineGameModuleOpenGL46/src/Graphics/LightClass.h"


#include "../../../EngineGameModel/src/Maths/LMMatrix4.h"

//#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"






const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class OpenGL46TestController : public TimestepController
{
private:
	//bool firstQuit;
	OpenGL4LightShader * m_LightShader;
	LightClass* m_Light;

	LightClass* m_Light2;

protected:
	float m_gameElapsedTime;
	LARGE_INTEGER m_gameStartTime;
	LARGE_INTEGER m_gameCurrentTime;
	float m_FrequencyQuadPart;

	//LMCamera m_myCamera;
	OpenGL4Object * m_OpenGL;
	CameraClass * m_Camera;
	ModelClass * m_Model;


	OpenGL4ColorShader * m_ColorShader;
	OpenGL4TextureShader * m_textureShader;
	OpenGL4Input * m_Input;

public:
	OpenGL46TestController();
	virtual ~OpenGL46TestController();
	
	bool Initialize(OpenGL4Object * object, HWND hwnd);

	INT Run();

	bool Frame();

	void Update(float deltaTime);
	bool Render(float rotation);

	void RenderBegin();
	void RenderEnd();

	bool ProcessMessages();
	void Shutdown();

};

#endif