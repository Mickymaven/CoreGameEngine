#include "UILabelCstr.h"

UILabelCstr::UILabelCstr()
{
}

UILabelCstr::~UILabelCstr()
{
}

bool UILabelCstr::Init(const RECT & rect, FontGroup * fontGroup)
{
	m_bounds = RECT(rect);

	m_font = fontGroup->m_font;
	m_color = &fontGroup->m_color;
	m_format = &fontGroup->m_format;

	sprintf_s(m_formatf, "%%f");

	return true;
}

void UILabelCstr::Render()
{
	m_font->DrawText(NULL, m_cstr, -1, &m_bounds, *m_format, *m_color);
}

void UILabelCstr::Select(POINT * p)
{

}

void UILabelCstr::AltSelect(POINT * p)
{

}

char * UILabelCstr::GetText()
{
	return m_cstr;
}

void UILabelCstr::SetText(const char * text)
{
	//strcpy_s(m_cstr, m_size, text);
	strcpy_s(m_cstr, text);
}

void UILabelCstr::SetText(int i)
{
	sprintf_s(m_cstr, "%i", i);
}

void UILabelCstr::SetText(float f)
{
	sprintf_s(m_cstr, m_formatf, f);
}

void UILabelCstr::SetColor(D3DCOLOR * color)
{
	m_color = color;


}

void UILabelCstr::SetFloatFormat(int whole, int remainder)
{
	sprintf_s(m_formatf, "%%");
	
	char buff[3];

	if (whole > -1)
	{	
		sprintf_s(buff,"%i", whole);
		strcat_s(m_formatf, buff);
	}

	if (remainder > -1)
	{
		strcat_s(m_formatf, ".");
		sprintf_s(buff, "%i", remainder);
		strcat_s(m_formatf, buff);
	}

	strcat_s(m_formatf, "f");

}

