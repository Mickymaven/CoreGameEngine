#include "DevInputModel.h"

DevInputModel::DevInputModel()
{}

bool DevInputModel::Init(string path)
{

	m_path = "Resources/Settings/DevInput.keys";

	m_keybinds.resize(devActionCount);
	m_keybinds[devActionLevelCharacter] = DIK_APOSTROPHE;
	m_keybinds[devActionTeleportChar] = DIK_C;
	m_keybinds[devActionHalfHealth] = DIK_O;
	m_keybinds[devTogglePathEnabled] = DIK_P;
	m_keybinds[devActionToggleDebugText] = DIK_BACKSLASH;


	m_spamFlags.resize(devActionCount, 0);

	m_spamFlags[devActionTeleportChar] = true;

	vector<int> full
	{
		devActionLevelCharacter,
		devActionTeleportChar,
		devActionHalfHealth,
		devTogglePathEnabled,
		devActionToggleDebugText
	};

	m_actionsforState.resize(1);

	m_actionsforState.at(0) = full;

	return true;
}

DevInputModel::~DevInputModel()
{

}
