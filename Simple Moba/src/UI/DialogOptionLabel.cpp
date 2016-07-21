#include "DialogOptionLabel.h"


DialogOptionLabel::DialogOptionLabel()
{
	m_font = NULL;
	m_color = NULL;
	m_format = NULL;
}

DialogOptionLabel::~DialogOptionLabel()
{

}

bool DialogOptionLabel::Init(const RECT & rect, FontGroup * fontGroup)
{
	if (!UILabel::Init(rect, fontGroup, NULL)) return false;

	return true;
}

void DialogOptionLabel::Render()
{
	m_font->DrawText(NULL, (*m_text).c_str(), -1, &m_bounds, *m_format, *m_color);

	//m_font.DrawText(NULL, "This is a DialogOptionLabel. ", -1, &m_bounds, *m_format, *m_color);
}

DialogOption * DialogOptionLabel::GetDialogOption()
{
	return m_dialogOption;
}

void DialogOptionLabel::SetDialogOption(DialogOption* dialogOption)
{
	m_dialogOption = dialogOption;
}

void DialogOptionLabel::Select(POINT * p)
{

}

void DialogOptionLabel::AltSelect(POINT * p)
{

}