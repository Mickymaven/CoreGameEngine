#if !defined(DAMAGE_H)
#define DAMAGE_H

#include "../Actors/VitalEntity.h"
#include "HealthEffect.h"

enum DamageType
{
	damageTypeDamage,
	damageTypeCatVoodoo,
	damageTypeCount
};

enum DamageOriginType
{
	damageOriginOpponent,
	damageOriginNeutral,
	damageOriginCount
};

class Damage : public HealthEffect
{
private:
	DamageType m_damageType;

public:
	Damage();
	~Damage();

	void Init(
	float duration,
	float timer,
	float damageValue,
	DamageType damageType,
	HealthEffectApplicationType damageApplicationType,
	VitalEntity * owner,
	void * abilitySource,
	VitalEntity * target);

	DamageType GetDamageType();

};

#endif