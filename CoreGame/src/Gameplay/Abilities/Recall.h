#if !defined(RECALL_H)
#define RECALL_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "AbilityIncludes.h"

class Recall : public InstantAbility
{
private:
	LMTimer m_recallTimer;
protected:

public:
	Recall(Actor * owner);
	~Recall();
	
	//void Update(float deltaTime);
	//void TargetEliminated();

	void Activate(float currentGameTime);
	void Success();

protected:
	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();

public:
		
	//accessors
	LMTimer * GetRecallTimer();
};

#endif