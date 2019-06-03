#include "GameController.h"

GameController::GameController()
{
	isDone = false;
	standardMatch5v5 = nullptr;
	openWorld = nullptr;




}

GameController::~GameController()
{

}

INT GameController::Run(GameConfiguration * config)
{
	timeElapsed = 0.0f;

	QueryPerformanceFrequency(&tFrequency);
	QueryPerformanceCounter(&tLastCount);

	if (!InitLoadingRender()) return (INT)g_msg.wParam;

	// Select Mode ////////////////////////
	switch (config->GetGameMode())
	{
	case modeStandard:mobaControllerToRun = standardMatch5v5 = new StandardMatch5v5(); break;
	case modeOpenWorld:mobaControllerToRun = openWorld = new OpenWorld(); break;
	default:isDone = true;
	}
	// Mode Seleted ////////////////////////


	// Load ///////////////////////////
	int loadResult = 2;
	bool isLoadingDone = false;
	
	if (!mobaControllerToRun->Init(*config)) return (INT)g_msg.wParam;

	mobaControllerToRun->GetMobaState()->SetFrameTimerModel(&m_frameTimer);

	while (!isLoadingDone)
	{
		if (!ProcessMessages())
		{
			loadResult = mobaControllerToRun->LoadStates();

			if (loadResult == initMessageAbort) { isLoadingDone = true; isDone = true; }
			else if (loadResult == initMessageComplete) { isLoadingDone = true; }
			else if (loadResult == initMessageContinue)
			{
				LoadingRender(
					config,
					mobaControllerToRun->m_stateLoadProgress,
					mobaControllerToRun->m_stateLoadProgressSize,
					mobaControllerToRun->GetMobaState()->GetInitPhaseString( 
						(InitPhase)mobaControllerToRun->m_stateLoadProgress
						));
			}
		}
	}
	


	//// Load Complete /////////////////////////////////////////////////////////////


	// Run Sim /////////////////////////////////////////////////////////////////////

	QueryPerformanceCounter(mobaControllerToRun->GetMobaState()->GetGameStartTime());
	QueryPerformanceCounter(mobaControllerToRun->GetMobaState()->GetGameCurrentTime());

	QueryPerformanceCounter(&tLastCount);

	
	while (!isDone)
	{
		if (!ProcessMessages())
		{
			QueryPerformanceCounter(&tCurrentCount);

			timeElapsed = (tCurrentCount.QuadPart - tLastCount.QuadPart) / (float)tFrequency.QuadPart;

			m_frameTimer.Update(timeElapsed);

			mobaControllerToRun->Update(timeElapsed);
				
			mobaControllerToRun->Render();

			Yield();
			tLastCount = tCurrentCount;
		}
	}

	return (INT)g_msg.wParam;
}

bool GameController::ProcessMessages()
{
	if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (g_msg.message == WM_QUIT)
		{
			isDone = true; OutputDebugString("QUIT");
		}

		if (g_msg.message == GAMEEXIT_MENU)
		{
			//g_D3D_Device->Reset(&g_Present_Parameters);
			g_deviceControl.SetRenderSettings(customRenderSettingsUniversal);

			isDone = true; OutputDebugString("Message found is for 'Game Exit to Menu'.");
			//delete m_gameStateToDelete;

			
			if (standardMatch5v5 != nullptr) delete standardMatch5v5; standardMatch5v5 = nullptr;
			if (openWorld  != nullptr) delete openWorld; openWorld = nullptr;
			//if (mobaControllerToRun != nullptr) delete mobaControllerToRun; mobaControllerToRun = nullptr;
			//if (!= nullptr) delete; = nullptr;

		}

		TranslateMessage(&g_msg);
		DispatchMessage(&g_msg);
		return true;
	}
	return false;
}

void GameController::Shutdown()
{
	
}

bool GameController::InitLoadingRender()
{

	D3DXCreateFont(g_D3D_Device, 50, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "", &loadFont);

	m_loadingBackground =
		new UIElement((float)g_clientSizeRect->right, (float)g_clientSizeRect->bottom,
		"Resources/Client/Intro/intro-back-dev.png");
	
	if (m_loadingBackground->Init())
		return true;
	return false;
}

void GameController::LoadingRender(GameConfiguration * config, int progress, int progressSize, string message)
{
	g_D3D_Device->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(24, 16, 24), 1.0f, 0);
	g_D3D_Device->BeginScene();
	//g_deviceControl.SetRenderSettings(customRenderSettingsGameUI);

	//g_deviceControl.SetRenderSettings(customRenderSettingsGameUI);
	//gameState->GetCameraDirector()->SetUsingCamera(usingInterfaceCamera);

	
	m_loadingBackground->Render();

	fontPos = { 0, 675, g_clientSizeRect->right, 1024 };
	sprintf_s(m_initBuffer, "Loading component %i/%i: %s", progress, progressSize, message.c_str());
	loadFont->DrawText(NULL, m_initBuffer, -1, &fontPos, DT_CENTER, D3DCOLOR_XRGB(192, 192, 192));
	
	fontPos = { 0, (g_clientSizeRect->bottom - 65), (g_clientSizeRect->right -25), g_clientSizeRect->bottom };
	sprintf_s(m_initBuffer, "dev build %s ", __DATE__);
	loadFont->DrawText(NULL, m_initBuffer, -1, &fontPos, DT_RIGHT, D3DCOLOR_XRGB(192, 192, 192));
	
	g_D3D_Device->EndScene();
	g_D3D_Device->Present(NULL, NULL, NULL, NULL);
}

void GameController::InitDebugPrint()
{
	QueryPerformanceCounter(&m_initCurrent);
	sprintf_s(m_initBuffer, "seconds %f \n", ((m_initCurrent.QuadPart - m_initStart.QuadPart) / (float)tFrequency.QuadPart));
	OutputDebugString(m_initBuffer);
	Yield();
}
