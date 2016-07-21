#include "KeyDialogInputModel.h"

KeyDialogInputModel::KeyDialogInputModel()
{}

bool KeyDialogInputModel::Init(string path)
{

	m_path = "Resources/Settings/KeyDialog.keys";

	m_keybinds.resize(keyDialogActionCount, 0);
	m_keybinds[keyDialogActionSelect] = MO_LEFT_BUTTON;
	m_keybinds[keyDialogActionClose] = DIK_ESCAPE;

	m_spamFlags.resize(keyDialogActionCount, 0);

	vector<int> full
	{
		keyDialogActionSelect,
		keyDialogActionClose
	};

	m_actionsforState.resize(1);

	m_actionsforState.at(0) = full;

	return true;
}

KeyDialogInputModel::~KeyDialogInputModel()
{

}