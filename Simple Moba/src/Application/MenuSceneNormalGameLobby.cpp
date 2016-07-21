#include "MenuSceneNormalGameLobby.h"


MenuSceneNormalGameLobby::MenuSceneNormalGameLobby(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam) :MenuScene(selfSceneEnum, name, cam)
{
	m_uxTitleFont = NULL;
	m_fontposTitle = { 50,50,1100,100 };

	m_fontCountdown = NULL;
	m_positionCountdown = { 600, 690, g_clientSizeRect->right, g_clientSizeRect->bottom };

	m_pointerToGameConfig = NULL;

	//m_timer = LMTimer(1.0f, false);
}

MenuSceneNormalGameLobby::~MenuSceneNormalGameLobby()
{

}

bool MenuSceneNormalGameLobby::Init()
{
	// -----------------------POSITION------------DIMENSIONS
	if (!m_buttonLockCharacter.Init(new POINT{ 650, 735 }, new POINT{ 400, 30 }, "Lock In Selection"))
		return false;

	if (FAILED(D3DXCreateFont(g_D3D_Device, 18, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, "", &m_uxTitleFont)))
		return false;

	if (FAILED(D3DXCreateFont(g_D3D_Device, 80, 0, FW_BOLD, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, "Nanum Brush Script", &m_fontCountdown)))
		return false;

	return true;
}

void MenuSceneNormalGameLobby::Update(float deltaTime)
{
	UpdateMouseClientPosition(); //globals.h
	g_inputControl.UpdateDeviceStates();


	//sprintf_s(buffertext, "Update timer state enum %i\n", (int)m_timer.GetState());
	//OutputDebugString(buffertext);

	//sprintf_s(buffertext, "Update timer elapsed %f\n", m_timer.GetElapsed());
	//OutputDebugString(buffertext);

	m_timer.Update(deltaTime);

	if (m_timer.GetState() == timerInitial)
	{
		if (g_inputControl.MouseButtonDown(0))
		{
			if (m_buttonLockCharacter.IsHit(GetMouseClientPosition()->x, GetMouseClientPosition()->y))
			{
				m_timer.RestartWithDuration(1.0f, true);
			}
		}
	}




	else if (m_timer.GetState() == timerFinished)
	{
		//	Map Name	
		m_gameConfigResult = GameConfiguration(gameMapBarebones, "Forest", modeStandard);

		m_pointerToGameConfig = &m_gameConfigResult;

		m_gameConfigResult.AddPlayer("Butter", characterGrey, yellowTeamName, 1, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Lemon", characterGrey, yellowTeamName, 2, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Gold", characterGrey, yellowTeamName, 3, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Amber 2", characterGrey, yellowTeamName, 4, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Cheese", characterGrey, yellowTeamName, 5, abilityCosmicSpaghetti, abilityCosmicSpaghetti);

		m_gameConfigResult.AddPlayer("Lavender", characterGrey, purpleTeamName, 6, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Violet", characterGrey, purpleTeamName, 7, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Lilac", characterGrey, purpleTeamName, 8, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Mauve", characterGrey, purpleTeamName, 9, abilityCosmicSpaghetti, abilityCosmicSpaghetti);
		m_gameConfigResult.AddPlayer("Grape", characterGrey, purpleTeamName, 10, abilityCosmicSpaghetti, abilityCosmicSpaghetti);

		//OutputDebugString("Game config initialised with players added");

		m_nextTarget = menuTargetGame;
	}

	//sprintf_s(buffertext, "Update timer state enum %i\n", (int)m_timer.GetState());
	//OutputDebugString(buffertext);
}

void MenuSceneNormalGameLobby::Render()
{
	m_uxTitleFont->DrawText(NULL, "Select Your Character and press \"Lock In Selection\"",
		-1, &m_fontposTitle, DT_LEFT, D3DCOLOR_XRGB(200, 200, 200));

	if (m_timer.GetState() != timerInitial)
	{
		if (m_timer.GetRemainder() > 0.4f)
		{
			sprintf_s(buffertext, "%1.1f", m_timer.GetRemainder());

			m_fontCountdown->DrawText(NULL, buffertext, -1, &m_positionCountdown,
				DT_LEFT, D3DCOLOR_XRGB(255, 63, 63));
		}

		else if (m_timer.GetRemainder() > 0.04f)
		{
			sprintf_s(buffertext, "%2.0f", m_timer.GetRemainder());

			m_fontCountdown->DrawText(NULL, buffertext, -1, &m_positionCountdown,
				DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		}
	}

	m_buttonLockCharacter.Render();
}

void MenuSceneNormalGameLobby::OnEnterScene()
{
	m_nextScene = menuNormalGameLobby;

	m_timer.RestartWithDuration(1.0f, false);


	sprintf_s(buffertext, "OnEnter timer state enum %i\n", (int)m_timer.GetState());
	//OutputDebugString(buffertext);
}

GameConfiguration * MenuSceneNormalGameLobby::GetGameConfig()
{
	return m_pointerToGameConfig;
}