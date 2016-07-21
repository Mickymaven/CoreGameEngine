#include "DialogBehavior.h"
#include "DialogBehavior.h"
#include "DialogBehavior.h"
#include "DialogBehavior.h"
#include "DialogBehavior.h"

std::function<void()> DialogBehavior::m_openDialogCallback;

DialogBehavior::DialogBehavior()
{
	m_client=nullptr;
	m_clientTeam=nullptr;
}

DialogBehavior::~DialogBehavior()
{

}

bool DialogBehavior::Init(std::function<void()> * menuExitCallback)
{
	m_menuExitCallback = menuExitCallback;

	return true;
}

void DialogBehavior::ActionEvent(int eventID)
{
	//virtual
}

void DialogBehavior::ActionDialog(int dialogID)
{
	//virtual
}

void DialogBehavior::ExitDialog(int exitDialog)
{
	//virtual
}

void DialogBehavior::DropDialogControl()
{
	m_client = nullptr;
	m_clientTeam = nullptr;
}

bool DialogBehavior::AuthDialog(PlayerCharacterController * client, vector<PlayerCharacterController*>* clientTeam)
{
	switch (m_permissionScheme)
	{
	case dialogPermissionSinglePlayer:
	{
		if (m_client == nullptr || m_client == client)
		{
			m_client = client;
			m_clientTeam = clientTeam;

			return true;
		}

	
	}
	break;



	}


	return false;
}

string & DialogBehavior::GetDir()
{
	return m_dialogDirectory;
}

vector < DialogScreenData > * DialogBehavior::GetDialogScreens()
{
	return &m_dialogScreens;
}

DialogScreenData * DialogBehavior::GetEntryOptions(int index)//By NPC STATE
{
	return &m_dialogScreens.at(m_dialogEntryPoints.at(index));
}

int DialogBehavior::GetEntryOptionIndex(int npcControllerState)
{
	return m_dialogEntryPoints.at(npcControllerState);
}

DialogScreenData * DialogBehavior::GetOptionsByScreenIndex(int index)
{
	return &m_dialogScreens.at(index);
}

PlayerCharacterController * DialogBehavior::GetClient()
{
	return m_client;
}

vector<PlayerCharacterController*>* DialogBehavior::GetClientTeam()
{
	return m_clientTeam;
}
