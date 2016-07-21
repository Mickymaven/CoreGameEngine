#include "UIKeyDialog.h"

UIKeyDialog::UIKeyDialog() : UIDialogBox()
{
	m_state = keyDialogStateNotChecking;
}

UIKeyDialog::~UIKeyDialog()
{

}

bool UIKeyDialog::Init(
	string title,
	string message,
	ViewProfile * viewProfile,
	ThemeResources * theme,
	LMVector2 * origin,
	LMVector2 * size
	)
{
	m_state = keyDialogStateNotChecking;

	if (!UIMenu::Init(viewProfile, theme, origin, size)) return false;

	m_size = LMVector2(*size);

	RECT rect = { 0, 0, 0, 0 };
	m_titleStr = "Key Dialog";
	m_messageStr = "Set your key now.";
	m_tempLabel = NULL;

	m_background = UIElement(size->x, size->y, "Resources/UI/Menu/Main/GameMainMenu.png");
	if (!m_background.Init()) return false;

	m_apply = UIButton(26.0f, 26.0f, "Resources/UI/Menu/Shared/checked.png");
	if (!m_apply.Init()) return false;
	m_apply.SetCallbackSTDFunction(std::bind(&UIKeyDialog::Apply, this));


	if (!m_title.Init(rect, &theme->m_settingsLabel, &m_titleStr)) return false;
	if (!m_message.Init(rect, &theme->m_settingsLabel, &m_messageStr)) return false;
	if (!m_selectedKey.Init(rect, &theme->m_settingsLabel, &m_selectedKeyMessage)) return false;

	InitPosition(origin, size);

	return true;
}

void UIKeyDialog::InitPosition(LMVector2 * origin, LMVector2 * size)
{
	//UI menu
	m_background.SetPosition(origin->x, 0.0f, origin->y);
	m_close.SetPosition(origin->x + size->x - 15.0f - m_close.GetWidth(), 0.0f, origin->y + 15.0f);

	//UIDialogBox
	m_title.SetBounds(origin->x + 10.0f, origin->y + 10.0f, origin->x + 190.0f, origin->y + 60.0f);
	m_message.SetBounds(origin->x + 10.0f, origin->y + 50.0f, origin->x + 190.0f, origin->y + 100.0f);

	//UIKeyDialog
	m_selectedKey.SetBounds(origin->x + 10.0f, origin->y + 50.0f, origin->x + 190.0f, origin->y + 100.0f);
	m_apply.SetPosition(m_bounds.right - 15.0f - m_apply.GetWidth(), 0.0f, m_bounds.bottom - 15.0f - m_apply.GetHeight());
}

void UIKeyDialog::Update(float deltaTime)
{
	switch (UIKeyDialog::m_state)
	{
	case keyDialogStateChecking: Checking(deltaTime); break;
	case keyDialogStateNotChecking: NotChecking(deltaTime); break;
	}


}

void UIKeyDialog::Render()
{
	if (UIMenu::GetUIMenuState() == menuOpened)
	{
		m_background.Render();
		m_close.Render();

		m_title.Render();



		if (UIKeyDialog::m_state == keyDialogStateChecking)
		{
			m_message.Render();
		}
		else {
			m_selectedKey.Render();
			m_apply.Render();
		}
	}
}

void UIKeyDialog::OnEnterChecking()
{
	found = false;
	m_state = keyDialogStateChecking;
}

void UIKeyDialog::Checking(float deltaTime)
{
	iKey = -1;
	mKey = -1;

	if (m_tempLabel == NULL)//todo delete this is cheap solution to debug
	{
		OnExitChecking();
		OnEnterNotChecking();
		OutputDebugString("Dialog::Checking bad label");
		return;
	}

	for (unsigned int i = 0; i < m_tempLabel->GetKeylist()->keySize; i++)
	{
		if (m_tempLabel->GetKeylist()->keylist[i] == true)
		{
			if (m_gameInputController->GetKeyPress(i, false, false))
			{
				found = true;
				iKey = i;
				m_selectedKeyMessage = "Your new bind is:\n  ";
				m_selectedKeyMessage = m_selectedKeyMessage.append(GetInputDefineString(i));
				break;
			}
		}
	}

	for (unsigned int i = 0; i < m_tempLabel->GetKeylist()->mouseSize; i++)
	{
		if (m_tempLabel->GetKeylist()->mouseList[i] == true)
		{
			if (!m_gameInputController->GetMousePressDownLast(i))
			{
				if (m_gameInputController->GetMousePress(i, false, false))
				{
					found = true;
					mKey = i;


					m_selectedKeyMessage = "Your new bind is:\n";
					if (i == LEFT_BUTTON) m_selectedKeyMessage.append(GetInputDefineString(MO_LEFT_BUTTON));
					else if (i == RIGHT_BUTTON) m_selectedKeyMessage.append(GetInputDefineString(MO_RIGHT_BUTTON));
					else if (i == MIDDLE_BUTTON) m_selectedKeyMessage.append(GetInputDefineString(MO_MIDDLE_BUTTON));
					break;
				}
			}
		}
	}



	if (found)
	{
		OnExitChecking();
		OnEnterNotChecking();
	}
}

void UIKeyDialog::OnExitChecking()
{

}

void UIKeyDialog::OnEnterNotChecking()
{
	m_state = keyDialogStateNotChecking;
}

void UIKeyDialog::NotChecking(float deltaTime)
{

}

void UIKeyDialog::OnExitNotChecking()
{

}

void UIKeyDialog::ExitCurrentState()
{

}

void UIKeyDialog::Activate(KeyLabel * label)
{
	LMVector2 origin(label->GetBounds()->left, label->GetBounds()->bottom);

	m_bounds.left = label->GetBounds()->left;
	m_bounds.top = label->GetBounds()->bottom - 10;

	m_bounds.right = m_bounds.left + m_size.x;
	m_bounds.bottom = m_bounds.top + m_size.y;

	InitPosition(&origin, &m_size);

	m_tempLabel = label;
	//Keylist keylist, int * result
	UIMenu::ExitCurrentState();
	UIMenu::OnEnterOpened();

	UIKeyDialog::ExitCurrentState();
	UIKeyDialog::OnEnterChecking();
}

void UIKeyDialog::Select(POINT * p)
{
	if (IsOpen())
	{
		m_close.Select(p);

		if (UIKeyDialog::m_state == keyDialogStateNotChecking)
		{
			m_apply.Select(p);
		}

		m_gameInputController->ExpendAllTheThings(false, true);
	}
}

void UIKeyDialog::AltSelect(POINT * p)
{
	//if (IsOpen()) {}
}

void UIKeyDialog::Apply()
{
	if (found)
	{
		if (mKey != -1)
		{
			if (mKey == LEFT_BUTTON) *m_tempLabel->GetKey() = MO_LEFT_BUTTON;
			else if (mKey == RIGHT_BUTTON) *m_tempLabel->GetKey() = MO_RIGHT_BUTTON;
			else if (mKey == MIDDLE_BUTTON) *m_tempLabel->GetKey() = MO_MIDDLE_BUTTON;
		}
		else if (iKey != -1) *m_tempLabel->GetKey() = iKey;

	}

	UIMenu::OnExitOpened();
	UIMenu::OnEnterClosed();
}

KeyDialogState UIKeyDialog::GetKeyDialogState() { return m_state; }
void UIKeyDialog::SetInputController(GameInputController * gameInputController) { m_gameInputController = gameInputController; }