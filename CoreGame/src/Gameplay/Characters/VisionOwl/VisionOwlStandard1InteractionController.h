#if !defined(VISIONOWLSTANDARD1INTERACTIONCONTROLLER_H)
#define VISIONOWLSTANDARD1INTERACTIONCONTROLLER_H

#include "../../Quests/OwlQuestStandard1.h"

#include "VisionOwlInteractionController.h"

class VisionOwlStandard1InteractionController : public VisionOwlInteractionController
{
private:
	LMVector3 m_despawnTarget;
	OwlQuestStandard1 * m_questS1;//quest model

public:
	VisionOwlStandard1InteractionController();
	~VisionOwlStandard1InteractionController();

	bool Init(//call NPC vals init or something
			Character * character,
			AggressionState * aggressionState,
			VisionOwlDialogBehavior * visionOwlDialogBehavior,
			DialogStandbyBehavior * dialogStandbyBehavior) override;

	bool InitQuestInformation(OwlQuestStandard1 * questS1);

	void Update(float deltaTime);

	void OnEnterDialogStandby();
	void DialogStandby(float deltaTime);
	void OnExitDialogStandby();

	void OnEnterInitialDialog();
	void InitialDialog(float deltaTime);
	void OnExitInitialDialog();

	void OnEnterAggressive();
	void Aggressive(float deltaTime);
	void OnExitAggressive();

	void OnEnterQuest();
	void Quest(float deltaTime);
	void OnExitQuest();

	void OnEnterReturnDialog();
	void ReturnDialog(float deltaTime);
	void OnExitReturnDialog();

	void OnEnterQuestCompleteStandby();
	void QuestCompleteStandby(float deltaTime);
	void OnExitQuestCompleteStandby();

	void OnEnterQuestRewardDialog();
	void QuestRewardDialog(float deltaTime);
	void OnExitQuestRewardDialog();

	void OnEnterPostRewardInactive();
	void PostRewardInactive(float deltaTime);
	void OnExitPostRewardInactive();

	void ExitCurrentState();

	void OnHit(VitalEntity * owner);
	

	DialogScreenData * ActionRequestDialogScreen() override;

	void ActionOnRespawn(float x, float y, float z) override;

	void ActionTakeToolsOnCancel();

	int CountTools(vector<int> * itemIndicesOut, vector<int> * countOfEachItem);
	void RemoveTools(vector<int> * itemIndices);

	void ExitInitialDialog();
	void ActionEvent(int index);

	void CallbackConfirmTrade();
};
#endif