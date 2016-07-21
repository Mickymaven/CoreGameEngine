#include "UIButton.h"


UIButton::UIButton()
{

}

UIButton::UIButton(float width, float height, string path) :UIElement(width,height,path)
{

}

UIButton::~UIButton()
{

}

void UIButton::SetCallbackSTDFunction(std::function<void()> f)
{
	m_callback = f;
}

void UIButton::OnClick()
{
	m_callback();
}

void UIButton::Select(POINT * p)
{
	if (IsPointInBounds(p))
	{
		OnClick();
	}
}

void UIButton::AltSelect(POINT * p)
{

}

void UIButton::SetPosition(LMVector3 * position) 
{
	UIBase::SetPosition(position);
}

void UIButton::SetPosition(float x, float y, float z)
{
	UIBase::SetPosition(x, y, z);

	m_bounds.left = x;
	m_bounds.top = z;
	m_bounds.right = x + m_width;
	m_bounds.bottom = z + m_height;
}