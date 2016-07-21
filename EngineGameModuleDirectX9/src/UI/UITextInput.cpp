#include "UITextInput.h"

UITextInput::UITextInput()
{
	m_state = textInputInactive;
}

UITextInput::~UITextInput()
{
}

bool UITextInput::Init(FontGroup * fontGroup, LMVector4 * bounds, char * initText, int cstrSize, TextInputState activeState)
{
	m_font = fontGroup->m_font;
	m_color = &fontGroup->m_color;

	m_leftDWORD = DT_LEFT;


	m_format = &m_leftDWORD;//&fontGroup->m_format;

	m_bounds.left = bounds->left();
	m_bounds.top = bounds->top();
	m_bounds.right = bounds->right();
	m_bounds.bottom = bounds->bottom();
	
	std::memcpy(m_text, initText, cstrSize);

	m_end = cstrSize;

	m_validInput.Init(keylistAcceptableChatCharacters);
	//m_validInput.m_state = keylistAcceptableChatCharacters;


	return true;
}

void UITextInput::Update(float deltaTime, float gameTime)
{
	switch (m_state)
	{
	case textInputActive:Active(deltaTime); break;
	case textInputInactive:Inactive(deltaTime); break;
	}
}

void UITextInput::Render()
{
	if (m_state == textInputActive)
		m_font->DrawText(NULL, m_text, -1, &m_bounds, *m_format, *m_color);
}

bool UITextInput::Char(char key)
{
	if (m_end < 64)
	{
		m_text[m_end] = key;
		m_text[m_end+1] = '\0';
		m_end++;

		return true;
	}

	return false;
}

bool UITextInput::Backspace()
{
	if (m_end > 0)
	{
		m_text[m_end] = '\0';
		m_text[m_end - 1] = '\0';
		m_end--;

		return true;
	}


	m_text[m_end] = '\0';

	return false;
}


void UITextInput::OnEnterActive()
{
	m_state = textInputActive;
}

void UITextInput::Active(float deltaTime)
{

	//int iKey = -1;

	for (int i = 0; i < m_validInput.keySize; i++)
	{
		if (m_validInput.keylist[i] == true)
		{

			if (m_gameInputController->GetKeyPress(i, false, false))
			{
				if (m_gameInputController->GetKeyPressDownLast(i) == false)
				{
					//iKey = i;
					if (UITextInput::Char(CharForKey(i)))
						m_gameInputController->ExpendKey(i);

				}
			}
		}
	}

}

void UITextInput::OnExitActive()
{

}

void UITextInput::OnEnterInactive()
{
	m_state = textInputInactive;
}

void UITextInput::Inactive(float deltaTime)
{

}

void UITextInput::OnExitInactive()
{

}

void UITextInput::ExitCurrentState()
{
	switch (m_state)
	{
	case textInputActive:OnExitActive(); break;
	case textInputInactive:OnExitInactive(); break;
	}
}

TextInputState UITextInput::GetState() { return m_state; }

void UITextInput::ActionUseDeactivate()
{

	std::memset(m_text, NULL, 64);

	m_end = 0;
	m_text[0] = '\0';
	ActionDeactivate();
}

void UITextInput::ActionActivate()
{
	ExitCurrentState();
	OnEnterActive();
}

void UITextInput::ActionDeactivate()
{
	ExitCurrentState();
	OnEnterInactive();
}

char * UITextInput::GetText() { return m_text; }


void UITextInput::SetInputController(GameInputController * gameInputController) { m_gameInputController = gameInputController; }