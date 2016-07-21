#include "UIMenu.h"

UIMenu::UIMenu()
{
	m_uiMenuState = menuClosed;
}

UIMenu::~UIMenu()
{

}

bool UIMenu::Init(
	ViewProfile * viewProfile,
	ThemeResources * theme,
	LMVector2 * origin,
	LMVector2 * size)
{
	m_close = UIButton(26.0f, 26.0f, "Resources/Shop/Images/shop_close.png");
	if (!m_close.Init()) return false;

	m_close.SetCallbackSTDFunction(std::bind(&UIMenu::CloseMenu, this));
	m_close.SetPosition(origin->x + size->x - 15.0f - m_close.GetWidth(), 0.0f, origin->y + 15.0f);

	return true;
}

void UIMenu::OnEnterOpened()
{
	m_uiMenuState = menuOpened;
}

void UIMenu::Opened(float deltaTime)
{

}

void UIMenu::OnExitOpened()
{

}

void UIMenu::OnEnterClosed()
{
	m_uiMenuState = menuClosed;
}

void UIMenu::Closed(float deltaTime)
{

}

void UIMenu::OnExitClosed()
{

}

void UIMenu::ExitCurrentState()
{
	switch (m_uiMenuState)
	{
	case menuOpened: OnExitOpened(); break;
	case menuClosed: OnExitClosed(); break;
	}
}

UIMenuState UIMenu::GetUIMenuState()
{
	return m_uiMenuState;
}

bool UIMenu::ToggleState()
{
	switch (m_uiMenuState)
	{
	case menuOpened:
		OnExitOpened();
		OnEnterClosed();

		return false; break;
	case menuClosed:
		OnExitClosed();
		OnEnterOpened();

		return true; break;
	}

	m_inputModel->SetState(m_uiMenuState);

	return true;
}

bool UIMenu::IsOpen()
{
	if (m_uiMenuState == menuOpened) return true;

	return false;
}

void UIMenu::CloseMenu()
{
	ToggleState();
	OnExitOpened();
	OnEnterClosed();
}

void UIMenu::Select(POINT * p)//is virtual
{

}
void UIMenu::AltSelect(POINT * p)//is virtual
{

}