#include "UIGameInfoPanel.h"

const int UIGameInfoPanel::elementIDs[] = 
{
	gameElementInfoAvatar0,
	gameElementInfoAvatar1,
	gameElementInfoAvatar2,
	gameElementInfoAvatar3,
	gameElementInfoAvatar4,
	gameElementInfoAvatar5,
	gameElementInfoAvatar6,
	gameElementInfoAvatar7,
	gameElementInfoAvatar8,
	gameElementInfoAvatar9
};


UIGameInfoPanel::UIGameInfoPanel()
{
}

UIGameInfoPanel::~UIGameInfoPanel()
{
}

bool UIGameInfoPanel::Init(ViewProfile * viewProfile, ThemeResources * themeResources, MobaState * gameState, TooltipController * tooltipController,
	PlayerCharacterController * initCharControl, vector<InputModel*> * inputModels, vector<ItemView> * itemViews)
{
	m_gameState = gameState;//base class this
	m_viewProfile = viewProfile; //this
	m_theme = themeResources;//t
	m_tooltipController = tooltipController;
	m_gameState = gameState;

	//viewProfile->InitUIBase(gameElementGameInfoPanel);
	int elementID = gameElementGameInfoPanel;

	SetBounds(
		viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID),
		viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID),
		viewProfile->m_aspectProfile->GetAlignX(elementID) + viewProfile->m_aspectProfile->GetXForElement(elementID) + viewProfile->m_aspectProfile->GetWidthForElement(elementID),
		viewProfile->m_aspectProfile->GetAlignY(elementID) + viewProfile->m_aspectProfile->GetYForElement(elementID) + viewProfile->m_aspectProfile->GetHeightForElement(elementID)
		);

	UIArea::m_bounds;

	if (!m_infoPanel.Init(initCharControl->GetCharacter(), itemViews, tooltipController)) return false;

	if (!m_tempAv.Init(
		viewProfile->m_aspectProfile->GetWidthForElement(gameElementInfoAvatar0),
		viewProfile->m_aspectProfile->GetWidthForElement(gameElementInfoAvatar0),
		"Resources/UI/Squares/Grey.png"
		)) return false;

	m_LayoutAvatars.resize(10);



	for (unsigned int i = 0; i < 10; i++)
	{
		m_LayoutAvatars[i].SetIcon(&m_tempAv);
		m_LayoutAvatars[i].SetPlayerCharacter(nullptr);
		//m_LayoutAvatars[i].SetPlayerCharacterView(nullptr);

		if (!m_viewProfile->InitLayoutAvatar(elementIDs[i], &m_LayoutAvatars[i], &m_tempAv)) return false;
	}

	m_controllers = gameState->GetPlayerCharacterTeams();

	switch (gameState->GetCharacterLists()->size())
	{
	case 1:break;
	case 2:
	{
		m_LayoutAvatarsByTeam.resize(2);
		
		m_LayoutAvatarsByTeam[0].push_back(&m_LayoutAvatars[0]);
		m_LayoutAvatarsByTeam[0].push_back(&m_LayoutAvatars[1]);
		m_LayoutAvatarsByTeam[0].push_back(&m_LayoutAvatars[2]);
		m_LayoutAvatarsByTeam[0].push_back(&m_LayoutAvatars[3]);
		m_LayoutAvatarsByTeam[0].push_back(&m_LayoutAvatars[4]);

		m_LayoutAvatarsByTeam[1].push_back(&m_LayoutAvatars[5]);
		m_LayoutAvatarsByTeam[1].push_back(&m_LayoutAvatars[6]);
		m_LayoutAvatarsByTeam[1].push_back(&m_LayoutAvatars[7]);
		m_LayoutAvatarsByTeam[1].push_back(&m_LayoutAvatars[8]);
		m_LayoutAvatarsByTeam[1].push_back(&m_LayoutAvatars[9]);



		//int teamSize;
		for (unsigned int teamIndex = 0; teamIndex < m_controllers->size(); teamIndex++)
		{
			for (unsigned int playerIndex = 0; playerIndex < m_controllers->at(teamIndex)->size(); playerIndex++)
			{
				m_LayoutAvatarsByTeam.at(teamIndex).at(playerIndex)->SetPlayerCharacter(
					m_controllers->at(teamIndex)->at(playerIndex)
					);

				if (playerIndex == 4) break;
			}

		}
	} break;
	default:break;
	}

	//init ability hotkey labels

	m_bindLabels.resize(10);

	CameraActions CameraActionsId[] =
	{
		cameraActionCameraFocusPlayer1,
		cameraActionCameraFocusPlayer2,
		cameraActionCameraFocusPlayer3,
		cameraActionCameraFocusPlayer4,
		cameraActionCameraFocusPlayer5,
		cameraActionCameraFocusPlayer6,
		cameraActionCameraFocusPlayer7,
		cameraActionCameraFocusPlayer8,
		cameraActionCameraFocusPlayer9,
		cameraActionCameraFocusPlayer10
	};


	for (unsigned int i = 0; i < 10; i++)
	{
		if (!viewProfile->InitRelativeLabel(elementIDs[i], &m_bindLabels[i], &themeResources->m_smallText, 20.0f, 13.0f, 1.0f, 1.0f)) return false;
		m_bindLabels[i].SetText(
			GetInputDefineString(
				inputModels->at(6)->m_keybinds[CameraActionsId[i]]
				).c_str()

			);


		//todo inputModels->at(6)-> is current one for camera input set can change
	}

}

void UIGameInfoPanel::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{
	m_playerCharacter = playerCharacterController;

}

void UIGameInfoPanel::Render()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		m_LayoutAvatars[i].Render();
		m_bindLabels[i].Render();
	}

	m_infoPanel.Render();


	//game time
	MyMinutes = floor((*m_gameState->GetGameElapsedTime() - 0.5f) / 60.0f);
	MySeconds = fmod((*m_gameState->GetGameElapsedTime() - 0.5f), 60.0f);
	if (MySeconds > 59.5f)
	{
		MyMinutes += 1.0f;
		MySeconds = 0.0f;
	}

	sprintf_s(m_clockBuff, "%.0f:%02.0f", MyMinutes, MySeconds);
	m_fontPos = { 0, 22, g_clientSizeRect->right, g_clientSizeRect->bottom };

	m_theme->m_largeText.m_font->DrawText(NULL, m_clockBuff, -1, &m_fontPos, DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
}

void UIGameInfoPanel::Select(POINT * p)
{
	for (unsigned int i = 0; i < m_LayoutAvatars.size(); i++)
	{
		if (m_LayoutAvatars[i].IsPointInBounds(p))
		{
			PlayerCharacterController * pcController = m_LayoutAvatars.at(i).GetPlayerCharacter();
			if (pcController != nullptr)
			{
				m_infoPanel.SetInfoPanelTarget(pcController->GetCharacter());
				m_infoPanel.SetState(infoPanelStateOpened);
			}
			return;
		}
	}

	m_infoPanel.SetState(infoPanelStateClosed);
}

void UIGameInfoPanel::AltSelect(POINT * p)
{
}

bool UIGameInfoPanel::MouseOver(POINT * p)
{
	if (m_infoPanel.MouseOver(p)) return true;

	return false;
}

InfoPanel * UIGameInfoPanel::GetInfoPanel() { return &m_infoPanel; }

