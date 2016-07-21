#if !defined(MOBACONTROLLERSHAREDDATA_H)
#define MOBACONTROLLERSHAREDDATA_H

#include "MobaActorStateObject.h"
#include "../../../CoreGame/src/Gameplay/TeamName.h" //forward dependency

struct MobaControllerSharedData
{
private:
	static vector <Actor*> * team;

public:
	static MobaActorStateObject * m_mobaActorStateObject;
	static vector<vector <Actor*> *> * teams;
	
	static void SetMobaActorStateObject(MobaActorStateObject * mobaActorStateObject);
	static Actor * SelectTargetInRange(LMVector3 * position, TeamName teamName, float radius, bool excludeNeutral);
};

#endif