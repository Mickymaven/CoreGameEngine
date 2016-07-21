#include "ShopZone.h"

LMVector3 ShopZone::m_tempVec;

ShopZone::ShopZone()
{

}

ShopZone::ShopZone(LMVector3 & position, float radius, string name, TeamName team)
{
	m_team = team;
	m_position = position;
	m_radius = radius;
	m_name = name;
	m_isVisibleThisUpdate = false;
}

ShopZone::~ShopZone()
{

}

LMVector3 * ShopZone::GetPosition()
{
	return &m_position;
}

float ShopZone::GetRadius()
{
	return m_radius;
}


string * ShopZone::GetName()
{
	return &m_name;
}

bool ShopZone::IsUsable(const LMVector3 & playerPosition, TeamName team)
{
	if ( m_team == team || m_team == teamNameNeutral)
	{
		m_isVisibleThisUpdate = IsInRange(playerPosition);
	}
	else m_isVisibleThisUpdate = false;

	return m_isVisibleThisUpdate;
}

bool ShopZone::IsInRange(const LMVector3 & playerPosition)
{
	m_tempVec = LMVector3();
	m_tempVec.x = (m_position.x - playerPosition.x);
	//temp.y = (m_position.y - playerPosition.y);
	m_tempVec.z = (m_position.z - playerPosition.z);

	return m_tempVec.LengthSq() < m_radius*m_radius;
}

bool ShopZone::GetIsVisibleThisUpdate()
{
	return m_isVisibleThisUpdate;
}

void ShopZone::SetIsVisibleThisUpdate(bool result)
{
	m_isVisibleThisUpdate = result;
}
