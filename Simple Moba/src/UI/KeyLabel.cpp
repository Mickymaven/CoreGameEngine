#include "KeyLabel.h"


KeyLabel::KeyLabel()
{
	m_font = NULL;
	m_color = NULL;
	m_format = NULL;
}

KeyLabel::KeyLabel(Keylist * keylist)
{
	m_font = NULL;
	m_color = NULL;
	m_format = NULL;

	m_keylist = keylist;
}

KeyLabel::~KeyLabel()
{

}

bool KeyLabel::Init(const RECT & rect, FontGroup * fontGroup, int * key)
{
	if (!UILabel::Init(rect, fontGroup, NULL)) return false;

	SetKeyValue(key);

	return true;
}

void KeyLabel::Render()
{
	m_font->DrawText(NULL, GetInputDefineString(*m_key).c_str(), -1, &m_bounds, *m_format, *m_color);
}

int * KeyLabel::GetKey()
{
	return m_key;
}

void KeyLabel::SetKeyValue(int * key)
{
	m_key = key;
}

Keylist * KeyLabel::GetKeylist()
{
	return m_keylist;
}

void KeyLabel::SetKeylist(Keylist * keylist)
{
	m_keylist = keylist;
}

void KeyLabel::Select(POINT * p)
{
	
}

void KeyLabel::AltSelect(POINT * p)
{

}