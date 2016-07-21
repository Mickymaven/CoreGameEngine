#include "CoreActorFactory.h"

CoreActorFactory::CoreActorFactory()
{
	m_coreActorStatsFactory = nullptr;
	m_createdActor = nullptr;
}

CoreActorFactory::~CoreActorFactory()
{
}

bool CoreActorFactory::Init(CoreActorStatsFactory * coreActorStatsFactory)
{
	m_coreActorStatsFactory = coreActorStatsFactory;
	m_actorStatsFactory = coreActorStatsFactory;
	return true;
}

bool CoreActorFactory::ConstructCoreActor(Actor ** actorOut, CharacterClassName characterClass, string * uniqueName, TeamName team)
{
	//Actor * m_createdActor;
	//ActorStats * m_createdActorStats;
	if (m_coreActorStatsFactory->ConstructActorStats(&m_createdActorStats, characterClass))
	{
		if (ActorFactory::ConstructActor(actorOut, characterClass, uniqueName, team))
		{
			return true;
			//*actorOut = m_createdActor;
		}
	}

	return false;
}
