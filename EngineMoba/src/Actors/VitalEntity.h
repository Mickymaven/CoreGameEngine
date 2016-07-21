#if !defined(VITALENTITY_H)
#define VITALENTITY_H

#include <functional>
#include <vector>
using namespace std;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"

#include "StatChangeObject.h"
#include "ActorStats.h"

enum VitalEntityState
{
	vitalEntityStateActive,
	vitalEntityStateIntargetable,
	vitalEntityStateInactive,
	vitalEntityStateCount
};

enum VitalEntityType
{
	vitalEntityTypeVitalEntity,
	vitalEntityTypeActor,
	vitalEntityTypeNPC,
	vitalEntityTypeCount
};

class VitalEntity : public Sprite
{
private:
protected:
	//todo implement visiblity based on notes
	//bool m_visible;
	//bool m_makeInvisibleNextUpdate; //notes at bottom
	//bool m_makeVisibleNextUpdate; //notes at bottom

	VitalEntityType m_vitalEntityType;
	VitalEntityState m_vitalEntityState;
	string m_className;
	StatChangeObject m_statChangeObject;
	ActorStats m_stats;

	void * m_controller;
	string m_uniqueName;

	std::function<void(VitalEntity * owner)> m_onHitCallback;


public:
	VitalEntity();
	VitalEntity(ActorStats * stats, LMVector3 position, LMVector3 rotation, LMVector3 scale, LMVector3 velocity, LMVector3 spin, LMVector3 resize, float acceleration);
	virtual ~VitalEntity();

	//Vital Entity State

	void OnEnterVitalEntityStateActive();
	void VitalEntityStateActiveBehaviour(float deltaTime);
	void OnExitVitalEntityStateActive();

	void OnEnterVitalEntityStateIntargetable();
	void VitalEntityStateIntargetableBehaviour(float deltaTime);
	void OnExitVitalEntityStateIntargetable();

	void OnEnterVitalEntityStateInactive();
	void VitalEntityStateInactiveBehaviour(float deltaTime);
	void OnExitVitalEntityStateInactive();

	void OnEnterForState(VitalEntityState state);
	void OnExitForState(VitalEntityState state);
	void ExitCurrentState();

	void SetToState(VitalEntityState newState);

	void SetInactive();
	void SetIntargetable();
	void SetActive();

	void OnHit(VitalEntity * owner);

	//Accessors
	void * GetVoidToController();
	VitalEntityType GetVitalEntityType();
	VitalEntityState GetVitalEntityState();
	string * GetVitalEntityClassName();
	StatChangeObject * GetStatChangeObject();
	ActorStats * GetStats();
	string GetUniqueName();
	
	//Mutators
	void SetOnHitCallback(std::function<void(VitalEntity * owner)> f);
	void SetVoidToController(void * controller);
	void SetVitalEntityType(VitalEntityType type);
	void SetName(string name);
	void SetStatChangeObject(StatChangeObject statChangeObject);
	void SetActorStats(ActorStats stats);
	void SetUniqueName(string uniqueName);


};

#endif

/*
//PlayerInput
if (visible) allow targetsFromInput.


visible = false;

// check players for fog of war / hide zone visibility
when exposed to enemy, vis = true


//Ability calc phase
m_makeInvisible = false;
m_makeVisable = false;

for ()
if (abilityGivesInvis) m_makeInvisible = true;
if (abilityTakesEnemyInvis) m_makeVisible = true;

//Apply Buff Phase


//make invisible "ObjectPhase"
if (makeInvis) vis = false;
//counters to invis "ObjectPhase"
if (makeVis) vis = true;

//Calc Damage Phase


//Render
if (vis) render;


*/


//visible left click, be hit by skill shot stuff
//not visible cat left click, be hit by skill shot stuff, no new autoaims but existing ones still finds you
//targetable: if (visible) can click, can skill shot
//not targetable: cannot click, cannot skill shot, no new autoaims.