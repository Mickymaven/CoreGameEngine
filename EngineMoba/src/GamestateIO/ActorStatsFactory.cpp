#include "ActorStatsFactory.h"

ActorStatsFactory::ActorStatsFactory()
{
	m_createdActorStats = nullptr;
}

ActorStatsFactory::~ActorStatsFactory()
{

}

bool ActorStatsFactory::ConstructActorStats(ActorStats ** actorStatsOut, int characterClass)
{
	//todo how fast is file IO here?
	m_createdActorStats = new ActorStats();

	string settingspath;
	string line;

	if (characterClass >= 0 && characterClass < m_settingsPaths.size())
	{
		settingspath = m_settingsPaths[characterClass];
	}
	else return false;

	ifstream statsFile(settingspath);

	m_createdActorStats->SetBaseLevel(1);
	m_createdActorStats->SetMaxLevel(20);

	if (statsFile.is_open())
	{

		int lineCount = 0;
		while (std::getline(statsFile, line))
		{
			lineCount++;
			switch (lineCount)
			{
			case 2://Name
				m_createdActorStats->SetName(line);
				break;
			case 4://Title
				m_createdActorStats->SetCaption(line);
				break;
			case 6://Base Health
				m_createdActorStats->SetBaseHealth(stof(line));
				break;
			case 8://health per level
				m_createdActorStats->SetHealthPerLevel(stof(line));
				break;
			case 10://Base Health Regen (persecond)
				m_createdActorStats->SetBaseHealthRegen(stof(line));
				break;
			case 12://BaseHealthRegen Per Level
				m_createdActorStats->SetHealthRegenPerLevel(stof(line));
				break;
			case 14://Base Ability Power
				m_createdActorStats->SetBaseCatVoodoo(stof(line));
				break;
			case 16://Ability Power Per Level
				m_createdActorStats->SetCatVoodooPerLevel(stof(line));
				break;
			case 18://Base Physical Damage
				m_createdActorStats->SetBasePhysicalDamage(stof(line));
				break;
			case 20://Physical Damage Per Level
				m_createdActorStats->SetPhysicalDamagePerLevel(stof(line));
				break;
			case 22://Base Attack Speed (attacks per second)
				m_createdActorStats->SetBaseAttackSpeed(stof(line));
				break;
			case 24://Attack Speed Per Level  (attacks per second)
				m_createdActorStats->SetAttackSpeedPerLevel(stof(line));
				break;
			case 26://Base Move Speed
				m_createdActorStats->SetBaseMoveSpeed(stof(line));
				break;
			case 28:///Move Speed per level
				m_createdActorStats->SetMoveSpeedPerLevel(stof(line));
				break;
			case 30://Base Armor
				m_createdActorStats->SetBaseArmor(stof(line));
				break;
			case 32://Armor Per Level
				m_createdActorStats->SetArmorPerLevel(stof(line));
				break;
			case 34://Base CatVoodoo Resist
				m_createdActorStats->SetBaseCatVoodooResist(stof(line));
				break;
			case 36://CatVoodoo Resist Per Level
				m_createdActorStats->SetCatVoodooResistPerLevel(stof(line));
				break;
			case 38:
				m_createdActorStats->SetBaseRange(stof(line));
				break;
			case 40:
				m_createdActorStats->SetRangePerLevel(stof(line));

				break;
			default:
				break;
			}
		}
	}

	*actorStatsOut = m_createdActorStats;

	return true;
}
