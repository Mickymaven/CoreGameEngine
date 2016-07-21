#if !defined(DAMAGEEVENT_H)
#define DAMAGEEVENT_H

#include "../../../EngineMoba/src/Actors/VitalEntity.h"

enum DamageEvents
{
	damageEventObjectDestroyed,
	damageEventTeamLootChestDestroyed,
	damageEventImportantNPC,
	damageEventPlayerDied,
	damageEventCount
};

struct DamageEvent
{
	//int eventId;  ?
	DamageEvents m_eventTypeId;
	VitalEntity * m_owner;
	VitalEntity * m_target;
	DeathEvent * m_deathEvent = nullptr;
};

#endif