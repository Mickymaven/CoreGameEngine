#include "UIChat.h"

UIChat::UIChat()
{
}

UIChat::~UIChat()
{
}

bool UIChat::Init(ViewProfile * viewProfile, ThemeResources * theme, ChatModel * chatModel)
{

	m_bounds.left = 50;
	m_bounds.right = 900;

	m_bounds.top = 600;
	m_bounds.bottom = 1000;

	m_font = theme->m_smallText.m_font;
	m_color = &theme->m_smallText.m_color;
	m_format = &theme->m_smallText.m_format;
	
	LMVector4 inputBounds = LMVector4(m_bounds.left, m_bounds.top, m_bounds.right, m_bounds.bottom);


	if (!m_textInput.Init(&theme->m_smallText, &inputBounds, "", 0, textInputActive)) return false;

	m_chatModel = chatModel;

	m_textInputActive = false;

	return true;
}

void UIChat::Update(float deltaTime)
{
	m_textInput.Update(deltaTime, 0);
}

void UIChat::Render()
{
	if (m_textInput.GetState() == textInputActive) m_textInput.Render();

	int messagesToRender = m_chatModel->GetMessageCount();

	if (messagesToRender > 5) messagesToRender = 5;

	int currentMessageIndex = m_chatModel->GetCurrentIndex();


	m_messageLine.resize(messagesToRender);


	//(LONG)(m_background.GetPosition()->x + 20.0f), (LONG)(m_background.GetPosition()->z + 20.0f),


	RECT bounds = { m_bounds.left, m_bounds.bottom - 500, g_clientSizeRect->right, g_clientSizeRect->bottom };


	int workingIndex = currentMessageIndex;

	for (unsigned int i = 0; i < 5; i++)
	{
		if (i < m_messageLine.size())
		{
			m_messageLine.at(i).m_chatMessage = &m_chatModel->GetMessages()->at(workingIndex);

			m_font->DrawText(NULL, m_messageLine.at(i).m_chatMessage->m_text, -1, &bounds, DT_LEFT, *m_color);

			workingIndex = m_chatModel->GetPreviousIndex(workingIndex);

			bounds.top -= 20.0f;
			bounds.bottom -= 20.0f;
		}

	}



}

void UIChat::AddMessage(char * message, int size)
{
}

void UIChat::ActionOpen()
{
	m_textInput.ActionActivate();
}

void UIChat::ActionClose()
{
	m_textInput.ActionDeactivate();
}

void UIChat::ActionSend()
{
	//do something then deactivate
	ChatMessage * pChatMessage = m_chatModel->GetNextFreeMessageAndIncrement();
	
	std::memcpy(pChatMessage->m_text, m_textInput.GetText(), 64);

	//m_chatModel->IncrementMessageCount();

	m_textInput.ActionUseDeactivate();
}

void UIChat::ActionLeft()
{
}

void UIChat::ActionRight()
{
}

void UIChat::ActionBackspace()
{
	m_textInput.Backspace();
}

void UIChat::ActionActivateTextInput()
{
	m_textInput.ActionActivate();
}

UITextInput *  UIChat::GetInputBox() { return &m_textInput; }

