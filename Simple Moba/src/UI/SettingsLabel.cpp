#include "SettingsLabel.h"


SettingsLabel::SettingsLabel()
{
	m_font = NULL;
	m_color = NULL;
	m_format = NULL;
}

SettingsLabel::~SettingsLabel()
{

}

bool SettingsLabel::Init(const RECT & rect, FontGroup * fontGroup, string * text)
{
	if (!UILabel::Init(rect,fontGroup, text)) return false;
	
	return true;
}

void SettingsLabel::Render()
{
	m_font->DrawText(NULL, m_text->c_str(), -1, &m_bounds, *m_format, *m_color);
}