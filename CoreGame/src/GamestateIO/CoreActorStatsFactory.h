#if !defined(COREACTORSTATSFACTORY_H)
#define COREACTORSTATSFACTORY_H

#include "../../../EngineMoba/src/GamestateIO/ActorStatsFactory.h"

class CoreActorStatsFactory : public ActorStatsFactory
{
protected:


public:
	CoreActorStatsFactory();
	~CoreActorStatsFactory();

	bool ConstructActorStats(ActorStats ** actorStatsOut, CharacterClassName characterClass);


};


#endif