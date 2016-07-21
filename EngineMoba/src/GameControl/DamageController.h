#if !defined (DAMAGECONTROLLER_H)
#define DAMAGECONTROLLER_H

#include <functional>
using namespace std::placeholders;

#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../CoreGame/src/Gameplay/DamageEvent.h"
#include "../Actors/VitalEntity.h"
#include "../Actors/Actor.h"
#include "../Actors/PlayerCharacterController.h"
#include "../Ability/Ability.h"
#include "../VitalEffect/Damage.h"
#include "../VitalEffect/Buff.h"

#include "DeathEvent.h"


#include "VitalObjectController.h"


class DamageController : public VitalObjectController
{
private:

	//StandardMatch5v5State * gameState;
	//MobaViewState * gameView;

	function<void(DamageEvent param)> m_damageEventCallback;//might be a vector later in case more then one place needs this event

	float m_playerDeathDuration;
	float m_npcDeathDuration;

	//temp stuff for each update
	char m_buffer[2000];
	float m_gameModeDamageMultiplier;

	//VitalEntity * m_targetToDamage;
	Ability * m_abilitySource;
	float m_appliedDamage;
	float m_targetHealth;

	float m_reductionValue;
	float m_totalDamageValue;
	float m_damagePortionValue;
	float m_reductionPortion;

	DamageOriginType m_finalBlowType;
	VitalEntity * m_finalBlowOrigin;
	DeathEvent * m_deathEvent;

	PlayerKDA m_ownerKDA;
	PlayerKDA m_targetKDA;

	bool m_deleteatindex;

	Damage ** m_damageVectorElement;

	bool m_isDeathThisUpdate;
	vector<DeathEvent *> m_deathFlags;
	char bufferb[1000];

public:
	DamageController::DamageController();
	~DamageController();

	void Init(MobaState * gameStateIn);

	// DAMAGE SYSTEM FUNCTIONS
	void Update(float deltaTime);

	void DamageVitalEntity(float deltaTime, Damage * damage);
	void DamageNPC(float deltaTime, Damage * damage);
	
	void DamageActor(float deltaTime, Damage * damage);

	//void StoreTargetHere(float deltaTime, Damage * damage);
	bool RemoveDamageForInactiveTargets(float deltaTime, Damage * damage);
	void CalcDamageAndUpdateAbility(float deltaTime, Damage * damage);

	void ApplyDamageChanges(float deltaTime, Damage * damage);

	void CommonOnDeath(Damage * damage);
	void CommonActorDeath(Damage * damage);
	void RemoveBuffsFromActor(Actor * actor);
	void StoreDamage(Damage * damage);
	void RecheckAllDamageToRemove(float deltaTime);
	void CalculateAssists(float deltaTime);
	
	//HELP STUFF
	void DamageController::GameMessageForPlayerCharacterDeathEvent(DeathEvent * deathEvent);
	void SetDamageEventCallback(function<void(DamageEvent e)> f);
};

#endif