#include "MenuSceneIntro.h"

MenuSceneIntro::MenuSceneIntro(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam) :MenuScene(selfSceneEnum, name, cam)
{
	//left, top, right, bottom
	m_fontposTitle = { 140, 100, 1000, 333 };
	m_fontPositionX = { 10, 350, 1280, 1024 };
	m_fontPositionY = { 10, 450, 1280, 1024 };

	//left, top right, bottom
}

MenuSceneIntro::~MenuSceneIntro()
{
	OutputDebugString("MENU SCENE DESTROYED");
}

bool MenuSceneIntro::Init()
{
	m_nextTarget = menuTargetCount;

	// -----------------------POSITION------------DIMENSIONS
	if (!m_buttonLaunch.Init(new POINT{ 25, g_clientSizeRect->bottom - 55 }, new POINT{ 30, 30 }, "Lobby test."))
		return false;

	if (!m_buttonQuickPlay.Init(new POINT{ g_clientSizeRect->right - 440, 10 }, new POINT{ 400, 30 }, "Quick Play"))
		return false;

	if (!m_moveScreenTwo.Init(new POINT{ g_clientSizeRect->left + 40, 10 }, new POINT{ 30, 30 }, "< 2"))
		return false;

	return true;
}

void MenuSceneIntro::Update(float fDeltaTime)
{

	///if (g_inputControl == NULL) OutputDebugString("INPUT CONTROLL NULL\n\n");

	UpdateMouseClientPosition(); //globals.h
	g_inputControl.UpdateDeviceStates();
	if (g_inputControl.MouseButtonDown(LEFT_BUTTON))
	{

		//
		if (m_buttonLaunch.IsHit(GetMouseClientPosition()->x, GetMouseClientPosition()->y))
			m_nextScene = menuNormalGameLobby;


		else if (m_buttonQuickPlay.IsHit(GetMouseClientPosition()->x, GetMouseClientPosition()->y))
			m_nextTarget = menuTargetGame;


		else if (m_moveScreenTwo.IsHit(GetMouseClientPosition()->x, GetMouseClientPosition()->y))
		{
			SetWindowPos(g_hwnd, HWND_TOP, -1680, 0, 0, 0, SWP_NOSIZE);
			m_nextTarget = menuTargetGame;
		}

	}
}

void MenuSceneIntro::Render()
{
	m_sharedBackground->Render();

	m_buttonLaunch.Render();
	m_buttonQuickPlay.Render();
	m_moveScreenTwo.Render();
}


void MenuSceneIntro::OnEnterScene()
{
	m_nextTarget = menuTargetCount;
	m_nextScene = menuIntro;
}
