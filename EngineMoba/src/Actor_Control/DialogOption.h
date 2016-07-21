#if !defined (DIALOGOPTION_H)
#define DIALOGOPTION_H

enum DialogAction
{
	dialogActionDialog,
	dialogActionDialogAsTrade,
	dialogActionDialogAsBasicScreen,
	dialogActionEvent,
	dialogActionExitPlusEvent,
	dialogActionExit,
	DialogActionCount
};

struct DialogOption
{
	DialogAction m_action;
	int m_actionParameter;
	string m_text;

	DialogOption(DialogAction action, int actionParameter)
	{
		m_action = action;
		m_actionParameter = actionParameter;
	};

};

#endif