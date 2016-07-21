#if !defined(ACTORFACTORY_H)
#define ACTORFACTORY_H

#include "ActorStatsFactory.h"

#include "../Actors/Actor.h"

class ActorFactory
{
protected:
	ActorStatsFactory * m_actorStatsFactory;

	Actor * m_createdActor;
	ActorStats * m_createdActorStats;

public:
	ActorFactory();
	~ActorFactory();

	bool Init(ActorStatsFactory * actorStatsFactory);

	bool ConstructActor(Actor ** actorOut, int characterClass, string * uniqueName, TeamName team);
};

#endif