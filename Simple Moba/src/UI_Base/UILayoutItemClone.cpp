#include "UILayoutItemClone.h"

UILayoutItemClone::UILayoutItemClone()
{
	m_item = NULL;
}

UILayoutItemClone::~UILayoutItemClone()
{

}

void UILayoutItemClone::Render()
{
	if (m_item != NULL)
	{
		m_item->RenderAtPosition(UIBase::m_position.x, UIBase::m_position.y, UIBase::m_position.z);
	}
}

void UILayoutItemClone::Select(POINT * p)
{
	m_item->SetIsSelected(!m_item->GetIsSelected());
}

void UILayoutItemClone::AltSelect(POINT * p)
{
	
}

bool UILayoutItemClone::MouseOver(POINT * p)//is virtual;
{
	if (IsPointInBounds(p))
	{
		if (m_item != NULL)
		{
			if (m_item->MouseOverCallBackWithBounds(&m_bounds)) return true;
		}
	}
	return false;
}


UILayoutItem * UILayoutItemClone::GetUILayoutItem()
{
	return m_item;
}

void UILayoutItemClone::SetUILayoutItem(UILayoutItem * item)
{
	m_item = item;
}