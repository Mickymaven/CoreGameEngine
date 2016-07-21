#if !defined(ACTORSTATS_H)
#define ACTORSTATS_H

#include <string>
using namespace std;

class ActorStats
{

private:
	

public:
	string m_name;
	string m_caption;
	int m_baseLevel;
	int m_maxLevel;
	float m_baseHealth;
	float m_healthPerLevel;
	float m_baseHealthRegen;
	float m_healthRegenPerLevel;
	float m_baseCatVoodoo;
	float m_catVoodooPerLevel;
	float m_basePhysicalDamage;
	float m_physicalDamagePerLevel;
	float m_baseAttackSpeed;
	float m_attackSpeedPerLevel;
	float m_baseMoveSpeed;
	float m_moveSpeedPerLevel;
	float m_baseArmor;
	float m_armorPerLevel;
	float m_baseCatVoodooResist;
	float m_catVoodooResistPerLevel;
	float m_baseRange;
	float m_rangePerLevel;

	int m_level;
	float m_health;
	float m_maxHealth;
	float m_healthRegen;
	float m_physicalDamage;
	float m_catVoodoo;
	float m_attackSpeed;
	float m_moveSpeed;
	float m_armor;
	float m_catVoodooResist;
	float m_range;

	ActorStats();
	ActorStats(
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
		float baseRange);
	~ActorStats();

	void CalcStatsFromBase();
	void LevelUp();
	void RegenHealth(float deltaTime);
	void AddHealth(float health);
	
	string GetName() { return m_name; }
	string GetCaption() { return m_caption; }
	int GetBaseLevel() { return m_baseLevel; };
	int GetMaxLevel() { return m_maxLevel; };
	float GetBaseHealth() { return m_baseHealth; };
	float GetHealthPerLevel() { return m_healthPerLevel; };
	float GetBaseHealthRegen() { return m_baseHealthRegen; };
	float GetHealthRegenPerLevel() { return m_healthRegenPerLevel; };
	float GetBaseCatVoodoo() { return m_baseCatVoodoo; };
	float GetCatVoodooPerLevel() { return m_catVoodooPerLevel; };
	float GetBasePhysicalDamage() { return m_basePhysicalDamage; };
	float GetPhysicalDamagePerLevel() { return m_physicalDamagePerLevel; };
	float GetBaseAttackSpeed() { return m_baseAttackSpeed; };
	float GetAttackSpeedPerLevel() { return m_attackSpeedPerLevel; };
	float GetBaseMoveSpeed() { return m_baseMoveSpeed; }
	float GetMoveSpeedPerLevel() { return m_moveSpeedPerLevel; }
	float GetBaseArmor() { return m_baseArmor; }
	float GetArmorPerLevel() { return m_armorPerLevel; }
	float GetBaseCatVoodooResist() { return m_baseCatVoodooResist; }
	float GetCatVoodooResistPerLevel() { return m_catVoodooResistPerLevel; }
	float GetBaseRange() { return m_baseRange; }
	float GetRangePerLevel() { return m_rangePerLevel; }

	int GetLevel() { return m_level; }
	float GetHealth() { return m_health; }
	float GetMaxHealth() { return m_maxHealth; }
	float GetHealthRegen() { return m_healthRegen; }
	float GetPhysicalDamage() { return m_physicalDamage; }
	float GetCatVoodoo() { return m_catVoodoo; };
	float GetAttackSpeed() { return m_attackSpeed; }
	float GetMoveSpeed() { return m_moveSpeed; }
	float GetArmor() { return m_armor; }
	float GetCatVoodooResist() { return m_catVoodooResist; }
	float GetRange() { return m_range; }

	//stat mutators

	void SetName(string name) { m_name = name; }
	void SetCaption(string caption) { m_caption = caption; }
	void SetBaseLevel(int baseLevel) { m_baseLevel = baseLevel; }
	void SetMaxLevel(int maxLevel) { m_maxLevel = maxLevel; }
	void SetBaseHealth(float baseHealth) { m_baseHealth = baseHealth; }
	void SetHealthPerLevel(float healthPerLevel) { m_healthPerLevel = healthPerLevel; }
	void SetBaseHealthRegen(float baseHealthRegen) { m_baseHealthRegen = baseHealthRegen; }
	void SetHealthRegenPerLevel(float healthRegenPerLevel) { m_healthRegenPerLevel = healthRegenPerLevel; }
	void SetBaseCatVoodoo(float baseCatVoodoo) { m_baseCatVoodoo = baseCatVoodoo; }
	void SetCatVoodooPerLevel(float catVoodooPerLevel) { m_catVoodooPerLevel = catVoodooPerLevel; }
	void SetBasePhysicalDamage(float basePhysicalDamage) { m_basePhysicalDamage = basePhysicalDamage; }
	void SetPhysicalDamagePerLevel(float physicalDamagePerLevel) { m_physicalDamagePerLevel = physicalDamagePerLevel; }
	void SetBaseAttackSpeed(float baseAttackSpeed) { m_baseAttackSpeed = baseAttackSpeed; }
	void SetAttackSpeedPerLevel(float attackSpeedPerLevel) { m_attackSpeedPerLevel = attackSpeedPerLevel; }
	void SetBaseMoveSpeed(float baseMoveSpeed) { m_baseMoveSpeed = baseMoveSpeed; }
	void SetMoveSpeedPerLevel(float moveSpeedPerLevel) { m_moveSpeedPerLevel = moveSpeedPerLevel; }
	void SetBaseArmor(float baseArmor) { m_baseArmor = baseArmor; }
	void SetArmorPerLevel(float armorPerLevel) { m_armorPerLevel = armorPerLevel; }
	void SetBaseCatVoodooResist(float baseCatVoodooResist) { m_baseCatVoodooResist = baseCatVoodooResist; }
	void SetCatVoodooResistPerLevel(float baseCatVoodooResist) { m_catVoodooResistPerLevel = baseCatVoodooResist; }
	void SetBaseRange(float baseRange) { m_baseRange = baseRange; }
	void SetRangePerLevel(float rangePerLevel) { m_rangePerLevel = rangePerLevel; }

	void SetLevel(int level) { m_level = level; }
	void SetHealth(float health) { m_health = health; }
	void SetMaxHealth(float maxHealth) { m_maxHealth = maxHealth; }
	void SetHealthRegen(float healthRegen) { m_healthRegen = healthRegen;  }
	void SetPhysicalDamage(float physicalDamage) { m_physicalDamage = physicalDamage; }
	void SetCatVoodoo(float catVoodoo) { m_catVoodoo = catVoodoo; }
	void SetAttackSpeed(float attackSpeed) { m_attackSpeed = attackSpeed; }
	void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
	void SetArmor(float armor) { m_armor = armor; }
	void SetCatVoodooResist(float catVoodooResist) { m_catVoodooResist = catVoodooResist; }
	void SetRange(float range) { m_range = range; }
};

#endif