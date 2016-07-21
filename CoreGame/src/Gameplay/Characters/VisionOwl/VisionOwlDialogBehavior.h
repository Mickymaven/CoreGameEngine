#if !defined(VISIONOWLDIALOGBEHAVIOR_H)
#define VISIONOWLDIALOGBEHAVIOR_H



#include "../../../../../EngineMoba/src/Actor_Control/DialogBehavior.h"
#include "../../../../../EngineMoba/src/Actor_Control/DialogViewScreenOptions.h"

enum VisionOwlDialogEvent
{
	visionOwlDialogEventCancelQuest,
	visionOwlDialogEventStartQuest,
	visionOwlDialogEventQuestEndTransition,
	visionOwlDialogEventStartCombat,
	visionOwlDialogEventDespawn,
	//visionOwlDialogEventOpenTrade,
	visionOwlDialogEventCount
};

enum VisionOwlDialogScreen
{
	visionOwlDialogScreenRootGreeting,
	visionOwlDialogScreenRoot,
	visionOwlDialogScreenPreCombat,
	visionOwlDialogScreenPreQuest,
	visionOwlDialogScreenQuestReturnIncomplete,
	visionOwlDialogScreenQuestReturnWin,
	visionOwlDialogScreenOfferTrade,
	visionOwlDialogScreenTakeTheItem,
	visionOwlDialogScreenItemTaken,
	visionOwlDialogScreenCount
};

class VisionOwlDialogBehavior : public DialogBehavior
{


public:
	VisionOwlDialogBehavior();
	~VisionOwlDialogBehavior();

	bool Init(std::function<void()> * menuExitCallback, std::function<void()> * questCallBack, std::function<void()> * combatCallback);

	void virtual ActionEvent(int eventID);
	void virtual ActionDialog(int dialogID);
	void virtual ExitDialog(int exitDialog);

};

#endif