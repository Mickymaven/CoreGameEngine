#if !defined(DIALOGSTANDBYBEHAVIOR_H)
#define DIALOGSTANDBYBEHAVIOR_H

#include "Interaction.h"
#include "WalkState.h"
#include "../../../EngineMoba/src/Actors/Actor.h"
enum DialogStandbyState
{
	dialogStandbyInitial,
	dialogStandbyStateCount
};

class DialogStandbyBehavior : public Interaction
{
	DialogStandbyState m_state;

public:
	DialogStandbyBehavior();
	bool Init(WalkState * walkState, Actor * owner);
	~DialogStandbyBehavior();

	void Update(float deltaTime);

	void OnEnterInitial();
	void Initial(float deltaTime);
	void OnExitInitial();

	void ExitCurrentState();

	DialogStandbyState GetState();

	void OnHit(VitalEntity * owner);
};

#endif