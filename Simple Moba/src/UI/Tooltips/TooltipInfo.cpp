#include "TooltipInfo.h"

LPD3DXFONT TooltipInfo::m_nameFont = NULL;

LPD3DXFONT TooltipInfo::m_textFont = NULL;

RECT TooltipInfo::m_fontPosition = { 0, 0, 0, 0 };

TooltipInfo::TooltipInfo()
{
	m_name = NULL;

	if (m_nameFont == NULL)
	{
		D3DXCreateFont(g_D3D_Device, 25, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "", &m_nameFont);
	}

	if (m_textFont == NULL)
	{
		D3DXCreateFont(g_D3D_Device, 20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "", &m_textFont);
	}
}

TooltipInfo::~TooltipInfo()
{
}

void TooltipInfo::Render()
{
	
}

void TooltipInfo::RenderEffect(TooltipEffect * effect)
{
	
	string str, substring;

	const int lineLength = 45;
	
	str.append(effect->descFirst + " ");
	str.append(effect->m_number + " ");
	str.append(effect->m_type + " ");
	str.append(effect->descSecond + " ");


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

const string * TooltipInfo::GetName() { return m_name; }

UIElement * TooltipInfo::GetBackground()
{
	return NULL;
}

void TooltipInfo::SetName(string * name)
{
	m_name = name;
}
