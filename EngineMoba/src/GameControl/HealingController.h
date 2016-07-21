#if !defined(HEALINGCONTROLLER_H)
#define HEALINGCONTROLLER_H

#include "VitalObjectController.h"

class HealingController : public VitalObjectController
{
private:
	Healing ** m_healingVectorElement;

	float m_gameModeHealingMultiplier;

	//Per object proccessing Variables
	float m_targetHealth;
	Ability * m_abilitySource;
	float m_healthPortionValue;
	float m_appliedHealing;

public:
	HealingController();
	~HealingController();

	void Init(MobaState * gameStateIn);

	void Update(float deltaTime);
	
	void HealVitalEntity(float deltaTime, Healing * healing);
	void HealNPC(float deltaTime, Healing * healing);
	void HealActor(float deltaTime, Healing * healing);
	
	bool RemoveHealingForInactiveTargets(float deltaTime, Healing * healing);
	void CalcHealingAndUpdateAbility(float deltaTime, Healing * healing);

	void ApplyHealingChanges(float deltaTime, Healing * healing);
	
	void StoreHealing(Healing * healing);
};

#endif