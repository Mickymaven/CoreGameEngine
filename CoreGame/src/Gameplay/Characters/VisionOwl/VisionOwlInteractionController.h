#if !defined(VISIONOWLINTERACTIONCONTROLLER_H)
#define VISIONOWLINTERACTIONCONTROLLER_H

#include <functional>
using namespace std::placeholders;

#include "../../../../../EngineMoba/src/Actor_Control/InteractionController.h"
#include "../../../../../EngineMoba/src/Actor_Control/AggressionState.h"


#include "../../../../../EngineMoba/src/Actor_Control/DialogStandbyBehavior.h"
#include "VisionOwlDialogBehavior.h"

enum VisionOwlEvents
{
	visionOwlEventCombat,
	visionOwlEventQuest,

};

class VisionOwlInteractionController : public InteractionController
{
protected:
	DialogStandbyBehavior * m_dialogStandbyBehavior;
	VisionOwlDialogBehavior * m_visionOwlDialogBehavior;
	AggressionState * m_aggressionState;

	TradeInventory * m_actorInv;
	PathController * m_pathController;


public:
	VisionOwlInteractionController();
	~VisionOwlInteractionController();

	virtual bool Init(
		Character * character,
		AggressionState * aggressionState,
		VisionOwlDialogBehavior * visionOwlDialogBehavior,
		DialogStandbyBehavior * dialogStandbyBehavior);

	virtual void Update(float deltaTime) = 0;

	virtual DialogScreenData * ActionRequestDialogScreen()=0;
	//virtual int ActionRequestDialogEntryPoint()=0;
	virtual void ActionOnRespawn(float x, float y, float z) = 0;

	virtual void ExitInitialDialog() = 0;
	virtual void ActionEvent(int index) = 0;

	virtual void CallbackConfirmTrade() = 0;

	virtual DialogBehavior * GetDialogBehavior() { return NULL; };
	virtual void OnHit(VitalEntity * owner) {};


	
};

#endif