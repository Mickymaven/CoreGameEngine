#include "InfoPanelController.h"

InfoPanelController::InfoPanelController() : UIArea()
{
	OutputDebugString("InfoPanel Construction\n");
	gameState = NULL;
	gameConfiguration = NULL;
	m_boxPositions = NULL;
	m_leftTeam = NULL;
	m_rightTeam = NULL;
}

InfoPanelController::~InfoPanelController()
{

}

bool InfoPanelController::Init(GameAssetFactory * gameAssetFactory, StandardMatch5v5State * gameStateIn, GameConfiguration * gameConfigurationIn, vector<ItemView> * itemViews, TooltipController * tooltipController)
{
	gameState = gameStateIn;
	gameConfiguration = gameConfigurationIn;
	m_leftTeam = gameState->GetTeamControllersAsVector(yellowTeamName);
	m_rightTeam = gameState->GetTeamControllersAsVector(purpleTeamName);

	m_boxCount = gameConfiguration->GetPlayerIDs()->size();
	m_boxPositions = new LMVector3[m_boxCount];

	float xStart = 0.17578125 * g_clientSizeRect->right; //180.0f / 1280.0f * g_clientSizeRect->right;// 180.0f;
	float yStart = 6.66f;
	float xSpace = 70.0f; // 70.0f / 1280.0f * g_clientSizeRect->right;

	float secondOffset = (0.5935- 0.17578125) * g_clientSizeRect->right;   //580.0f / 1280.0f * g_clientSizeRect->right;

	for (int index = 0; index < m_boxCount; index++)
	{
		if (index <=4)
		m_boxPositions[index] = LMVector3(xStart + (index * xSpace), 0.0f, yStart);
		else 
		m_boxPositions[index] = LMVector3(secondOffset + xStart + ((index - 5.0f) * xSpace), 0.0f, yStart);
	}

	/////

	UIElement * e = NULL;
	GetTeamsPanelIcons()->resize(gameConfiguration->GetPlayerCharacterNames()->size());

	for (unsigned int i = 0; i < gameConfiguration->GetPlayerCharacterNames()->size(); i++)
	{
		e = gameAssetFactory->GetCharacterIcon(
			gameConfiguration->GetPlayerCharacterNames()->at(i));

		GetTeamsPanelIcons()->at(i) = e;

		e->GetPosition()->x = GetPositionArray()[i].x;
		e->GetPosition()->y = GetPositionArray()[i].y;
		e->GetPosition()->z = GetPositionArray()[i].z;

	}
	/////


	if (!m_infoPanel.Init(gameStateIn->GetControlledCharacter(), itemViews, tooltipController)) return false;

	return true;
}

void InfoPanelController::Update(float deltaTime)
{
	
}

void InfoPanelController::Render()
{
	for (unsigned int i = 0; i < m_boxCount; i++)
	{
		m_teamsPanelIcons.at(i)->Render();
	}
}

void InfoPanelController::RenderInfoPanel()
{
	m_infoPanel.Render();
}

void InfoPanelController::Select(POINT * p)
{

}

void InfoPanelController::AltSelect(POINT * p)
{

}

bool InfoPanelController::MouseOver(POINT * p)
{
	if (m_infoPanel.MouseOver(p)) return true;

	return false;
}

void InfoPanelController::HandleLeftClick()
{
	//if (gameView->GetGameShopMenu()->GetState() == gameShopMenuStateOpened) return;
	//else if (gameView->GetMainMenu()->IsOpen()) return;

	BehaviorOnFirstHit(50.0f, 50.0f, m_boxPositions, m_boxCount, 0);
}

void InfoPanelController::ImplementBehavior(int index, int enumIndex)
{
		if (enumIndex == 0)
	{
		//OutputDebugString("MOUSE OVER \n");
		if (index <= 4)
			m_infoPanel.SetInfoPanelTarget(m_leftTeam->at(index)->GetCharacter());
		else
			m_infoPanel.SetInfoPanelTarget(m_rightTeam->at(index - 5)->GetCharacter());
		
		m_infoPanel.SetState(infoPanelStateOpened);
	}
}

InfoPanel * InfoPanelController::GetInfoPanel()
{
	return & m_infoPanel;
}

LMVector3 * InfoPanelController::GetPositionArray()
{
	return m_boxPositions;
}

vector <UIElement*> * InfoPanelController::GetTeamsPanelIcons()
{
	return &m_teamsPanelIcons;
}