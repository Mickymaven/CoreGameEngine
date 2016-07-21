#include "InfoPanel.h"

InfoPanel::InfoPanel()
{

}

InfoPanel::~InfoPanel()
{

}

bool InfoPanel::Init(Character * character, vector<ItemView> * itemViews, TooltipController * tooltipController)
{

	m_character = character;

	m_state = infoPanelStateClosed;

	if (!m_background.Init(880.0f, 50.0f, "Resources/UI/Player/info-panel_background.png")) return false;
	m_background.SetPosition(185.0f, 0.0f, 50.0f);

	if (!StatBase::Init(tooltipController)) return false;


	//INV INIT
	m_inv.m_items.resize(10);
	if (!m_inv.Init()) return false;

	m_inv.SetItemViews(itemViews);
	
	for (unsigned int i = 0; i < 10; i++)
	{
		m_inv.m_items.at(i).SetMouseOverCallback(
			std::bind(&TooltipController::ActivateTooltipItem, tooltipController, _1, _2, _3));
	}

	LMVector4 v4 = LMVector4(580.0f, 60.0f, 1100.f, 100.0f);
	m_inv.PositionItems(&v4,43.0f,43.0f,45.0f,0.0f);


	//STATS INIT

	//m_stats.m_stats.resize(9);
	//if (!m_stats.Init()) return false;



	SetInfoPanelTarget(character);
	
	return true;
}


void InfoPanel::Render()
{
	if (m_state == infoPanelStateOpened)
	{
		m_background.Render();

		m_inv.Render();

		InfoPanelRenderRow(m_character);

	}
}

void  InfoPanel::Select(POINT * p)
{

}

void  InfoPanel::AltSelect(POINT * p)
{

}

bool  InfoPanel::MouseOver(POINT * p)
{
	if (m_state == infoPanelStateOpened)
		if (m_inv.MouseOver(p)) return true;

	return false;
}

InfoPanelState InfoPanel::GetState()
{
	return m_state;
}

void InfoPanel::SetState(InfoPanelState state)
{
	m_state = state;
}

void InfoPanel::SetInfoPanelTarget(Character * character)
{
	m_character = character;

	m_inv.SetItems(character->GetInventory());
	//m_stats.SetStatLabels(playerCharacterController->GetActor()->GetStats());

}

vector<LMVector3 *> * InfoPanel::GetInventoryRenderPositions()
{
	return & m_itemPositions;
}

Character * InfoPanel::GetInfoPanelTarget()
{
	return m_character;
}