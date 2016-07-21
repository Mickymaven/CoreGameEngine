#if !defined(BUFF_H)
#define BUFF_H

#include <vector>
using std::vector;


#include "../../../EngineGameModel/src/Utility/LMTimer.h"
#include "../../../Simple Moba/src/UI/Tooltips/TooltipInfoBuff.h"//forwerd dependency

#include "../Actors/StatChangeObject.h"
#include "../Actors/VitalEntity.h"


class Buff
{
private:
	LMTimer m_timer;
	StatChangeObject m_statsToChange;

	//VitalEntity * m_source;
	//StatChangeObject * m_ownerStatChangeObject;

	int m_buffClass;//buff enum abstracted into int so our client ui can access flyweight tooltip objects from a vector

	char buffer[1000];
	double hpAdded;

	double lastElapsed;
	double  hpAddedOnLastElapsed;
	double hpAddedExact;

	bool m_isCurve;
	float m_hpToCurve;
protected:

public:
	Buff();
	~Buff();
	
	bool Init(int buffClass,float duration);
	void Update(float deltaTime);
	void HP(float deltaTime);

	const int & GetBuffClass();

	LMTimer * GetTimer();
	StatChangeObject * GetStatChangeObject();
	StatChangeObject * stat();

	void SetHPCurve(bool isCurve, float hp);
};

#endif