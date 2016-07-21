#if !defined(DIALOGBEHAVIOR_H)
#define DIALOGBEHAVIOR_H

#include <vector>
using std::vector;

#include <functional>
using namespace std::placeholders;

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "Interaction.h"
#include "DialogOption.h"

enum DialogPermissionScheme
{
	dialogPermissionOpen,
	dialogPermissionSingleTeam,
	dialogPermissionSinglePlayer,
	dialogPermissionSchemeCount

};


struct DialogScreenData
{
	int m_viewScreenClass;
	string m_dialogText;
	vector<DialogOption*> m_options;
	vector<DialogOption*> m_TradeScreenOptions;
};

class DialogBehavior : public Interaction
{
protected:
	DialogPermissionScheme m_permissionScheme;
	PlayerCharacterController * m_client;
	vector<PlayerCharacterController*> * m_clientTeam;
	//PlayerCharacterView * clientView, vector<PlayerCharacterView *> * clientTeamViews

	string m_dialogDirectory;
	//Event
	vector<std::function<void()>*> m_eventCallbacks;

	//Dialog Representation
	vector < DialogScreenData > m_dialogScreens;

	//Exit Menu
	std::function<void()> * m_menuExitCallback;


	vector<int> m_dialogEntryPoints;

public:
	static std::function<void()> m_openDialogCallback;

	DialogBehavior();
	~DialogBehavior();

	bool Init(std::function<void()> * menuExitCallback);

	void virtual ActionEvent(int eventID);
	void virtual ActionDialog(int dialogID);
	void virtual ExitDialog(int exitDialog);

	void DropDialogControl();

	bool AuthDialog(PlayerCharacterController * client, vector<PlayerCharacterController *> * clientTeam);

	string & GetDir();


	vector < DialogScreenData > * GetDialogScreens();

	DialogScreenData * GetEntryOptions(int index);
	int GetEntryOptionIndex(int npcControllerState);
	DialogScreenData * GetOptionsByScreenIndex(int index);

	PlayerCharacterController * GetClient();
	vector<PlayerCharacterController *> * GetClientTeam();

};

#endif