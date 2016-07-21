#include "VisionOwlDialogBehavior.h"

VisionOwlDialogBehavior::VisionOwlDialogBehavior()
{
	m_dialogDirectory = "VisionOwl";
	m_permissionScheme = dialogPermissionSinglePlayer;
}

VisionOwlDialogBehavior::~VisionOwlDialogBehavior()
{

}

bool VisionOwlDialogBehavior::Init(std::function<void()> * menuExitCallback, std::function<void()> * questCallBack, std::function<void()> * combatCallback)
{
	m_eventCallbacks.resize(visionOwlDialogEventCount);
	m_eventCallbacks.at(visionOwlDialogEventStartQuest) = questCallBack;
	m_eventCallbacks.at(visionOwlDialogEventStartCombat) = combatCallback;

	m_dialogScreens.resize(visionOwlDialogScreenCount);

	//0m_dialogScreens.at(visionOwlDialogScreenRootGreeting).m_dialogText = "Dialog Root Greeting.";
	m_dialogScreens.at(visionOwlDialogScreenRootGreeting).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenRootGreeting).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenRoot));
	m_dialogScreens.at(visionOwlDialogScreenRootGreeting).m_options.push_back(new DialogOption(dialogActionExit, 0));

	//1m_dialogScreens.at(visionOwlDialogScreenRoot).m_dialogText = "Dialog Root.";
	m_dialogScreens.at(visionOwlDialogScreenRoot).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenRoot).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenPreQuest));
	m_dialogScreens.at(visionOwlDialogScreenRoot).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenPreCombat));
	m_dialogScreens.at(visionOwlDialogScreenRoot).m_options.push_back(new DialogOption(dialogActionExit, 0));

	//2m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_dialogText = "Offer Combat.";
	m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_options.push_back(new DialogOption(dialogActionExitPlusEvent, visionOwlDialogEventStartCombat));
	m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenRoot));
	m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_options.push_back(new DialogOption(dialogActionExit, 0));

	//3m_dialogScreens.at(visionOwlDialogScreenPreQuest).m_dialogText = "Offer Quest.";
	m_dialogScreens.at(visionOwlDialogScreenPreCombat).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenPreQuest).m_options.push_back(new DialogOption(dialogActionExitPlusEvent, visionOwlDialogEventStartQuest));
	m_dialogScreens.at(visionOwlDialogScreenPreQuest).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenRoot));
	m_dialogScreens.at(visionOwlDialogScreenPreQuest).m_options.push_back(new DialogOption(dialogActionExit, 0));

	//4Quest Incomplete
	m_dialogScreens.at(visionOwlDialogScreenQuestReturnIncomplete).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenQuestReturnIncomplete).m_options.push_back(new DialogOption(dialogActionExit, 0));
	m_dialogScreens.at(visionOwlDialogScreenQuestReturnIncomplete).m_options.push_back(new DialogOption(dialogActionExitPlusEvent, visionOwlDialogEventCancelQuest));

	//5Quest WIN
	m_dialogScreens.at(visionOwlDialogScreenQuestReturnWin).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenQuestReturnWin).m_options.push_back(new DialogOption(dialogActionEvent, visionOwlDialogEventQuestEndTransition));

	//6reward offer (pre inv screen)
	//m_dialogScreens.at(visionOwlDialogScreenOfferTrade).m_dialogText = "Offer Reward.";
	m_dialogScreens.at(visionOwlDialogScreenOfferTrade).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenOfferTrade).m_options.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenTakeTheItem));
	m_dialogScreens.at(visionOwlDialogScreenOfferTrade).m_options.push_back(new DialogOption(dialogActionExit, 0));

	//help you take the reward item..
	//m_dialogScreens.at(visionOwlDialogScreenTakeTheItem).m_options.push_back(new DialogOption(dialogAc
	m_dialogScreens.at(visionOwlDialogScreenTakeTheItem).m_viewScreenClass = dialogScreenViewGameShop;
	m_dialogScreens.at(visionOwlDialogScreenTakeTheItem).m_options.push_back(new DialogOption(dialogActionExit, 0));
	m_dialogScreens.at(visionOwlDialogScreenTakeTheItem).m_TradeScreenOptions.push_back(new DialogOption(dialogActionDialog, visionOwlDialogScreenItemTaken));

	m_dialogScreens.at(visionOwlDialogScreenItemTaken).m_viewScreenClass = dialogScreenViewBasic;
	m_dialogScreens.at(visionOwlDialogScreenItemTaken).m_options.push_back(new DialogOption(dialogActionExitPlusEvent, visionOwlDialogEventDespawn));

	//one for each state
	
	//m_dialogEntryPoints index is intended to represent only states this npc are in
	//aditionally for states you arent logically allowed to enter dialog from, you shouldnt be able to get any dialog entry point
	//we could return an an entry point
	
	m_dialogEntryPoints.push_back(0);//ibDialogStandby,
	m_dialogEntryPoints.push_back(0);//ibInitialDialog,
	m_dialogEntryPoints.push_back(0);//ibAggressive,
	m_dialogEntryPoints.push_back(0);//ibQuest,
	m_dialogEntryPoints.push_back(0);//ibReturnDialog,
	m_dialogEntryPoints.push_back(5);//ibQuestCompleteStandby,
	m_dialogEntryPoints.push_back(6);//ibQuestRewardDialog,
	m_dialogEntryPoints.push_back(0);//ibPostRewardInactive,

	if (!DialogBehavior::Init(menuExitCallback)) return false;

	return true;
}

void VisionOwlDialogBehavior::ActionEvent(int eventID)
{

}

void VisionOwlDialogBehavior::ActionDialog(int dialogID)
{

}

void VisionOwlDialogBehavior::ExitDialog(int exitDialog)
{

}
