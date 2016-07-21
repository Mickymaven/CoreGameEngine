#include "TabLayoutMenu.h"


TabLayoutMenu::TabLayoutMenu() : UIMenu()
{

}

TabLayoutMenu::~TabLayoutMenu()
{

}

bool TabLayoutMenu::Init()
{	
	return true;
}

void TabLayoutMenu::Select(POINT * p)//is virtual
{

}

void TabLayoutMenu::AltSelect(POINT * p)//is virtual
{

}

bool TabLayoutMenu::SetPage(UIContentArea * contentArea)
{
	if (contentArea != m_page)
	{
		m_page = contentArea;
		return true;
	}
	
	return false;
}

LMVector4 * TabLayoutMenu::GetPageOrigin()
{
	return &m_pageOrigin;
}