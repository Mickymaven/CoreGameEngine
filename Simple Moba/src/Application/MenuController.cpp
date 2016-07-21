#include "MenuController.h"



MenuController::MenuController()
{

	m_pIntroMenu = NULL;
	m_pHomeMenu = NULL;
	m_pPlayMenu = NULL;
	m_pNormalGameLobbyMenu = NULL;
	m_menuControllerTarget = menuTargetExit;
	currentState = menuIntro;

	m_pGameConfig = NULL;

	isDone = false;
}

MenuController::~MenuController()
{

}

bool MenuController::Init()
{
	int x = 0;



	return true;
}

void MenuController::Reset()
{
	m_menuControllerTarget = menuTargetExit;



	SetMenu(menuIntro);
	GetMenu(menuIntro)->OnEnterScene();

	isDone = false;
}

bool MenuController::InitMenu(MenuSceneSelection menuSceneEnum)
{

	switch (menuSceneEnum)
	{
	case menuIntro:
		m_pIntroMenu = new MenuSceneIntro(menuSceneEnum, "Intro Menu", &m_uicamera);
		if (!m_pIntroMenu->Init()) return false;
		break;
	case menuNormalGameLobby:
		m_pNormalGameLobbyMenu = new MenuSceneNormalGameLobby(menuSceneEnum, "Game Lobby: Normal Game", &m_uicamera);
		if (!m_pNormalGameLobbyMenu->Init()) return false;

		break;
	default:
		return false;
		break;
	}

	return true;
}

MenuControllerTarget MenuController::Run()
{
	//VV view stuff init /////////////////////////////////////////////////////
	GetClientRect(g_hwnd, g_clientSizeRect);

	float w = (float)g_clientSizeRect->right;
	float h = (float)g_clientSizeRect->bottom;


	D3DXVECTOR3	pos = D3DXVECTOR3(0.5f * w, -1.0f, 0.5f * h - 0.0001f);  //interface settings copied in cameraDirector;
	D3DXVECTOR3 lookAt = D3DXVECTOR3(0.5f * w, 0.0f, 0.5f * h);           //interface settings copied in cameraDirector;

	m_uicamera = m_cameraFactory.ConstructGameFreeCamera(projectionOrthographic, cameraLockStatic);
	m_uicamera.Init(0.0f, w, h, &pos, &lookAt);

	//temp place to init menu renderstates
	g_deviceControl.SetRenderSettings(customRenderSettingsUniversal);
	g_deviceControl.SetRenderSettings(customRenderSettingsMenuUI);
	// ^^ view stuff init//////////////////////////////////////////////////////////

	//use view st uff
	g_D3D_Device->SetTransform(D3DTS_VIEW, m_uicamera.GetViewMatrix());
	g_D3D_Device->SetTransform(D3DTS_PROJECTION, m_uicamera.GetProjectionMatrix());


	Reset();//move this if you dont want to always go to into
			//while mc.Run() (located in in main loop);



	LARGE_INTEGER tFrequency;
	LARGE_INTEGER tLastCount;
	LARGE_INTEGER tCurrentCount;
	float timeElapsed = 0.0f;

	QueryPerformanceFrequency(&tFrequency);
	QueryPerformanceCounter(&tLastCount);

	while (!isDone)
	{
		if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (g_msg.message == WM_QUIT) isDone = true;
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
		}
		else
		{

			QueryPerformanceCounter(&tCurrentCount);

			timeElapsed = (tCurrentCount.QuadPart - tLastCount.QuadPart) / (float)tFrequency.QuadPart;

			Update(timeElapsed);
			Render();

			Yield();
			tLastCount = tCurrentCount;
		}
	}

	return m_menuControllerTarget;
}


MenuScene * MenuController::GetMenu(MenuSceneSelection menuSceneEnum)
{
	switch (menuSceneEnum)
	{
	case menuIntro:
		return m_pIntroMenu;
		break;
	case menuNormalGameLobby:
		return m_pNormalGameLobbyMenu;
		break;
	default:
		return NULL;

	}
}

void MenuController::SetMenu(MenuSceneSelection state)
{

	if (GetMenu(state) == NULL)
	{
		if (InitMenu(state))
		{
			currentState = state;
			GetMenu(state)->OnEnterScene();
		}
		else
		{
			MessageBox(NULL, "MenuController::SetMenu() Cant init menu for state", "Error", MB_OK);
		}

		return;
	}

	if (currentState != state)
	{
		currentState = state;
		GetMenu(state)->OnEnterScene();
	}
	else
	{
		currentState = state;
	}

}

void MenuController::Update(float deltaTime)
{
	MenuSceneSelection nextTargetScene;
	MenuControllerTarget nextTargetController;

	switch (currentState)
	{
	case menuIntro:
		m_pIntroMenu->Update(deltaTime);
		nextTargetScene = m_pIntroMenu->CheckTargetScene();
		nextTargetController = m_pIntroMenu->CheckTargetController();
		break;
	case menuNormalGameLobby:
		m_pNormalGameLobbyMenu->Update(deltaTime);
		nextTargetScene = m_pNormalGameLobbyMenu->CheckTargetScene();
		nextTargetController = m_pNormalGameLobbyMenu->CheckTargetController();

		break;
	default:
		MessageBox(NULL, "update: Worst enum provided ever.", "Error!", MB_OK);
		break;
	}

	SetMenu(nextTargetScene);


	if (nextTargetController == menuTargetNone)
	{

	}
	else if (nextTargetController == menuTargetGame)
	{
		switch (currentState)
		{
		case menuNormalGameLobby:
			m_pGameConfig = m_pIntroMenu->GetTestGameConfig(0);//m_pNormalGameLobbyMenu->GetGameConfig();
			break;
		case menuIntro:
			m_pGameConfig = m_pIntroMenu->GetTestGameConfig(0);
			break;
		default:
			MessageBox(NULL, "update: Worst enum provided ever.", "Error!", MB_OK);
			break;
		}

		isDone = true;
		m_menuControllerTarget = menuTargetGame;
	}


	else if (nextTargetController == menuTargetExit)
	{
		isDone = true;
		m_menuControllerTarget = menuTargetExit;
	}
}

void MenuController::Render()
{
	g_D3D_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(12, 12, 12), 1.0f, 0);
	g_D3D_Device->BeginScene();




	switch (currentState)
	{
	case menuIntro:
		m_pIntroMenu->Render();
		//maybe add chat system overlay rendering here
		break;

	case menuNormalGameLobby:
		m_pNormalGameLobbyMenu->Render();
		break;
	default:
		MessageBox(NULL, "render: Worst enum provided ever.", "Error!", MB_OK);
		break;
	}

	g_D3D_Device->EndScene();
	g_D3D_Device->Present(NULL, NULL, NULL, NULL);
}

