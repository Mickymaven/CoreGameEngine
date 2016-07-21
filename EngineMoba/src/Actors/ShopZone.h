#if !defined(SHOPZONE_H)
#define SHOPZONE_H

#include <string>
using std::string;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../CoreGame/src/Gameplay/TeamName.h"

class ShopZone
{
private:
	static LMVector3 m_tempVec;

	TeamName m_team;

	LMVector3 m_position;
	float m_radius;
	string m_name;
	bool m_isVisibleThisUpdate;

public:
	ShopZone();
	ShopZone(LMVector3 & position, float radius, string name, TeamName team);
	~ShopZone();

	LMVector3 * GetPosition();
	float GetRadius();
	string * GetName();
	
	bool IsUsable(const LMVector3 & playerPosition, TeamName team);

	bool IsInRange(const LMVector3 & playerPosition);
	
	//Access
	bool GetIsVisibleThisUpdate();
	
	//Mutate
	void SetIsVisibleThisUpdate(bool result);
};

#endif

