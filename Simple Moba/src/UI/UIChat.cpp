#include "UIChat.h"

UIChat::UIChat()
{
}

UIChat::~UIChat()
{
}

bool UIChat::Init(ViewProfile * viewProfile, ThemeResources * theme, CoreGameState * coreGameState)
{
	m_msgLimit = 10;

	m_bounds.left = 50;
	m_bounds.right = 900;

	m_bounds.top = 600;
	m_bounds.bottom = 650;

	m_font = theme->m_mediumPlainText.m_font;
	m_color = &theme->m_mediumPlainText.m_color;
	m_format = &theme->m_mediumPlainText.m_format;
	
	LMVector4 inputBounds = LMVector4(m_bounds.left, m_bounds.top, m_bounds.right, m_bounds.bottom);


	if (!m_textInput.Init(&theme->m_mediumPlainText, &inputBounds, "", 0, textInputActive)) return false;

	m_coreGameState = coreGameState;
	m_chatModel = coreGameState->GetChatModel();

	m_textInputActive = false;


	m_background = UIElement(250.0f, 40.0f, "Resources/Themes/Forest/Dialog/background.png");
	if (!m_background.Init()) return false;

	m_background.SetPosition((float)m_bounds.left - 8, 0.0f, (float)m_bounds.top - 8);


	m_msgFrameEndIndex = m_chatModel->GetCurrentIndex();
	m_isFrameEndStickingOn = true;

	m_currentInputMessageScope = msgScopeGlobal;
	m_isWhisperOn = true;
	m_whisperID = 1;

	RECT scopeLabelBounds = { m_bounds.left - 50, m_bounds.bottom - 50, m_bounds.left-10, m_bounds.bottom };



	if (!m_scopeLabel.Init(scopeLabelBounds, &theme->m_mediumPlainText)) return false;

	strcpy(m_scopeCstrGroup.global, "All");
	strcpy(m_scopeCstrGroup.whisper, "Whisper");
	strcpy(m_scopeCstrGroup.team, "Team");

	m_scopeCstrGroup.globalColor = D3DCOLOR_XRGB(240, 240, 140);
	m_scopeCstrGroup.teamColor = D3DCOLOR_XRGB(140, 240, 96);
	m_scopeCstrGroup.whisperColor = D3DCOLOR_XRGB(240, 140, 96);




	SetCycleLabelCstr();//must be after groupCstr and current cycle state


	return true;
}

void UIChat::Update(float deltaTime)
{
	m_textInput.Update(deltaTime, 0);
}

void UIChat::Render()
{
	if (m_textInput.GetState() == textInputActive)
	{
		m_background.Render();
		m_textInput.Render();
		m_scopeLabel.Render();
	}

	int messagesToRender = m_chatModel->GetMessageCount();

	if (messagesToRender > m_msgLimit) messagesToRender = m_msgLimit;

	int currentMessageIndex = m_chatModel->GetCurrentIndex();


	m_messageLine.resize(messagesToRender);


	//(LONG)(m_background.GetPosition()->x + 20.0f), (LONG)(m_background.GetPosition()->z + 20.0f),


	RECT bounds = { m_bounds.left, m_bounds.top - 28, g_clientSizeRect->right, g_clientSizeRect->bottom };


	int workingIndex;
	if (m_isFrameEndStickingOn) workingIndex = currentMessageIndex;
	else workingIndex = m_msgFrameEndIndex;

	int userTeam = 1;
	int messageTeam = 1;
	ChatMessageTarget messageTargetScope = targetGlobal;


	string * stringDest = nullptr;

	
	for (unsigned int i = 0; i < m_msgLimit; i++)
	{
		if (i < m_messageLine.size())
		{			
			m_messageLine.at(i).m_chatMessage = &m_chatModel->GetMessages()->at(workingIndex);

			stringDest = nullptr;

			m_coreGameState->GetGameConfiguration()->GetNameByPlayerID(&stringDest, &m_messageLine.at(i).m_chatMessage->m_playerID);


			if (stringDest!=nullptr)
			{			
				strcpy(m_messageLine.at(i).chararray, "[");
				strcat_s(m_messageLine.at(i).chararray, (*stringDest).c_str());
				strcat_s(m_messageLine.at(i).chararray, "] ");
				strcat_s(m_messageLine.at(i).chararray, m_messageLine.at(i).m_chatMessage->m_text);

				switch (m_messageLine.at(i).m_chatMessage->m_messageTarget) {
					case targetGlobal: m_messageLine.at(i).color = m_scopeCstrGroup.globalColor; break;
					case targetTeam: m_messageLine.at(i).color = m_scopeCstrGroup.teamColor; break;
					case targetPlayer: m_messageLine.at(i).color = m_scopeCstrGroup.whisperColor; break;
					default: break;
				}

				m_font->DrawText(NULL, m_messageLine.at(i).chararray, -1, &bounds, DT_LEFT, m_messageLine.at(i).color);
			}
			workingIndex = m_chatModel->GetPreviousIndex(workingIndex);

			bounds.top -= 28.0f;
			bounds.bottom -= 28.0f;
		}

	}



}

void UIChat::AddMessage(char * message, int size)
{
}

void UIChat::ActionOpen()
{
	m_textInput.ActionActivate();
	m_textInput.SetColor(GetColorWithScope(m_currentInputMessageScope));
}

void UIChat::ActionClose()
{
	m_textInput.ActionDeactivate();
}

void UIChat::ActionSend()
{
	char x;

	std::memcpy(&x, m_textInput.GetText(), 1);

	if (x == '\0')
	{
		m_textInput.ActionUseDeactivate();

		return;
	}


	//do something then deactivate
	ChatMessage * pChatMessage = m_chatModel->GetNextFreeMessageAndIncrement();
	
	std::memcpy(pChatMessage->m_text, m_textInput.GetText(), 64);
	pChatMessage->m_playerID = m_coreGameState->GetPlayerID();
	pChatMessage->m_teamID = m_coreGameState->GetControlledActor()->GetTeam();

	switch (m_currentInputMessageScope)
	{
	case msgScopeTeam: pChatMessage->m_messageTarget = targetTeam;  break;
	case msgScopeWhisper: pChatMessage->m_messageTarget = targetPlayer;  break;
	case msgScopeGlobal: pChatMessage->m_messageTarget = targetGlobal;  break;
	case msgScopeCount:	default: break;

	}


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

void UIChat::ActionScrollUp()
{
	m_msgFrameEndIndex -= 1;
	if (m_msgFrameEndIndex < 0) m_msgFrameEndIndex = 0;
	m_isFrameEndStickingOn = false;

}

void UIChat::ActionScrollDown()
{
	m_msgFrameEndIndex += 1;

	if (m_msgFrameEndIndex >= m_chatModel->GetCurrentIndex())
	{
		m_msgFrameEndIndex = m_chatModel->GetCurrentIndex();
		m_isFrameEndStickingOn = true;
	}
	else m_isFrameEndStickingOn = false;

}

void UIChat::ActionCycleScope()
{
	switch (m_currentInputMessageScope)
	{
		case msgScopeTeam: 
			if (m_isWhisperOn)
			{
				m_currentInputMessageScope = msgScopeWhisper;
			}
			else m_currentInputMessageScope = msgScopeGlobal;
			
			break;
		case msgScopeWhisper: m_currentInputMessageScope = msgScopeGlobal; break;
		case msgScopeGlobal: m_currentInputMessageScope = msgScopeTeam;  break;
		case msgScopeCount:	default: break;

	}

	m_textInput.SetColor(GetColorWithScope(m_currentInputMessageScope));

	SetCycleLabelCstr();

}

void UIChat::SetCycleLabelCstr()
{
	switch (m_currentInputMessageScope)
	{
	case msgScopeTeam: m_scopeLabel.SetText(m_scopeCstrGroup.team); break;
	case msgScopeWhisper: m_scopeLabel.SetText(m_scopeCstrGroup.whisper); break;
	case msgScopeGlobal: m_scopeLabel.SetText(m_scopeCstrGroup.global);  break;
	case msgScopeCount:	default: break;

	}

	m_scopeLabel.SetColor(GetColorWithScope(m_currentInputMessageScope));

	
}

D3DCOLOR * UIChat::GetColorWithScope(ChatMessageInputScope scope)
{
	switch (scope)
	{
	case msgScopeTeam: return &m_scopeCstrGroup.teamColor;
	case msgScopeWhisper: return &m_scopeCstrGroup.whisperColor;
	case msgScopeGlobal: return &m_scopeCstrGroup.globalColor;
	}

	return &m_scopeCstrGroup.globalColor;
}

void UIChat::ActionActivateTextInput()
{
	m_textInput.ActionActivate();
}

UITextInput *  UIChat::GetInputBox() { return &m_textInput; }

