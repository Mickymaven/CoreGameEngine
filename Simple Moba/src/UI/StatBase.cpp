#include "StatBase.h"

StatBase::StatBase()
{

}

StatBase::~StatBase()
{

}

bool StatBase::Init(TooltipController * tooltipController)
{
	m_itemPositions.resize(10);

	LMVector3 * position = NULL;

	m_fontPosition = { 540, 70, g_clientSizeRect->right, g_clientSizeRect->bottom };

	for (unsigned int i = 0; i < m_itemPositions.size(); i++)
	{
		m_itemPositions.at(i) = LMVector3(
			(float)(m_fontPosition.left + 50 + 38 * i),
			0.0f,
			(float)(m_fontPosition.top - 10) );		
	}



	if (FAILED(
		D3DXCreateFont(g_D3D_Device, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "", &m_textFont) // DEFAULT_QUALITY //FW_BOLD
		))
	{
		MessageBox(NULL, "Failed to load font in StatBase", "Error", MB_OK);
		return false;
	}

	m_fontPosition = { 0, 0, 0, 0 };



	return true;
}


void StatBase::InfoPanelRenderRow(Character * character)
{
	
	RenderRow(character);
	//RenderInvRow(actorController);
}

void StatBase::RenderScore(PlayerKDA kda)
{
	sprintf_s(m_textBuffer, "%i / %i / %i", kda.kills, kda.deaths, kda.assists);

	m_textFont->DrawText(NULL, m_textBuffer, -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 210, 192));

	m_fontPosition.left += 50;

}

void StatBase::RenderInvRow(Character * character)
{
	/*
	int iSize = actorController->GetInventory()->size();
	for (int invIndex = 0; invIndex < iSize; invIndex++)
	{
		if (actorController->GetInventory()->at(invIndex) != NULL)
		{
			actorController->GetInventory()->at(invIndex)->RenderTileVersionAtPosition(
				m_itemPositions.at(invIndex)->x,
				0.0f,
				m_itemPositions.at(invIndex)->z);

		}
	}
	*/
}

void StatBase::RenderRow(Character * character)
{
	//sprintf_s(m_textBuffer, "%f", actor->GetStats()->GetHealth());
	m_fontPosition = { 185, 75, g_clientSizeRect->right, g_clientSizeRect->bottom };

	for (int index = 0; index < 9; index++)
	{
		m_fontPosition.left += 40;

		switch (index)
		{
		case 0:
			sprintf_s(m_textBuffer, "Inv.");
			break;
		case 1:
			sprintf_s(m_textBuffer, "%.1f", character->GetActor()->GetStats()->GetRange());
			break;
		case 2:
			sprintf_s(m_textBuffer, "%.2f", character->GetActor()->GetStats()->GetHealthRegen());
			break;
		case 3:
			sprintf_s(m_textBuffer, "%.0f", character->GetActor()->GetStats()->GetPhysicalDamage());
			break;
		case 4:
			sprintf_s(m_textBuffer, "%.0f", character->GetActor()->GetStats()->GetCatVoodoo());
			break;
		case 5:
			sprintf_s(m_textBuffer, "%.1f", character->GetActor()->GetStats()->GetAttackSpeed());
			break;
		case 6:
			sprintf_s(m_textBuffer, "%.1f", character->GetActor()->GetStats()->GetMoveSpeed());
			break;
		case 7:
			sprintf_s(m_textBuffer, "%.0f", character->GetActor()->GetStats()->GetArmor());
			break;
		case 8:
			sprintf_s(m_textBuffer, "%.0f", character->GetActor()->GetStats()->GetCatVoodooResist());
			break;

		}

		m_textFont->DrawText(NULL, m_textBuffer, -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 210, 192));
		
	}

}

