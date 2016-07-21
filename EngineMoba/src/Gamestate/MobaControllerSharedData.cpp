#include "MobaControllerSharedData.h"

MobaActorStateObject * MobaControllerSharedData::m_mobaActorStateObject = NULL;

vector<vector <Actor*> *> * MobaControllerSharedData::teams;
vector <Actor*> * MobaControllerSharedData::team;//temp

void MobaControllerSharedData::SetMobaActorStateObject(MobaActorStateObject * mobaActorStateObject)
{
	m_mobaActorStateObject = mobaActorStateObject;
	teams = m_mobaActorStateObject->GetActorTeams();
}

Actor * MobaControllerSharedData::SelectTargetInRange(LMVector3 * position, TeamName teamName, float radius, bool excludeNeutral)
{
	Actor * target = nullptr;
	LMVector3 * targetPosition = nullptr;
	float hitDist, a, b, hypoSquared, closestDistSquared = 9999.0f;

	for (unsigned int iTeam = 0; iTeam < teams->size(); iTeam++)
	{
		if (excludeNeutral) if (iTeam == teamNameNeutral) continue;//skip neutral team while selecting targets
		if (iTeam == teamName) continue;

		team = teams->at(iTeam);

		for (unsigned int iActor = 0; iActor < team->size(); iActor++)
		{
			if (team->at(iActor)->GetVitalEntityState() != vitalEntityStateInactive)
			{
				hitDist = radius + team->at(iActor)->GetPhysicsObject()->GetRadius();

				targetPosition = team->at(iActor)->GetPhysicsObject()->GetPosition();
				a = abs(position->x - targetPosition->x);
				b = abs(position->z - targetPosition->z);
				hypoSquared = (a*a + b*b);
				
				if (hypoSquared < hitDist*hitDist)
				{
					if (hypoSquared < closestDistSquared)
					{
						closestDistSquared = hypoSquared;
						target = team->at(iActor);
					}
				}
			}
		}
	}

	return target;
}