#include "ActorFactory.h"

ActorFactory::ActorFactory()
{
}

ActorFactory::~ActorFactory()
{
}

bool ActorFactory::Init(ActorStatsFactory * actorStatsFactory)
{
	m_actorStatsFactory = actorStatsFactory;

	return true;
}

bool ActorFactory::ConstructActor(Actor ** actorOut, int characterClass, string * uniqueName, TeamName team)
{
	m_actorStatsFactory->ConstructActorStats(&m_createdActorStats, (CharacterClassName)characterClass);
	
	m_createdActor = new Actor(
		m_createdActorStats,
		LMVector3(0.0f, 0.0f, 0.0f),//Position
		LMVector3(0.0f, 0.0f, 0.0f),//Rotation
		LMVector3(1.0f, 1.0f, 1.0f),//Scale
		LMVector3(0.0f, 0.0f, 0.0f),//Velocity
		LMVector3(0.0f, 0.0f, 0.0f),//Spin
		LMVector3(0.0f, 0.0f, 0.0f),//Resize
		0.0f);

	m_createdActor->SetUniqueName(*uniqueName);
	m_createdActor->SetTeam(team);

	*actorOut = m_createdActor;

	return true;
}
