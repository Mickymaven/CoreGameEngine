#include "StatPanel.h"

StatPanel::StatPanel()
{


}

StatPanel::~StatPanel()
{

}

bool StatPanel::Init(
	ViewProfile * viewProfile,
	ThemeResources * themeResources,
	MobaState * gameState,
	vector<PlayerCharacterController*> * yellowTeam,
	vector<PlayerCharacterController*> * purpleTeam,
	TooltipController * tooltipController,
	vector<ItemView> * lightweightItemViews)
{
	m_gameState = gameState;
	m_tooltipController = tooltipController;
	m_viewProfile = viewProfile;
	m_theme = themeResources;

	m_lightweightItemViews = lightweightItemViews;

	m_teamControllers.resize(2);

	m_teamControllers.at(0) = yellowTeam;
	m_teamControllers.at(1) = purpleTeam;

	if (FAILED(
		D3DXCreateFont(g_D3D_Device, 28, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "", &m_textFont) // DEFAULT_QUALITY //FW_BOLD
		))
	{
		MessageBox(NULL, "Failed to load font in StatBase", "Error", MB_OK);
		return false;
	}

	m_fontPosition = { 0, 0, 0, 0 };

	m_kdaPosition1 = { 0, 0, 150, 240 };


	//if (!StatBase::Init()) return false;

	m_yellowTeam = yellowTeam;
	m_purpleTeam = purpleTeam;

	m_state = statPanelClosed;
	
	if (!viewProfile->InitElement(gameElementStatVerticalStats, &m_verticalStats)) return false;

	if (!viewProfile->InitElement(gameElementStatBackground, &m_background)) return false;

	m_originLeft = LMVector2 (
		m_background.GetPosition()->x + 0.047f * m_background.GetWidth(),
		m_background.GetPosition()->y + 0.15f * m_background.GetHeight()
		);


	m_originRight = LMVector2(
		m_background.GetPosition()->x + 0.64f * m_background.GetWidth(),
		m_background.GetPosition()->y + 0.15f * m_background.GetHeight()
		);


	m_originLeft2 = LMVector2(
		m_background.GetPosition()->x + 0.047f * m_background.GetWidth(),
		m_background.GetPosition()->y + 0.42f * m_background.GetHeight()
		);


	m_originRight2 = LMVector2(
		m_background.GetPosition()->x + 0.64f * m_background.GetWidth(),
		m_background.GetPosition()->y + 0.42f * m_background.GetHeight()
		);


	//m_background->SetPosition(90.0f / 1280.0f * g_clientSizeRect->right, 0.0f, 0.0f);
	//m_close->SetPosition((1100.0f + 90.0f - 53.0f) / 1280.0f * g_clientSizeRect->right, 0.0f, 65.0f);

	m_teams.resize(2);

	for (unsigned int iTeam = 0; iTeam < 2; iTeam++)
	{
		m_teams.at(iTeam).resize(5);

		for (unsigned int iPlayer = 0; iPlayer < 5; iPlayer++)
		{
			m_teams.at(iTeam).at(iPlayer).resize(10);

			for (unsigned int iInv = 0; iInv < 10; iInv++)
			{
			

				m_layoutItems.push_back(&m_teams.at(iTeam).at(iPlayer).at(iInv));
				m_teams.at(iTeam).at(iPlayer).at(iInv).SetMouseOverCallback(
					std::bind(&TooltipController::ActivateTooltipItem, tooltipController, _1, _2, _3));
			}
		}
	}

	CalculateInvPositions();
	SetInvItems();

	return true;
}
void  StatPanel::CalculateInvPositions()
{
	float rowTop = 0.0f;
	float elementLeft = 0.0f;
	LMVector3 * pos = NULL;
	RECT * eleBounds = NULL;
	float eleWidth = 0.0f;
	float eleHeight = 0.0f;

	rowTop = m_originLeft2.y -20.0f; //220.0f;
	elementLeft = m_originLeft2.x; //200.0f - 20.0f;//780

	for (unsigned int iTeam = 0; iTeam < 2; iTeam++)
	{
		if (iTeam == 1) elementLeft = m_originRight.x;//2nd team on right

		for (unsigned int iPlayer = 0; iPlayer < 5; iPlayer++)
		{
			for (unsigned int iInv = 0; iInv < 10; iInv++)
			{
				m_teams.at(iTeam).at(iPlayer).at(iInv).SetWidth(43.0f);
				m_teams.at(iTeam).at(iPlayer).at(iInv).SetHeight(43.0f);

				eleWidth = m_teams.at(iTeam).at(iPlayer).at(iInv).GetWidth();
				eleHeight = m_teams.at(iTeam).at(iPlayer).at(iInv).GetHeight();
				pos = m_teams.at(iTeam).at(iPlayer).at(iInv).GetPosition();
				eleBounds = m_teams.at(iTeam).at(iPlayer).at(iInv).GetBounds();

				eleBounds->left = elementLeft;
				eleBounds->top = rowTop;
				eleBounds->bottom = rowTop + eleHeight;
				eleBounds->right = elementLeft + eleWidth;

				pos->x = elementLeft;
				pos->z = rowTop;
				
				rowTop += 43.0f;
			}

			rowTop = m_originLeft2.y -20.0f;
			elementLeft += 70.0f;
		}
	}
}

void  StatPanel::SetInvItems()
{
	for (unsigned int iTeam = 0; iTeam < 2; iTeam++)
	{
		m_teams.at(iTeam).resize(5);

		for (unsigned int iPlayer = 0; iPlayer < 5; iPlayer++)
		{
			m_teams.at(iTeam).at(iPlayer).resize(10);

			for (unsigned int iInv = 0; iInv < 10; iInv++)
			{
				if (m_teamControllers.at(iTeam)->at(iPlayer)->GetCharacter()->GetInventory()->at(iInv) !=NULL)
				{
					m_teams.at(iTeam).at(iPlayer).at(iInv).SetWithItemView(
						&m_lightweightItemViews->at(
							m_teamControllers.at(iTeam)->at(iPlayer)->GetCharacter()->GetInventory()->at(iInv)->GetItemClass() ) );
				}
				else m_teams.at(iTeam).at(iPlayer).at(iInv).SetWithItemView(NULL);

				//it we end up neading the state of the item on the stat panel,
				//we could possibly need this later in some kind
				//m_teams.at(iTeam).at(iPlayer).at(iInv).SetItem();
			}
		}
	}
}

void StatPanel::Update(float deltaTime)
{
	//TODO find pace to make inv items setting an event driven call
	SetInvItems();
}

void StatPanel::Render()
{
	switch (m_state)
	{
		case statPanelOpenedItems:
		case statPanelOpenedStats:
			m_background.Render();
			//m_close->Render();

			RenderTeamCollumns(m_yellowTeam, 0);
			RenderTeamCollumns(m_purpleTeam, 1);

			if (m_state == statPanelOpenedStats) m_verticalStats.Render();
			break;

	case statPanelClosed:
	default:
		break;
	}
}

void StatPanel::RenderTeamCollumns(vector<PlayerCharacterController* > * team, unsigned int teamIndex)
{
	if (teamIndex == 0)
	{
		m_fontPosition = { g_clientSizeRect->right/2 - 95, 60, g_clientSizeRect->right, g_clientSizeRect->bottom };
		m_textFont->DrawText(NULL, "Yellow", -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 128));

		m_fontPosition = { (LONG)m_originLeft.x, (LONG)m_originLeft.y, g_clientSizeRect->right, g_clientSizeRect->bottom };
	}

	else if (teamIndex == 1)
	{
		m_fontPosition = { 0, 60, g_clientSizeRect->right / 2 + 95, g_clientSizeRect->bottom };
		m_textFont->DrawText(NULL, "Purple", -1, &m_fontPosition, DT_RIGHT, D3DCOLOR_XRGB(192, 128, 192));
		
		m_fontPosition = { (LONG)m_originRight.x,(LONG)m_originRight.y, g_clientSizeRect->right, g_clientSizeRect->bottom };
	}
		
	for (unsigned int playerIndex = 0; playerIndex < team->size(); playerIndex++)
	{
		m_fontPosition.top = m_originLeft.y;

		RenderKDA(team->at(playerIndex)->GetCharacter()->GetActor()->GetKDA());
		
		m_fontPosition.top += 90;

		if (m_state == statPanelOpenedItems) RenderItems(team->at(playerIndex));
		else RenderStats(team->at(playerIndex));
		
		m_fontPosition.left += 70;
	}
}

void StatPanel::RenderKDA(PlayerKDA kda)
{
	m_kdaPosition1 = { m_fontPosition.left -38, m_fontPosition.top, m_fontPosition.left + 42, g_clientSizeRect->bottom };


	sprintf_s(m_textBuffer, "%i", kda.kills);
	m_textFont->DrawText(NULL, m_textBuffer, -1, &m_kdaPosition1, DT_CENTER, D3DCOLOR_XRGB(192, 210, 192));

	m_kdaPosition1.top += 40;
	sprintf_s(m_textBuffer, "%i", kda.deaths);
	m_textFont->DrawText(NULL, m_textBuffer, -1, &m_kdaPosition1, DT_CENTER, D3DCOLOR_XRGB(192, 210, 192));

	m_kdaPosition1.top += 40;
	sprintf_s(m_textBuffer, "%i", kda.assists);
	m_textFont->DrawText(NULL, m_textBuffer, -1, &m_kdaPosition1, DT_CENTER, D3DCOLOR_XRGB(192, 210, 192));
}

void StatPanel::RenderItems(PlayerCharacterController * playerCharacterController)
{
	for (unsigned int i = 0; i < m_layoutItems.size(); i++)
	{
		if (m_layoutItems.at(i)->GetIcon() != NULL)
			m_layoutItems.at(i)->Render();
	}
}

void StatPanel::RenderStats(PlayerCharacterController * playerCharacterController)
{
	m_fontPosition.top += 50;

	for (int index = 0; index < 10; index++)
	{
		if (index != 0) m_fontPosition.top += 43;

		switch (index)
		{
		case 0: sprintf_s(m_textBuffer, "Inv: %i  ", *playerCharacterController->GetCharacter()->GetInventoryValue()); break;
		case 1: sprintf_s(m_textBuffer, "%.1f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetMoveSpeed()); break;
		case 2: sprintf_s(m_textBuffer, "%.1f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetRange()); break;
		case 3: sprintf_s(m_textBuffer, "%.1f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetAttackSpeed()); break;
		case 4: sprintf_s(m_textBuffer, "%.0f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetPhysicalDamage()); break;
		case 5: sprintf_s(m_textBuffer, "%.0f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetCatVoodoo()); break;
		case 6: sprintf_s(m_textBuffer, "%.0f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetArmor()); break;
		case 7: sprintf_s(m_textBuffer, "%.0f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetCatVoodooResist()); break;
		case 8: sprintf_s(m_textBuffer, "%.2f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->GetHealthRegen()); break;
		case 9: sprintf_s(m_textBuffer, "%.0f", playerCharacterController->GetCharacter()->GetActor()->GetStats()->m_maxHealth); break;

		}

		m_textFont->DrawText(NULL, m_textBuffer, -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 210, 192));

	}
}


bool StatPanel::ToggleAction(StatPanelState message)
{
	if (m_state == statPanelClosed || message != m_state)
	{
		m_state = message;

		return true;

	}
	else m_state = statPanelClosed;

	return false;
}


void StatPanel::Select(POINT * p)
{

}

void StatPanel::AltSelect(POINT * p)
{

}

bool StatPanel::MouseOver(POINT * p)
{

	if (m_state == statPanelClosed) return false;
	//if (!IsPointInBounds(p)) return false;


	if (m_state == statPanelOpenedItems)
	{
		for (unsigned int i = 0; i < m_layoutItems.size(); i++)
		{
			if (m_layoutItems.at(i)->MouseOver(p)) return true;
		}
	}

	return false;
}

StatPanelState StatPanel::GetState()
{
	return m_state;
}
