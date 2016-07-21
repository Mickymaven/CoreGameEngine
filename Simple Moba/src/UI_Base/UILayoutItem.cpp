#include "UILayoutItem.h"


UILayoutItem::UILayoutItem()
{
	m_selected = false;
	m_item = NULL;
	m_icon = NULL;
	m_itemView = NULL;

}

UILayoutItem::UILayoutItem(Item * item)
{
	m_item = item;
	m_width = m_itemView->GetIcon()->GetWidth();
	m_height = m_itemView->GetIcon()->GetHeight();
	m_selected = false;
}


UILayoutItem::UILayoutItem(Item * item, ItemView * itemView)
{
	m_item = item;
	m_itemView = itemView;
	m_icon = m_itemView->GetIcon();
	m_width = m_itemView->GetIcon()->GetWidth();
	m_height = m_itemView->GetIcon()->GetHeight();
	m_selected = false;
}



UILayoutItem::~UILayoutItem()
{

}

void UILayoutItem::Update(float deltaTime)
{

}

void UILayoutItem::Render()
{
	RenderAtPosition(m_position.x, m_position.y, m_position.z);
}

void UILayoutItem::RenderAtPosition(float x, float y, float z)
{
	if (m_itemView != NULL) m_icon->Render(x,y,z);
}

void UILayoutItem::Select(POINT * p)
{
	if (IsPointInBounds(p))
		m_callback();
}

void UILayoutItem::AltSelect(POINT * p)
{

}

bool UILayoutItem::MouseOver(POINT * p)
{
	if (IsPointInBounds(p))
	{
		if (m_item != NULL)
		{
			//m_itemView->GetAbilityView()->GetAbility()

			m_mouseOverCallback(&m_bounds, m_itemView->GetTooltip(), m_item->GetAbility() );
			return true;
		}
	}
	return false;
}

bool UILayoutItem::MouseOverCallBackWithBounds(RECT * bounds)
{
	if (m_item != NULL)
	{
		//m_itemView->GetAbilityView()->GetAbility()
		m_mouseOverCallback(bounds, m_itemView->GetTooltip(), m_item->GetAbility());
		return true;
	}

	return false;
}

Item * UILayoutItem::GetItem() { return m_item; }
ItemView * UILayoutItem::GetItemView() { return m_itemView; }


void UILayoutItem::SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfoItem * tooltipInfoItem, Ability * ability)> f)
{ m_mouseOverCallback = f; }

void UILayoutItem::SetWithItemView(ItemView * itemView)
{
	if (itemView == NULL)
	{
		m_itemView = NULL;
		m_icon = NULL;
		m_item = NULL;
	}
	else
	{
		m_itemView = itemView;
		m_icon = itemView->GetIcon();
		m_item = itemView->GetItem();
	}

}

void UILayoutItem::SetItem(Item * item){ m_item = item; }
void UILayoutItem::SetItemView(ItemView * itemView){ m_itemView = itemView; }
