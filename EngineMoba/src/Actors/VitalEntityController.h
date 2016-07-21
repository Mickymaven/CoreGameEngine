#if !defined(VITALENTITYCONTROLLER_H)
#define VITALENTITYCONTROLLER_H

#include <vector>
using namespace std;

#include "VitalEntity.h"
#include "../VitalEffect/Damage.h"
#include "../VitalEffect/Healing.h"

#include <functional> //we are making fstd::funtctions to put in our vital entity for OnHit callbacks.
using namespace std::placeholders;

class VitalEntityController
{
private:
	VitalEntity * m_vitalEntity;
protected:
	vector<Damage * > m_damageReceived;
	vector<Healing * > m_healingReceived;

public:
	VitalEntityController();
	VitalEntityController(VitalEntity * vitalEntity);
	~VitalEntityController();

	//Accessors
	vector<Damage *> * GetDamageRecieved();
	vector<Healing *> * GetHealingRecieved();
	VitalEntity * GetVitalEntity();
};

#endif