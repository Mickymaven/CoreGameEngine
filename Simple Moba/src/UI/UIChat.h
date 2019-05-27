#if !defined(UICHAT_H)
#define UICHAT_H

#include "../../../EngineGamePlatform/src/Application/Globals.h" //todo bad?


#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UITextInput.h"


#include "../../../CoreGame/src/Gamestate/CoreGameState.h"
#include "../../../EngineMoba/src/Player/ChatModel.h"



#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

struct MessageLine
{
	int lineNumber;
	D3DCOLOR color;
	char chararray[128];
	ChatMessage * m_chatMessage;
	LMVector3 m_bounds;
};

struct MessageScopeCstrGroup
{
	char team[16];
	char whisper[16];
	char global[16];

	D3DCOLOR teamColor;
	D3DCOLOR whisperColor;
	D3DCOLOR globalColor;
};

enum ChatMessageInputScope
{
	msgScopeTeam,
	msgScopeWhisper,
	msgScopeGlobal,
	msgScopeCount
};


class UIChat : public UIArea
{
	CoreGameState * m_coreGameState;

	ChatModel * m_chatModel;

	vector<MessageLine> m_messageLine;

	LPD3DXFONT m_font;
	D3DCOLOR * m_color;
	DWORD * m_format;

	UITextInput m_textInput;
	bool m_textInputActive;

	MessageLine m_input;
	UIElement m_background;

	unsigned int m_msgLimit;

	int m_msgFrameEndIndex;
	bool m_isFrameEndStickingOn;

	ChatMessageInputScope m_currentInputMessageScope;

	bool m_isWhisperOn;
	unsigned short m_whisperID;

	UILabelCstr m_scopeLabel;

	string m_scopeString;

	MessageScopeCstrGroup m_scopeCstrGroup;

public:
	UIChat();
	~UIChat();

	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * theme,
		CoreGameState * coreGameState);

	void Update(float deltaTime);
	void Render();

	void AddMessage(char * message, int size);

	void ActionOpen();
	void ActionClose();
	void ActionSend();
	void ActionLeft();
	void ActionRight();
	void ActionBackspace();
	void ActionScrollUp();
	void ActionScrollDown();
	void ActionCycleScope();

	void SetCycleLabelCstr();

	D3DCOLOR * GetColorWithScope(ChatMessageInputScope scope);

	void ActionActivateTextInput();

	bool IsInputActive();

	UITextInput * GetInputBox();
};

#endif