#if !defined(ANGRYCATINTERACTIONCONTROLLER_H)
#define ANGRYCATINTERACTIONCONTROLLER_H

#include "../../../../../EngineMoba/src/Actor_Control/InteractionController.h"
#include "../../../../../EngineMoba/src/Actor_Control/AggressionState.h"


class AngryCatInteractionController : public InteractionController
{
private:
	AggressionState * m_aggressionState;

public:
	AngryCatInteractionController();
	AngryCatInteractionController(Actor * actor, AggressionState * aggressionState);
	~AngryCatInteractionController();

	void Update(float deltaTime);
	
	void OnEnterAgressive();
	void Aggressive(float deltaTime);
	void OnExitAgressive();


	void OnHit(VitalEntity * owner);


	DialogScreenData * ActionRequestDialogScreen();

	int ActionRequestDialogEntryPoint();

	virtual DialogBehavior * GetDialogBehavior();
	virtual void ActionEvent(int index);

};

#endif