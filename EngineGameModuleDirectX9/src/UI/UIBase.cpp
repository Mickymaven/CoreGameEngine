#include "UIBase.h"

UIBase::UIBase()
{

}

UIBase::~UIBase()
{

}

void UIBase::Render()
{

}

LMVector3 * UIBase::GetPosition()
{
	return &m_position;
}

RECT * UIBase::GetBounds()
{
	return &m_bounds;
}

float UIBase::GetWidth()
{
	return m_width;
}

float UIBase::GetHeight()
{
	return m_height;
}

void UIBase::SetPosition(LMVector3 * position)
{
	m_position.x = position->x;
	m_position.y = position->y;
	m_position.z = position->z;
}

void UIBase::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void UIBase::SetBounds(long left, long top, long right, long bottom)
{
	m_bounds.left = left;
	m_bounds.top = top;
	m_bounds.right = right;
	m_bounds.bottom = bottom;

	m_position.x = left;
	m_position.z = top;
}

void UIBase::SetWidth(float width)
{
	m_width = width;
}

void UIBase::SetHeight(float height)
{
	m_height = height;
}

bool UIBase::IsPointInBounds(POINT * p)
{
	if (p->x > m_bounds.left)
	{
		if (p->x < m_bounds.right)
		{
			if (p->y > m_bounds.top)
			{
				if (p->y < m_bounds.bottom)
				{
					//OutputDebugString("We go a hit in a UITestable\n");
					return true;
				}
			}
		}
	}

	return false;
}

void UIBase::Select(POINT * p){}
void UIBase::AltSelect(POINT * p){}