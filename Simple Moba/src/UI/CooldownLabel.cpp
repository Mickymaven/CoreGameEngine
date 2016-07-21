#include "CooldownLabel.h"


const char CooldownLabel::m_baseFormatStringAbove[6] = "%5.0f";
const char CooldownLabel::m_baseFormatStringBelow[6] = "%1.1f";

CooldownLabel::CooldownLabel()
{
	m_belowThreshhold = 1.0f;
	m_state = coolTextZero;

	m_fontBelow =nullptr;
	m_colorBelow = nullptr;
	m_formatBelow = nullptr;

}

CooldownLabel::~CooldownLabel()
{
}

bool CooldownLabel::Init(const RECT & rect, FontGroup * aboveFont, FontGroup * belowFont, int belowThreshhold)
{
	m_fontBelow = belowFont->m_font;
	m_colorBelow = &belowFont->m_color;
	m_formatBelow = &belowFont->m_format;

	m_belowThreshhold = belowThreshhold;

	return UILabelCstr::Init(rect, aboveFont);

	return true;
}

void CooldownLabel::Render()
{
	switch (m_state)
	{
	case coolTextZero:return;
	case coolTextBelow:m_fontBelow->DrawText(NULL, m_cstr, -1, &m_bounds, *m_formatBelow, *m_colorBelow); break;
	case coolTextAbove:m_font->DrawText(NULL, m_cstr, -1, &m_bounds, *m_format, *m_color); break; //base class vars
	default:break;
	}
}

void CooldownLabel::SetText(float f)
{
	if (f < 0.0001f)
	{
		m_state = coolTextZero;
		sprintf_s(m_cstr, "");
	}
	else if (f < m_belowThreshhold)
	{
		m_state = coolTextBelow;
		sprintf_s(m_cstr, m_baseFormatStringBelow, f);
	}
	else
	{
		m_state = coolTextAbove;
		sprintf_s(m_cstr, m_baseFormatStringAbove, f);
	}
}
