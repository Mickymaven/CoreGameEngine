#if !defined (ABILITY_H)
#define ABILITY_H

#include<string>
#include <vector>
using namespace std;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "../../../EngineGameModel/src/Base/PhysicsObject.h"
#include "../Actors/StatChangeObject.h"

#include "../VitalEffect/Buff.h"
#include "../VitalEffect/Damage.h"
#include "../VitalEffect/Healing.h"

#include "../Actors/VitalEntity.h"
#include "../Actors/Actor.h"

#include "../../../EngineGameModel/src/Utility/LMTimer.h"

//for derived classes
#include "../../../EngineGameModel/src/Base/Sprite.h"




enum AbilityState
{
	abilityInactive,
	abilityActive,
	abilityStateCount
};

enum AbilityCastType
{
	abilityCastTypeDirectionalCast,
	abilityCastTypeInstantCast,
	abilityCastTypePointCast,
	abilityCastTypeSingleTargetCast
};

enum AbilityResult
{
	abilityResultOK,
	abilityResultOnCooldown,
	abilityResultRequiredTargetMissing,
	abilityResultIntargetable,
	abilityResultStillActive,
	abilityResultOutOfRange,
	abilityResultMaximumCountReached,
	abilityResultCount
};

enum NeutralCategoryState
{
	neutralCategoryNone,
	neutralCategoryAll,
	neutralCategoryCount

};

enum AbilityTargetGroup
{
	//abilityTargetTeamMember,
	//abilityTargetOpponentMember,
	abilityTargetTeam,
	abilityTargetOpponents,
	abilityTargetGroupCount
};


class Ability
{
protected:
	Actor * m_owner;

	vector<Actor *> * m_playerTeam;
	vector<Actor *> * m_opponentTeam;
	vector<Actor *> * m_neutralTeam;

	string m_name;
	AbilityState m_state;
	AbilityCastType m_castType;
	AbilityTargetGroup m_targetGroup;
	DamageType m_damageType;
	HealthEffectApplicationType m_appType;

	float m_range;

	float m_defaultCooldown;
	float m_castTime;//value of currentGameTime OnActivate
	float m_timeActive;//value of currentGameTime + deltaTime
	float m_maximumLife;
	float m_cooldownExpires; // Game time in seconds at which cooldown for ability is up

	float m_tempTime;

	Buff * m_tempBuff; //temp buff pointer, stores buff from Targets BuffReciepent::CreateBuff(). must call BuffReciepent::pushbuff for eg.

	vector<Damage *> m_damageOnUpdate;
	vector<Healing *> m_healingOnUpdate;

	float m_ownerPhysicalDamageOnCast;
	float m_ownerCatVoodooOnCast;
	
	float m_physicalDamageApplied;
	float m_catVoodooApplied;

public:
	Ability();
	Ability(Actor * owner);
	~Ability();

	void virtual Update(float deltaTime);

	void UpdateLifeTimer(float deltaTime);
	bool InactiveConditions(float deltaTime, bool isTimeUp);//might leave and not make virtual as a default behavior

	void virtual TargetEliminated();

	void virtual OnEnterActive(float currentGameTime)=0;
	void virtual Active(float deltaTime) = 0;
	void virtual OnExitActive() = 0;

	void virtual OnEnterInactive() = 0;
	void virtual Inactive(float deltaTime) = 0;
	void virtual OnExitInactive() = 0;

	void ExitCurrentState();

	AbilityResult virtual CanActivate(
		float gameTime,
		LMVector3 * m_indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		Actor * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam) =0;

	AbilityResult virtual Activate(
		float gameTime,
		LMVector3 * m_indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		Actor * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam)=0;

	bool IsTargetableOpponentOrTeam(Actor * target);

	bool OffCooldown(float currentGameTime);
	void ApplyCooldown(float gameTime);
	float GetCooldownRemaining(float currentGameTime);

	Actor * ClosestTargetInRange(LMVector3 * position, float radius, NeutralCategoryState checkneutral);

	void GetActorsInRange(vector<Actor*> * actorsInRange, vector<Actor*> * actorsIn, LMVector3 * position, float radius);
	
	void CreateBuff(Actor * target, BuffType buffType, int buffName, float duration);

	void AddDamage(float damageValue, DamageType damageType, VitalEntity * owner, VitalEntity * target, float duration, float timer, HealthEffectApplicationType appType);
	void AddHealing(float healValue, VitalEntity * owner, VitalEntity * target, float duration, float timer, HealthEffectApplicationType appType);


	//accessors

	AbilityState GetState();
	AbilityCastType GetCastType();
	AbilityTargetGroup GetTargetGroup();
	HealthEffectApplicationType GetHealthEffectApplicationType();
	float GetRange();
	string * GetName();
	float GetCooldown();

	vector<Damage *> * GetDamageOnUpdate();
	vector<Healing *> * GetHealingOnUpdate();

	//mutators
	void SetDamageApplied(float damage, DamageType damageType);
	void SetOwner(Actor * owner);
	void SetTeams(vector<Actor *> * playerTeam, vector<Actor *> * opponentTeam, vector<Actor *> * neutralTeam);
	void SetDamageValuesOnActivation();

};

#endif
