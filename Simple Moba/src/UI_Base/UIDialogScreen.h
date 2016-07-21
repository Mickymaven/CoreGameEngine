#if !defined(UIDIALOGSCREEN_H)
#define UIDIALOGSCREEN_H

#include <vector>
using std::vector;
#include <functional>
using namespace std::placeholders;

#include "../../../EngineMoba/src/Actor_Control/DialogBehavior.h"
#include "../../../EngineMoba/src/Actor_Control/DialogViewScreenOptions.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

#include "../UI/DialogOptionLabel.h"
#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

#include "../GameplayView/NPCView.h"


enum DialogScreenState
{
	dialogScreenActive,
	dialogScreenInactive,
	dialogScreenStateCount
};


//This class is the base for any UI component that is used in dialog flow
//UIBasicDialogScreen, GameShopMenu

class UIDialogScreen
{
protected:
	static ViewProfile * m_viewProfile;
	static ThemeResources * m_theme;
	static std::function<void(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option)> m_dialogViewChangeCallback;

	DialogScreenState m_state;
	InputModel * m_inputModel; //with multiple dialog screens, how would we know which input models are active.
	// this will probably be resolved by putting input into DialogScreenController.

	NPCView * m_dialogOwner;
	DialogBehavior * m_dialogBehavior;
	int m_dialogScreenNumber;

	UILabel m_dialogText;

	vector<DialogOptionLabel> m_options;



	RECT m_r;

public:
	UIDialogScreen();
	~UIDialogScreen();

	bool Init(ViewProfile * viewProfile,
		ThemeResources * theme);


	virtual void Update(float deltaTime);
	virtual void Render();

	void OnEnterActive();
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float deltaTime);
	void OnExitInactive();

	void ExitCurrentState();

	DialogScreenState GetDialogScreenState();

	void ActionForOption(DialogOption * dialogOption);

	void Reactivate();
	void SetAsActive();
	void SetDialogModel(NPCView * npcView);
	void virtual Activate(NPCView * npcView);
	void ActionNextDialog(int index);

	void SetOptions(int index);
	void SetOptions(DialogScreenData * data);

	void ActionEvent(NPCView * npcView, int index);

	void ActionNextDialogWithClass(NPCView * npcView, int index, DialogScreenViewOptions classEnum);

	static void SetDialogViewChangeCallback(std::function<void(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option)> f);
};


#endif