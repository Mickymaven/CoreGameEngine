#include "UILayoutAvatar.h"

UILayoutAvatar::UILayoutAvatar()
{
	m_pcController = nullptr;
	//m_pcView = nullptr;
	m_icon = nullptr;

	//base
	m_callback = nullptr;
	//m_mouseOverCallback = nullptr;
	m_selected = false;

}

UILayoutAvatar::~UILayoutAvatar()
{
}

void UILayoutAvatar::Update(float deltaTime)
{
}

void UILayoutAvatar::Render()
{
	RenderAtPosition(m_position.x, m_position.y, m_position.z);
}

void UILayoutAvatar::RenderAtPosition(float x, float y, float z)
{
	if (m_icon !=nullptr) m_icon->Render(x, y, z);
}

void UILayoutAvatar::Select(POINT * p)
{
	m_callback();
}

void UILayoutAvatar::AltSelect(POINT * p)
{
}

bool UILayoutAvatar::MouseOver(POINT * p)
{
	return false;
}

bool UILayoutAvatar::MouseOverCallBackWithBounds(RECT * bounds)
{
	//m_mouseOverCallback(bounds, m_abilityView->GetTooltip(), m_ability);

	return false;
}

void UILayoutAvatar::SetPlayerCharacter(PlayerCharacterController * pcController) { m_pcController = pcController; }
//void UILayoutAvatar::SetPlayerCharacterView(PlayerCharacterView * pcView) { m_pcView = pcView; }

PlayerCharacterController * UILayoutAvatar::GetPlayerCharacter()
{
	return m_pcController;
}
