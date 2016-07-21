#if !defined(HEAL_H)
#define HEAL_H

#include "HealthEffect.h"

class Healing : public HealthEffect
{
private:

public:
	Healing();
	~Healing();

	void Init(
		float duration,
		float timer,
		float damageValue,
		HealthEffectApplicationType damageApplicationType,
		VitalEntity * owner,
		void * abilitySource,
		VitalEntity * target);
};

#endif