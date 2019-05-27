#include "OpenGL46TestController.h"

OpenGL46TestController::OpenGL46TestController() : TimestepController()
{
	m_gameElapsedTime=0.0f;
	m_gameStartTime = LARGE_INTEGER ();
	m_gameCurrentTime = LARGE_INTEGER();
	m_FrequencyQuadPart=0.0f;
	tLastCount = LARGE_INTEGER();

	//firstQuit = true;
}

OpenGL46TestController::~OpenGL46TestController()
{
}

INT OpenGL46TestController::Run()
{
	QueryPerformanceCounter(&m_gameStartTime);
	QueryPerformanceCounter(&m_gameCurrentTime);
	QueryPerformanceCounter(&tLastCount);


	isDone = false;

	g_msg.message = 0;

	while (!isDone)
	{
		if (!ProcessMessages())
		{
			QueryPerformanceCounter(&tCurrentCount);

			timeElapsed = (tCurrentCount.QuadPart - tLastCount.QuadPart) / (float)tFrequency.QuadPart;

			Update(timeElapsed);

			Render();

			Yield();
			tLastCount = tCurrentCount;
		}
	}

	return (INT)g_msg.wParam;
}

void OpenGL46TestController::Update(float deltaTime)
{
}

void OpenGL46TestController::Render()
{
	RenderBegin();


	RenderEnd();
}

void OpenGL46TestController::RenderBegin()
{
	
	g_OpenGL4Object.BeginScene(0.5f, 0.5f, 0.0f, 1.0f);
}

void OpenGL46TestController::RenderEnd()
{
	g_OpenGL4Object.EndScene();
}

bool OpenGL46TestController::ProcessMessages()
{
	if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
	{
		
		if (g_msg.message == WM_QUIT)
		{
			isDone = true; OutputDebugString("QUIT");
			firstQuit = false;
		}
		

		if (g_msg.message == GAMEEXIT_MENU)
		{
			isDone = true; OutputDebugString("Message found is for 'Game Exit to Menu'.");
		}

		TranslateMessage(&g_msg);
		DispatchMessage(&g_msg);
		return true;
	}
	return false;
}

void OpenGL46TestController::Shutdown()
{
}
