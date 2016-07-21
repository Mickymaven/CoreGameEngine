#if !defined(UICHAT_H)
#define UICHAT_H

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UITextInput.h"

#include "../../../EngineMoba/src/Player/ChatModel.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

struct MessageLine
{
	int lineNumber;
	D3DCOLOR color;
	char array[128];
	ChatMessage * m_chatMessage;
	LMVector3 m_bounds;
};


class UIChat : public UIArea
{
	ChatModel * m_chatModel;

	vector<MessageLine> m_messageLine;

	LPD3DXFONT m_font;
	D3DCOLOR * m_color;
	DWORD * m_format;

	UITextInput m_textInput;
	bool m_textInputActive;

	MessageLine m_input;
	UIElement m_background;

public:
	UIChat();
	~UIChat();

	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * theme,
		ChatModel * chatModel);

	void Update(float deltaTime);
	void Render();

	void AddMessage(char * message, int size);

	void ActionOpen();
	void ActionClose();
	void ActionSend();
	void ActionLeft();
	void ActionRight();
	void ActionBackspace();

	void ActionActivateTextInput();

	bool IsInputActive();

	UITextInput * GetInputBox();
};

#endif