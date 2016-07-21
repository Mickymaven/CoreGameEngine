#include "UIBasicDialogScreen.h"

UIBasicDialogScreen::UIBasicDialogScreen()
{
	m_state = dialogScreenInactive;
	m_inputModel = nullptr;
	//m_options;
}

UIBasicDialogScreen::~UIBasicDialogScreen()
{

}

bool UIBasicDialogScreen::Init(
	ViewProfile * viewProfile,
	ThemeResources * theme)
{
	if (!UIDialogScreen::Init(viewProfile, theme)) return false;

	m_r = { 0, 0, 0, 0 };

	//background 
	m_background = UIElement(1280.0f, 400.0f, "Resources/Themes/Forest/Dialog/background.png");
	if (!m_background.Init()) return false;
	
	m_background.SetPosition(0.0f, 0.0f, 350.0f);


	//init NPC text

	m_dialogText.SetBounds(100, 450, 1100, 480);




	return true;
}

void UIBasicDialogScreen::Update(float deltaTime)
{
	switch (m_state)
	{
	case dialogScreenActive:Active(deltaTime); break;
	case dialogScreenInactive:Inactive(deltaTime); break;
	}
}

void UIBasicDialogScreen::Render()
{
	if (m_state == dialogScreenActive)
	{
		m_background.Render();
		m_dialogText.Render();

		for (unsigned int i = 0; i < m_options.size(); i++)
		{
			m_options.at(i).Render();
		}
	}
}

void UIBasicDialogScreen::Select(POINT * p)
{
	if (m_state == dialogScreenInactive) return;

	//if (!IsPointInBounds(p)) return;

	for (unsigned int i = 0; i < m_options.size(); i++)
	{
		//m_options.at(i).Select(p);
		if (m_options.at(i).IsPointInBounds(p))
		{
			ActionForOption(m_options.at(i).GetDialogOption());
		}
	}
}

void UIBasicDialogScreen::AltSelect(POINT * p)
{

}