#include "StatChangeObject.h"

StatChangeObject::StatChangeObject()
{
	Zero();
}

StatChangeObject::~StatChangeObject()
{

}

void StatChangeObject::Update(float deltaTime)
{
	Zero();
}

void StatChangeObject::Zero()
{
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

StatChangeObject& StatChangeObject::operator += (const StatChangeObject& stats)
{
	m_health += stats.m_health;
	m_maxHealth += stats.m_maxHealth;
	m_healthRegen += stats.m_healthRegen;
	m_physicalDamage += stats.m_physicalDamage;
	m_catVoodoo += stats.m_catVoodoo;
	m_attackSpeed += stats.m_attackSpeed;
	m_moveSpeed += stats.m_moveSpeed;
	m_armor += stats.m_armor;
	m_catVoodooResist += stats.m_catVoodooResist;
	m_range += stats.m_range;

	return *this;
}

void StatChangeObject::AddHealth(float health)
{
	m_health += health;
}

void StatChangeObject::AddMaxHealth(float maxHealth)
{
	m_maxHealth += maxHealth;
}

void StatChangeObject::AddHealthRegen(float healthRegen)
{
	m_healthRegen += healthRegen;
}

void StatChangeObject::AddPhysicalDamage(float physicalDamage)
{
	m_physicalDamage += physicalDamage;
}

void StatChangeObject::AddCatVoodoo(float catVoodoo)
{
	m_catVoodoo += catVoodoo;
}

void StatChangeObject::AddAttackSpeed(float attackSpeed)
{
	m_attackSpeed += attackSpeed;
}

void StatChangeObject::AddMoveSpeed(float moveSpeed)
{
	m_moveSpeed += moveSpeed;
}

void StatChangeObject::AddArmor(float armor)
{
	m_armor += armor;
}

void StatChangeObject::AddCatVoodooResist(float catVoodooResist)
{
	m_catVoodooResist += catVoodooResist;
}

void StatChangeObject::AddRange(float range)
{
	m_range += range;
}