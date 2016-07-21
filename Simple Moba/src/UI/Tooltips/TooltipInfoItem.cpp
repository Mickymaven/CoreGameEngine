#include "TooltipInfoItem.h"


UIElement TooltipInfoItem::m_background;

TooltipInfoItem::TooltipInfoItem()
{
	m_background.Init();

}

TooltipInfoItem::~TooltipInfoItem()
{

}

void TooltipInfoItem::Render()
{
	m_background.Render();

	m_fontPosition.left = static_cast<LONG>(m_background.GetPosition()->x + 20.0f);
	m_fontPosition.top = static_cast<LONG>(m_background.GetPosition()->z + 20.0f);
	m_fontPosition.right = static_cast<LONG>(g_clientSizeRect->right);
	m_fontPosition.bottom = static_cast<LONG>(g_clientSizeRect->bottom);

	m_nameFont->DrawText(NULL, m_name->c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));


	string str;
		

	for (unsigned int index = 0; index < m_stats->size(); index++)
	{

	if (m_stats->at(index).fNumber > 0) str = "+";


		str.append(m_stats->at(index).number + " " + m_stats->at(index).name);

		m_fontPosition.top += 26;
		m_textFont->DrawText(NULL, str.c_str(), -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
		str = "";
	}

	m_fontPosition.top += 39;

	
	if (m_effects!=NULL)
	{
		for (unsigned int index = 0; index < m_effects->size(); index++)
		{

			if (index == 0)
			{
				m_textFont->DrawText(NULL, "Active:", -1, &m_fontPosition, DT_LEFT, D3DCOLOR_XRGB(192, 192, 192));
			}
			RenderEffect(&m_effects->at(index));
		}
	}
	
}

UIElement * TooltipInfoItem::GetBackground()
{
	return &m_background;
}

void TooltipInfoItem::SetStats(vector<TootipItemStat> * stats)
{
	m_stats = stats;
}

void TooltipInfoItem::SetEffects(vector<TooltipEffect> * effects)
{
	m_effects = effects;
}