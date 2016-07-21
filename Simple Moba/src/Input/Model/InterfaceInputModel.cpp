#include "InterfaceInputModel.h"

InterfaceInputModel::InterfaceInputModel()
{}

bool InterfaceInputModel::Init(string path)
{

	m_path = "Resources/Settings/InterfaceInput.keys";

	m_keybinds.resize(interfaceActionCount);
	m_keybinds[interfaceActionSelect] = MO_LEFT_BUTTON;
	m_keybinds[interfaceActionAltSelect] = MO_RIGHT_BUTTON;

	m_spamFlags.resize(interfaceActionCount, 0);
	m_spamFlags[interfaceActionSelect] = true;
	m_spamFlags[interfaceActionAltSelect] = true;

	vector<int> full
	{
		interfaceActionSelect,
		interfaceActionAltSelect
	};

	m_actionsforState.resize(1);

	m_actionsforState.at(0) = full;

	return true;
}

InterfaceInputModel::~InterfaceInputModel()
{

}