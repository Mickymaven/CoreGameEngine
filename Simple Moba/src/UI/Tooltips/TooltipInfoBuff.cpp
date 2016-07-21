#include "TooltipInfoBuff.h"


UIElement TooltipInfoBuff::m_background;

TooltipInfoBuff::TooltipInfoBuff()
{
	
	//left top right bottom
	//m_tooltipZone = { position.x - m_zoneSpill, position.z + 170.0f + m_zoneSpill, g_clientSizeRect->right + m_zoneSpill, g_clientSizeRect->bottom - m_zoneSpill};
	//m_mouseover = { position.x, position.z, position.x + 50.0f, position.z - 50.0f };
}

TooltipInfoBuff::~TooltipInfoBuff()
{
	//delete m_effects;
	//m_effects = NULL;
}

void TooltipInfoBuff::Render()
{
	m_background.Render();

	m_fontPosition.left = static_cast<LONG>(m_background.GetPosition()->x + 20.0f);
	m_fontPosition.top = static_cast<LONG>(m_background.GetPosition()->z + 20.0f);
	m_fontPosition.right = static_cast<LONG>(g_clientSizeRect->right);
	m_fontPosition.bottom = static_cast<LONG>(g_clientSizeRect->bottom);
	m_nameFont->DrawText(NULL, m_name->c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
	
	string str, substring;

	const int lineLength = 45;
	for (unsigned int index = 0; index < m_effects->size(); index++)
	{
		str.append(m_effects->at(index).descFirst + " ");
		str.append(m_effects->at(index).m_number + " ");
		str.append(m_effects->at(index).m_type + " ");
		str.append(m_effects->at(index).descSecond + " ");
	}

	for (unsigned int strIndex = 0; str.length() > strIndex * lineLength; strIndex++)
	{
		if ((float)str.length() >= (strIndex * lineLength) + lineLength)
		{
			substring = str.substr(strIndex * lineLength, lineLength);
		}

		else if ((float)str.length() > strIndex * lineLength)
		{
			substring = str.substr(strIndex * lineLength, str.length() - (strIndex * lineLength));
		}
		m_fontPosition.top += (LONG)26;
		m_textFont->DrawText(NULL, substring.c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));

	}
}

UIElement * TooltipInfoBuff::GetBackground()
{
	return &m_background;
}

void TooltipInfoBuff::SetEffects(vector<TooltipEffect> * effects)
{
	m_effects = effects;
}