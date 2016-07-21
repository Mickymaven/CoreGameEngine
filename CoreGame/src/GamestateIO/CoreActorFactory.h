#if !defined(COREACTORFACTORY_H)
#define COREACTORFACTORY_H

#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineMoba/src/GamestateIO/ActorFactory.h"

#include "CoreActorStatsFactory.h"

class CoreActorFactory : public ActorFactory
{
private:
	CoreActorStatsFactory * m_coreActorStatsFactory;

public:
	CoreActorFactory();
	~CoreActorFactory();

	bool Init(CoreActorStatsFactory * coreActorStatsFactory);

	bool ConstructCoreActor(Actor ** actorOut, CharacterClassName characterClass, string * uniqueName, TeamName team);

};

#endif