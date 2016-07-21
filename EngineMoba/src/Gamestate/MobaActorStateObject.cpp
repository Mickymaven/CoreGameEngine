#include "MobaActorStateObject.h"

vector <vector <Actor *> *> * MobaActorStateObject::m_actorTeams = NULL;

vector <vector <Actor *> *> * MobaActorStateObject::GetActorTeams()
{
	return m_actorTeams;
}

void MobaActorStateObject::SetActorTeams(vector <vector <Actor *> *> * actorTeams)
{
	m_actorTeams = actorTeams;
}