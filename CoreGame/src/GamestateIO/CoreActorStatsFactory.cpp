#include "CoreActorStatsFactory.h"

CoreActorStatsFactory::CoreActorStatsFactory()
	: ActorStatsFactory()
{
	//todo think of better init flow.

	m_settingsPaths.resize(characterNameCount);
	m_settingsPaths[characterAngryCat] = "Resources/Characters/AngryCat.stats";
	m_settingsPaths[characterVisionOwl] = "Resources/Characters/VisionOwl.stats";
	m_settingsPaths[characterNenian] = "Resources/Characters/Nenian.stats";
	m_settingsPaths[characterSurku] = "Resources/Characters/Surku.stats";
	m_settingsPaths[characterGrey] = "Resources/Characters/Grey.stats";
	m_settingsPaths[characterLoost] = "Resources/Characters/Grey.stats";
	m_settingsPaths[characterTypy] = "Resources/Characters/Grey.stats";
	m_settingsPaths[characterShork] = "Resources/Characters/Shork.stats";
	m_settingsPaths[characterCaalu] = "Resources/Characters/Caalu.stats";
}

CoreActorStatsFactory::~CoreActorStatsFactory()
{
}

bool CoreActorStatsFactory::ConstructActorStats(ActorStats ** actorStatsOut, CharacterClassName characterClass)
{
	if (ActorStatsFactory::ConstructActorStats(actorStatsOut, characterClass))
	{
		//todo more stuff?

		return true;
	}
	return false;
}
