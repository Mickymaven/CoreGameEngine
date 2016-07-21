#include "TooltipInfoAbility.h"


UIElement TooltipInfoAbility::m_background = UIElement(400.0f, 267.0f, "Resources/misc/ux_tool_tip_ability.png");

TooltipInfoAbility::TooltipInfoAbility()
{
	m_background.Init();
	//left top right bottom
	//m_tooltipZone = { position.x - m_zoneSpill, position.z + 170.0f + m_zoneSpill, g_clientSizeRect->right + m_zoneSpill, g_clientSizeRect->bottom - m_zoneSpill};
	//m_mouseover = { position.x, position.z, position.x + 50.0f, position.z - 50.0f };
}

TooltipInfoAbility::~TooltipInfoAbility()
{

}

void TooltipInfoAbility::Render()
{
	m_background.Render();
	
	//char buffer[1000];
	//sprintf_s(buffer, " str: %s, font POS %f, %f \n", m_name->c_str(),  m_background.GetPosition()->x + 3.0f, g_clientSizeRect->bottom - (m_background.GetPosition()->z + 250.0f - 3.0f));
	//OutputDebugString(buffer);
	m_fontPosition = { (LONG)(m_background.GetPosition()->x + 20.0f), (LONG)(m_background.GetPosition()->z + 20.0f), g_clientSizeRect->right, g_clientSizeRect->bottom };

	m_nameFont->DrawText(NULL, m_name->c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));

	for (unsigned int index = 0; index < m_effects->size(); index++)
	{
		RenderEffect(&m_effects->at(index));
	}

		/*
		sprintf_s(
			buffer2,
			"%s %s %s %s",
			m_effects->at(index).descFirst.c_str(),
			m_effects->at(index).m_number.c_str(),
			m_effects->at(index).m_type.c_str(),
			m_effects->at(index).descSecond.c_str()
			);

		memcpy(subbuffer, &buffer2[0], 40);
		subbuffer[20] = '\0';
		m_fontPosition.top += 26.0f;
		m_textFont->DrawText(NULL, subbuffer, -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
		*/


		/*
		m_fontPosition = { m_background.GetPosition()->x + 7.0f,
			m_fontPosition.top, g_clientSizeRect->right, g_clientSizeRect->bottom };
		m_textFont->DrawText(NULL, m_effects->at(index).descFirst.c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
		
		sprintf_s(buffer, "%s %s ", m_effects->at(index).m_number.c_str(), m_effects->at(index).m_type.c_str());
		

		m_fontPosition.top += 26.0f;

		m_fontPosition = { m_background.GetPosition()->x + 7.0f,
			m_fontPosition.top, g_clientSizeRect->right, g_clientSizeRect->bottom };
		m_textFont->DrawText(NULL, buffer, -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
		*/

	//sprintf_s(m_buffer, "dev build %s ", __DATE__);
}

UIElement * TooltipInfoAbility::GetBackground()
{
	return &m_background;
}

void TooltipInfoAbility::SetEffects(vector<TooltipEffect> * effects)
{
	m_effects = effects;
}