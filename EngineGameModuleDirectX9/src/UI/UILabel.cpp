#include "UILabel.h" 

UILabel::UILabel() : UIBase()
{
	m_font = NULL;
	m_color = NULL;
	m_format = NULL;
}

UILabel::~UILabel()
{

}

bool UILabel::Init(const RECT & rect, FontGroup * fontGroup, string * text)
{

	m_bounds = RECT(rect);

	m_font = fontGroup->m_font;
	m_color = &fontGroup->m_color;
	m_format = &fontGroup->m_format;

	if (text != NULL) m_text = text;

	return true;
}

void UILabel::Render()
{
	m_font->DrawText(NULL, m_text->c_str(), -1, &m_bounds, *m_format, *m_color);
}

void UILabel::SetText(string * text)
{
	m_text = text;
}


void UILabel::Select(POINT * p)//is virtual
{}

void UILabel::AltSelect(POINT * p)//is virtual
{}