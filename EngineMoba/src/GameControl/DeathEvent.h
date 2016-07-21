#if !defined(DEATHEVENT_H)
#define DEATHEVENT_H

#include <vector>
using std::vector;

#include "../Actors/Actor.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../VitalEffect/Damage.h"

class DeathEvent
{
private:
	VitalEntity * m_victim;
	vector<VitalEntity * > m_assists;
	vector<Damage * > m_damageContributions;
	VitalEntity * m_finalBlowOrigin;
	DamageOriginType m_finalBlowType;
	
public:
	DeathEvent(VitalEntity * victim, DamageOriginType finalBlowType, VitalEntity * finalBlowOrigin);
	~DeathEvent();
	void AddAssist(VitalEntity * assist);
	void AddDamage(Damage * damage);


	//Accessors
	VitalEntity * GetVictim();
	vector<VitalEntity * > * GetAssists();
	vector<Damage * > * GetDamageContributions();
	VitalEntity * GetFinalBlowOrigin();
	DamageOriginType * GetFinalBlowType();

};

#endif