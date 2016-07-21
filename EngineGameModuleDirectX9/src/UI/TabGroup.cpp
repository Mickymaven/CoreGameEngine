#include "TabGroup.h"


TabGroup::TabGroup()
{
	m_isVertical = true;
}

TabGroup::~TabGroup()
{
	for (unsigned int i = 0; i < m_tabs.size(); i++)
	{
		delete m_tabs.at(i);
		m_tabs.at(i) = nullptr;
	}
}

bool TabGroup::Init(LMVector2 * origin, LMVector2 * size)
{
	//m_bounds = { origin->x, origin->y, origin->x + size->x, origin->y + size->y };
	
	m_bounds.left = origin->x;
	m_bounds.top = origin->y;
	m_bounds.right = origin->x + size->x;
	m_bounds.bottom = origin->y + size->y;

	PositionContent(&m_bounds);

	return true;
}

void TabGroup::PositionContent(RECT * bounds)
{
	LONG elementTop = bounds->top;
	LONG elementLeft = bounds->left;

	float eleWidth = 0.0f;
	float eleHeight = 0.0f;

	RECT * eleBounds = NULL;


	for (unsigned int i = 0; i < m_tabs.size(); i++)
	{
		eleWidth = m_tabs.at(i)->GetWidth();
		eleHeight = m_tabs.at(i)->GetHeight();

		//m_tabs.at(i)->GetPosition()->x = elementLeft;
		//m_tabs.at(i)->GetPosition()->z = elementTop;

		//m_tabs.at(i)->GetBounds()->left = elementLeft;
		//m_tabs.at(i)->GetBounds()->top = elementTop;
		//m_tabs.at(i)->GetBounds()->bottom = elementTop + eleHeight;
		//m_tabs.at(i)->GetBounds()->right = elementLeft + eleWidth;

		m_tabs.at(i)->SetBounds(elementLeft, elementTop, elementLeft + eleWidth, elementTop + eleHeight);


		if (m_isVertical) elementTop += eleHeight + eleHeight / 10.0f;
		else elementLeft += eleWidth + eleWidth / 10.0f;

	}
}

void TabGroup::CalcPos()
{
	PositionContent(&m_bounds);
}

void TabGroup::Render()
{
	for (unsigned int i = 0; i < m_tabs.size(); i++)
	{
		m_tabs.at(i)->Render();
	}
}

/*
void TabGroup::PushTab(UITab* tab)
{
m_tabs.push_back(tab);
}
*/

bool TabGroup::NewTab(float w, float h, string path, FontGroup * fontGroup, string * labelText, UIContentArea * contentArea, std::function<bool(UIContentArea*)> f)
{
	UITab * tab = new UITab(contentArea, w, h, path);

	if (!tab->Init(fontGroup, labelText)) return false;

	tab->SetCallbackSelectPage(f);

	m_tabs.push_back(tab);


	return true;
}

void TabGroup::Select(POINT * p)
{
	if (IsPointInBounds(p))
	{
		for (unsigned int i = 0; i < m_tabs.size(); i++)
		{
			m_tabs.at(i)->Select(p);
		}
	}
}

void TabGroup::AltSelect(POINT * p)
{
	if (IsPointInBounds(p))
	{
		for (unsigned int i = 0; i < m_tabs.size(); i++)
		{
			m_tabs.at(i)->AltSelect(p);
		}
	}
}

vector < UITab* > *  TabGroup::GetTabs()
{
	return &m_tabs;
}