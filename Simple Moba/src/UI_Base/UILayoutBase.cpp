#include "UILayoutBase.h"

UILayoutBase::UILayoutBase()
{
}

UILayoutBase::~UILayoutBase()
{
}

UIElement * UILayoutBase::GetIcon() { return m_icon; }
bool UILayoutBase::GetIsSelected() { return m_selected; }

void UILayoutBase::SetPosition(float x, float y, float z)
{
	UIBase::SetPosition(x, y, z);

	m_bounds.left = x;
	m_bounds.top = z;
	m_bounds.right = x + m_width;
	m_bounds.bottom = z + m_height;
}

void UILayoutBase::SetCallback(std::function<void()> f) { m_callback = f; }
void UILayoutBase::SetIcon(UIElement * uielement) { m_icon = uielement; }
void UILayoutBase::SetIsSelected(bool state) { m_selected = state; }