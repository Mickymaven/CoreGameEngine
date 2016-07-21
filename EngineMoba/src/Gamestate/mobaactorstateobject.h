#if !defined(MOBAACTORSTATEOBJECT_H)
#define MOBAACTORSTATEOBJECT_H

#include <vector>
using std::vector;

#include "../Actors/Actor.h"

struct MobaActorStateObject
{
protected:
	static vector <vector <Actor *> *> * m_actorTeams;
	//static vector<int> m_teamEnums;
	//static vector<string*> *m_teamStrings;

public:
	vector <vector <Actor *> *> * GetActorTeams();

	void SetActorTeams(vector <vector <Actor *> *> * actorTeams);
};

#endif