#if !defined(OWLQUESTSTANDARD1CONFIG_H)
#define OWLQUESTSTANDARD1CONFIG_H

#include <vector>
using std::vector;

#include "../../../../EngineGameModel/src/Maths/LMVector3.h"

class OwlQuestStandard1Config
{
private:
	//NPC spawn position
	//NPC spawn time
	//Quest 1 Item spawn locations

public:
	vector<LMVector3> m_itemSpawns;

	OwlQuestStandard1Config();
	~OwlQuestStandard1Config();
};

#endif