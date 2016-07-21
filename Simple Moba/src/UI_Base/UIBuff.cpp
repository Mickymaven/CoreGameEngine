#include "UIBuff.h"


UIBuff::UIBuff()
{
	m_selected = false;
	m_buff = NULL;
	m_buffView = NULL;
	m_icon = NULL;
	m_height = 0.0f;
	m_width = 0.0f;

}

UIBuff::~UIBuff()
{

}

void UIBuff::Update(float deltaTime)
{

}

void UIBuff::Render()
{
	RenderAtPosition(m_position.x, m_position.y, m_position.z);
}

void UIBuff::RenderAtPosition(float x, float y, float z)
{
	if (m_buffView != NULL) m_icon->Render(x, y, z);
}

void UIBuff::Select(POINT * p)
{
	if (IsPointInBounds(p))
		m_callback();
}

void UIBuff::AltSelect(POINT * p)
{

}

bool UIBuff::MouseOver(POINT * p)
{
	if (IsPointInBounds(p))
	{
		if (m_buffView != NULL && m_icon != NULL)
		{
			m_mouseOverCallback(&m_bounds, m_buffView->GetTooltip());
			return true;
		}
	}
	return false;
}

bool UIBuff::MouseOverCallBackWithBounds(RECT * bounds)
{
	if (m_buffView != NULL)
	{
		m_mouseOverCallback(bounds, m_buffView->GetTooltip());
		return true;
	}

	return false;
}

Buff * UIBuff::GetBuff() { return m_buff; }
BuffView * UIBuff::GetBuffView() { return m_buffView; }


void UIBuff::SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfo * tooltipInfo)> f) { m_mouseOverCallback = f; }
void UIBuff::SetBuff(Buff * buff){ m_buff = buff; }
void UIBuff::SetBuffView(BuffView * buffView) { m_buffView = buffView; }