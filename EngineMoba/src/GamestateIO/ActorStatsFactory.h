#if !defined(ACTORSTATSFACTORY_H)
#define ACTORSTATSFACTORY_H

#include <vector>
using std::vector;

#include <windows.h>

#include "GameObjectFactory.h"
#include "../../../EngineMoba/src/Actors/ActorStats.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"//(forward dependency)

class ActorStatsFactory: public GameObjectFactory
{
protected:
	ActorStats * m_createdActorStats;
	vector<const char *> m_settingsPaths;

public:
	ActorStatsFactory();
	~ActorStatsFactory();

	bool ConstructActorStats(ActorStats ** actorStatsOut, int characterClass);

};


#endif