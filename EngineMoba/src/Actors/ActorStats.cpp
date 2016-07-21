#include "ActorStats.h"
#include <Windows.h>
ActorStats::ActorStats()
{
	string m_name = "";
	string m_caption = "";

	m_baseLevel = 0;
	m_maxLevel = 0;
	m_baseHealth = 0.0f;
	m_healthPerLevel = 0.0f;
	m_baseHealthRegen = 0.0f;
	m_healthRegenPerLevel = 0.0f;
	m_baseCatVoodoo = 0.0f;
	m_catVoodooPerLevel = 0.0f;
	m_basePhysicalDamage = 0.0f;
	m_physicalDamagePerLevel = 0.0f;
	m_baseAttackSpeed = 0.0f;
	m_attackSpeedPerLevel = 0.0f;
	m_baseMoveSpeed = 0.0f;
	m_moveSpeedPerLevel = 0.0f;
	m_baseArmor = 0.0f;
	m_armorPerLevel = 0.0f;
	m_baseCatVoodooResist = 0.0f;
	m_catVoodooResistPerLevel = 0.0f;
	m_baseRange = 0.0f;
	m_rangePerLevel = 0.0f;


	m_level = 0;
	m_health = 0.0f;
	m_maxHealth = 0.0f;
	m_healthRegen = 0.0f;
	m_physicalDamage = 0.0f;
	m_catVoodoo = 0.0f;
	m_attackSpeed = 0.0f;
	m_moveSpeed = 0.0f;
	m_armor = 0.0f;
	m_catVoodooResist = 0.0f;
	m_range = 0.0f;
}

ActorStats::ActorStats(
	string name,
	string caption,
	float baseHealth,
	float baseHealthRegen,
	float baseCatVoodoo,
	float basePhysicalDamage,
	float baseAttackSpeed,
	float baseMoveSpeed,
	float baseArmor,
	float baseCatVoodooResist,
	float baseRange)
{
	m_name = name;
	m_caption = caption;
	m_baseLevel = 0;
	m_maxLevel = 0;
	m_baseHealth = baseHealth;
	m_healthPerLevel = 0;
	m_baseHealthRegen = baseHealthRegen;
	m_healthRegenPerLevel = 0;
	m_baseCatVoodoo = baseCatVoodoo;
	m_catVoodooPerLevel = 0;
	m_basePhysicalDamage = basePhysicalDamage;
	m_physicalDamagePerLevel = 0;
	m_baseAttackSpeed = baseAttackSpeed;
	m_attackSpeedPerLevel = 0;
	m_baseMoveSpeed = baseMoveSpeed;
	m_moveSpeedPerLevel = 0;
	m_baseArmor = baseArmor;
	m_armorPerLevel = 0;
	m_baseCatVoodooResist = baseCatVoodooResist;
	m_catVoodooResistPerLevel = 0;
	m_baseRange = baseRange;
	m_rangePerLevel = 0;
}


ActorStats::~ActorStats()
{

}

void ActorStats::CalcStatsFromBase()
{
	m_maxHealth = m_baseHealth + (m_level * m_healthPerLevel);
	m_healthRegen = m_baseHealthRegen + (m_level * m_healthRegenPerLevel);
	m_physicalDamage = m_basePhysicalDamage + (m_level * m_physicalDamagePerLevel);
	m_catVoodoo = m_baseCatVoodoo + (m_level * m_catVoodooPerLevel);
	m_attackSpeed = m_baseAttackSpeed + (m_level * m_attackSpeedPerLevel);
	m_moveSpeed = m_baseMoveSpeed + (m_level * m_moveSpeedPerLevel);
	m_armor = m_baseArmor + (m_level * m_armorPerLevel);
	m_catVoodooResist = m_baseCatVoodooResist + (m_level * m_catVoodooResistPerLevel);
	m_range = m_baseRange + (m_level * m_rangePerLevel);
}

void ActorStats::LevelUp()
{
	if (m_level < 20)
	{
		float pc = m_health / m_maxHealth;
		m_level++;
		CalcStatsFromBase();
		m_health = pc * m_maxHealth;
	}
}


void ActorStats::RegenHealth(float deltaTime)
{
	if (m_health > 0.0f)
	{
		if (m_health < m_maxHealth)
		{
			m_health += m_healthRegen *  deltaTime;
			if (m_health > m_maxHealth) m_health = m_maxHealth;
		}
	}
}

void ActorStats::AddHealth(float health)
{
	//char buffer2[500];
	//sprintf_s(buffer2, "%f \n", health);
	//OutputDebugString(buffer2);

	if (health + m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	else
	{
		m_health += health;

		if (m_health < 0)
		{
			MessageBox(NULL, "Health is below zero in Add Health and No death is being Applied.", "Error", MB_OK);
		}
	}
}
