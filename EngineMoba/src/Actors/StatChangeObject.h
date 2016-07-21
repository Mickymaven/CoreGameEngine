#if !defined(STATCHANGEOBJECT_H)
#define STATCHANGEOBJECT_H

class StatChangeObject
{
private:


public:
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

	StatChangeObject();
	~StatChangeObject();

	void Update(float deltaTime);
	
	void Zero();
	StatChangeObject& operator += (const StatChangeObject&);

	//access
	float GetHealth() { return m_health; };
	float GetMaxHealth() { return m_maxHealth; };
	float GetHealthRegen() { return m_healthRegen; }
	float GetPhysicalDamage() { return m_physicalDamage; };
	float GetCatVoodoo() { return m_catVoodoo; };
	float GetAttackSpeed() { return m_attackSpeed; }
	float GetMoveSpeed() { return m_moveSpeed; }
	float GetArmor() { return m_armor; }
	float GetCatVoodooResist() { return m_catVoodooResist; }
	float GetRange() { return m_range; }

	//mutate
	void SetHealth(float health) {m_health = health;}
	void SetMaxHealth(float maxHealth) {m_maxHealth = maxHealth;}
	void SetHealthRegen(float healthRegen) {m_healthRegen = healthRegen;}
	void SetPhysicalDamage(float physicalDamage) {m_physicalDamage = physicalDamage;}
	void SetCatVoodoo(float catVoodoo){m_catVoodoo = catVoodoo;}
	void SetAttackSpeed(float attackSpeed) {m_attackSpeed = attackSpeed;}
	void SetMoveSpeed(float moveSpeed) {m_moveSpeed = moveSpeed;}
	void SetArmor(float armor) {m_armor = armor;}
	void SetCatVoodooResist(float catVoodooResist) {m_catVoodooResist = catVoodooResist;}
	void SetRange(float range)  { m_range = range; }

	//add
	void AddHealth(float health);
	void AddMaxHealth(float maxHealth);
	void AddHealthRegen(float healthRegen);
	void AddPhysicalDamage(float physicalDamage);
	void AddCatVoodoo(float catVoodoo);
	void AddAttackSpeed(float attackSpeed);
	void AddMoveSpeed(float moveSpeed);
	void AddArmor(float armor);
	void AddCatVoodooResist(float catVoodooResist);
	void AddRange(float range);

};
	
#endif