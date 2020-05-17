#if !defined(MAIN_H)
#define MAIN_H

#include <Windows.h>
#include "../../../EngineGameModuleOpenGL46/src/Device/OpenGL4Object.h"
#include "../../../EngineGameModuleOpenGL46/src/Input/OpenGL4Input.h"
#include "../GameControl/OpenGL46TestController.h"

class Main
{
public:
	Main();
	virtual ~Main();
	HRESULT Create(HINSTANCE hInstance);
	INT Run();
	bool InitWindowClass();
	bool InitOpenGLExtensions();
	bool InitWindow();
	bool InitDirectX();
	bool InitOpenGL();
	bool ShowMyWindow();
	bool InitDeviceController();
	bool InitInputController();
	bool InitMenuController();

	//open gl way


	LPCSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	OpenGL4Object* m_OpenGL;
	OpenGL4Input* m_Input;
	OpenGL46TestController* m_Graphics;

	bool OGLINIT();
	void OGLRUN();
	void OGLSHUT();
	bool OGLFRAME();
	bool OGLINITWINDOWS(OpenGL4Object*, int&, int&);
	void OGLSHUTDOWNWINDOWS();


	LRESULT CALLBACK Main::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);


private:

};


static Main* ApplicationHandle = 0;

#endif