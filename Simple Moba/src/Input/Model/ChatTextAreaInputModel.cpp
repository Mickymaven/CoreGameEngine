#include "ChatTextAreaInputModel.h"

ChatTextAreaInputModel::ChatTextAreaInputModel()
{
}

bool ChatTextAreaInputModel::Init(string path)
{

	m_path = "Resources/Settings/ChatTextArea.keys";

	m_keybinds.resize(chatTextAreaActionCount, 0);
	m_keybinds[chatTextAreaActionOpen] = DIK_RETURN;
	m_keybinds[chatTextAreaActionSelect] = MO_LEFT_BUTTON;
	m_keybinds[chatTextAreaActionClose] = DIK_ESCAPE;
	m_keybinds[chatTextAreaActionSend] = DIK_RETURN;
	m_keybinds[chatTextAreaActionLeft] = DIK_LEFT;
	m_keybinds[chatTextAreaActionRight] = DIK_RIGHT;
	m_keybinds[chatTextAreaActionBackspace] = DIK_BACKSPACE;

	m_spamFlags.resize(chatTextAreaActionCount, 0);


	vector<int> inactiveTextArea
	{
		chatTextAreaActionOpen
	};

	vector<int> activeTextArea
	{
		chatTextAreaActionSelect,
		chatTextAreaActionClose,
		chatTextAreaActionSend,
		chatTextAreaActionLeft,
		chatTextAreaActionRight,
		chatTextAreaActionBackspace
	};



	m_actionsforState.resize(2);

	m_actionsforState.at(0) = activeTextArea;
	m_actionsforState.at(1) = inactiveTextArea;

	return true;
}

ChatTextAreaInputModel::~ChatTextAreaInputModel()
{

}