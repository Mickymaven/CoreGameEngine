#include "UILayoutAbility.h"

UILayoutAbility::UILayoutAbility()
{
	m_selected = false;
	m_ability = NULL;
}

UILayoutAbility::UILayoutAbility(Ability * ability)
{
	m_ability = ability;
	m_width = 50.0f;
	m_height = 50.0f;
	//m_width = ability->GetUIElement()->GetWidth();
	//m_height = ability->GetUIElement()->GetHeight();
	m_selected = false;
}

UILayoutAbility::~UILayoutAbility()
{

}

void UILayoutAbility::Update(float deltaTime)
{

}

void UILayoutAbility::Render()
{
	RenderAtPosition(m_position.x, m_position.y, m_position.z);
}

void UILayoutAbility::RenderAtPosition(float x, float y, float z)
{
	if (m_abilityView != NULL) m_icon->Render(x, y, z);
}

void UILayoutAbility::Select(POINT * p)
{
	if (IsPointInBounds(p))
		m_callback();
}

void UILayoutAbility::AltSelect(POINT * p)
{

}

bool UILayoutAbility::MouseOver(POINT * p)
{
	if (IsPointInBounds(p))
	{
		if (m_abilityView != NULL)
		{
			m_mouseOverCallback(&m_bounds, m_abilityView->GetTooltip(), m_ability);
			return true;
		}
	}
	return false;
}

bool UILayoutAbility::MouseOverCallBackWithBounds(RECT * bounds)
{
	if (m_abilityView != NULL)
	{
		m_mouseOverCallback(bounds, m_abilityView->GetTooltip(), m_ability);
		return true;
	}

	return false;
}

//access
Ability * UILayoutAbility::GetAbility(){ return m_ability; }
AbilityView * UILayoutAbility::GetAbilityView(){ return m_abilityView; }

//mutators
void UILayoutAbility::SetMouseOverCallback(std::function<void(RECT * bounds, TooltipInfo * tooltipInfo, Ability * ability)> f) 
{ m_mouseOverCallback = f; }
void UILayoutAbility::SetAbility(Ability * ability) { m_ability = ability; }
void UILayoutAbility::SetAbilityView(AbilityView * abilityView) { m_abilityView = abilityView; }
