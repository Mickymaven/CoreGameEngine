#include "UIDialogScreen.h"

ViewProfile * UIDialogScreen::m_viewProfile = nullptr;
ThemeResources * UIDialogScreen::m_theme = nullptr;

std::function<void(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option)> UIDialogScreen::m_dialogViewChangeCallback;

UIDialogScreen::UIDialogScreen()
{
	m_state = dialogScreenInactive;
	m_inputModel = nullptr;
	//m_options;
}

UIDialogScreen::~UIDialogScreen()
{

}

bool UIDialogScreen::Init(
	ViewProfile * viewProfile,
	ThemeResources * theme)
{
	m_viewProfile = viewProfile;
	m_theme = theme;

	m_dialogOwner = nullptr;


	DialogBehavior::m_openDialogCallback = std::bind(&UIDialogScreen::Reactivate, this);



	//init NPC text
	if (!m_dialogText.Init(m_r, &theme->m_dialogTitle, NULL)) return false;

	//m_dialogText.SetBounds(100, 450, 1100, 480);


	return true;
}


void UIDialogScreen::Update(float deltaTime) // is virtual
{

}

void UIDialogScreen::Render() // is virtual
{

}

/*
void UIDialogScreen::Update(float deltaTime)
{
switch (m_state)
{
case dialogScreenActive:Active(deltaTime); break;
case dialogScreenInactive:Inactive(deltaTime); break;
}
}

void UIDialogScreen::Render()
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
*/

void UIDialogScreen::OnEnterActive()
{
	m_state = dialogScreenActive;
}

void UIDialogScreen::Active(float deltaTime)
{

}

void UIDialogScreen::OnExitActive()
{

}

void UIDialogScreen::OnEnterInactive()
{
	m_state = dialogScreenInactive;
}

void UIDialogScreen::Inactive(float deltaTime)
{

}

void UIDialogScreen::OnExitInactive()
{

}

void UIDialogScreen::ExitCurrentState()
{
	switch (m_state)
	{
	case dialogScreenActive:OnExitActive(); break;
	case dialogScreenInactive:OnExitInactive(); break;
	}
}

DialogScreenState UIDialogScreen::GetDialogScreenState()
{
	return m_state;
}



void UIDialogScreen::ActionForOption(DialogOption * dialogOption)
{
	switch (dialogOption->m_action)
	{

	case dialogActionDialog:				//ActionNextDialog(dialogOption->m_actionParameter); break;
		ActionNextDialogWithClass(m_dialogOwner, dialogOption->m_actionParameter, dialogScreenViewGameShop); break;

	case dialogActionDialogAsTrade:			ActionNextDialogWithClass(m_dialogOwner, dialogOption->m_actionParameter, dialogScreenViewGameShop); break;
	case dialogActionDialogAsBasicScreen:	ActionNextDialogWithClass(m_dialogOwner, dialogOption->m_actionParameter, dialogScreenViewBasic); break;

	case dialogActionEvent:					ActionEvent(m_dialogOwner, dialogOption->m_actionParameter); break;

		//case dialogActionEventTradeEvent:


	case dialogActionExitPlusEvent:			/* followed by case fallthrough */ActionEvent(m_dialogOwner, dialogOption->m_actionParameter);
	
	//event intentional case fallthrough to action exit..
	case dialogActionExit:					ExitCurrentState(); OnEnterInactive(); break;

	}
}

void UIDialogScreen::Reactivate()
{
	SetOptions(m_dialogOwner->GetNPCController()->GetInteractionController()->ActionRequestDialogScreen());
	SetAsActive();
}

void UIDialogScreen::SetAsActive()
{
	ExitCurrentState();
	OnEnterActive();
}

void UIDialogScreen::SetDialogModel(NPCView * npcView)
{
	m_dialogOwner = npcView;
	m_dialogBehavior = m_dialogOwner->GetNPCController()->GetDialogBehavior();
}

void UIDialogScreen::Activate(NPCView * npcView)
{
	SetDialogModel(npcView);
	Reactivate();
}

void UIDialogScreen::ActionNextDialog(int index)
{

	//SetOptions(m_dialogBehavior->GetOptionsByScreenIndex(index));
	//m_dialogViewChangeCallback(npcController, index, (DialogScreenViewOptions)classEnum);
}



void UIDialogScreen::SetOptions(int index)
{
	SetOptions(m_dialogBehavior->GetOptionsByScreenIndex(index));
}

void UIDialogScreen::SetOptions(DialogScreenData * data)
{
	m_dialogText.SetText(&data->m_dialogText);

	m_options.resize(data->m_options.size());

	for (unsigned int i = 0; i < data->m_options.size(); i++)
	{
		m_options.at(i).Init(m_r, &m_theme->m_dialogLabel);

		m_options.at(i).SetBounds(100, 520 + 50 * i, 1100, 550 + 50 * i);
		m_options.at(i).SetDialogOption(data->m_options.at(i));
		m_options.at(i).SetText(&data->m_options.at(i)->m_text);
	}
}

void UIDialogScreen::ActionEvent(NPCView * npcView, int index)
{
	npcView->GetNPCController()->GetInteractionController()->ActionEvent(index);
}

void UIDialogScreen::SetDialogViewChangeCallback(std::function<void(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option)> f)
{
	m_dialogViewChangeCallback = f;
}

void UIDialogScreen::ActionNextDialogWithClass(NPCView * npcView, int index, DialogScreenViewOptions classEnum)
{
	m_dialogViewChangeCallback(npcView, index, (DialogScreenViewOptions)classEnum);
}