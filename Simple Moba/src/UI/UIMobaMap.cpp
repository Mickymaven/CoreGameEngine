#include "UIMobaMap.h"

UIMobaMap::UIMobaMap()
{

}

UIMobaMap::~UIMobaMap()
{

}

bool UIMobaMap::Init(StandardMatch5v5State * gameStateIn, GameConfiguration * gameConfigurationIn)
{
	gameConfiguration = gameConfigurationIn;
	gameState = gameStateIn;

	m_positionMax = LMVector2(400.0f, 400.0f);
	
	m_playerTeams.resize(2);
	m_playerTeams.at(0) = gameState->GetTeamControllersAsVector(yellowTeamName);
	m_playerTeams.at(1) = gameState->GetTeamControllersAsVector(purpleTeamName);

	//m_icons.resize(0);

	m_playerIcons.resize(2);

	m_mapSize = LMVector3(200.0f, 0.0f, 200.0f);
	m_mapOrigin = LMVector3((float)g_clientSizeRect->right - m_mapSize.x, 0.0f, (float)g_clientSizeRect->bottom - m_mapSize.z);
	
	m_bounds.left = m_mapOrigin.x;
	m_bounds.right = m_mapOrigin.x + m_mapSize.x;

	m_bounds.top = m_mapOrigin.z;
	m_bounds.bottom = m_mapOrigin.z + m_mapSize.z;
	
	for (unsigned int teamCount = 0; teamCount < m_playerTeams.size(); teamCount++)
	{
		m_playerIcons.at(teamCount).resize(m_playerTeams.at(teamCount)->size());

		for (unsigned int memberCount = 0; memberCount < m_playerTeams.at(teamCount)->size(); memberCount++)
		{
			m_playerIcons.at(teamCount).at(memberCount).Init(20.0f, 20.0f, "Resources/UI/Icons/Grey.png");
			if (!m_playerIcons.at(teamCount).at(memberCount).Init()) return false;

			m_playerIcons.at(teamCount).at(memberCount).GetPosition()->x = 0.0f;
			m_playerIcons.at(teamCount).at(memberCount).GetPosition()->z = 0.0f;
		}
	}

	return true;
}


void UIMobaMap::Update(float deltaTime)
{
	for (unsigned int teamCount = 0; teamCount < m_playerTeams.size(); teamCount++)
	{
		for (unsigned int memberCount = 0; memberCount < m_playerTeams.at(teamCount)->size(); memberCount++)
		{
			m_playerIcons.at(teamCount).at(memberCount).GetPosition()->x = (g_clientSizeRect->right-m_mapSize.z) +
				( ( m_playerTeams.at(teamCount)->at(memberCount)->GetCharacter()->GetActor()->GetPhysicsObject()->GetPosition()->x
				 / m_positionMax.x) * m_mapSize.x - 0.5f*m_playerIcons.at(teamCount).at(memberCount).GetWidth() );

			m_playerIcons.at(teamCount).at(memberCount).GetPosition()->z = g_clientSizeRect->bottom - 
				( ( m_playerTeams.at(teamCount)->at(memberCount)->GetCharacter()->GetActor()->GetPhysicsObject()->GetPosition()->z
				 / m_positionMax.y) * m_mapSize.z + 0.5f*m_playerIcons.at(teamCount).at(memberCount).GetHeight() );
		}
	}
}

void UIMobaMap::Render()
{
	for (unsigned int teamCount = 0; teamCount < m_playerTeams.size(); teamCount++)
	{
		for (unsigned int memberCount = 0; memberCount < m_playerTeams.at(teamCount)->size(); memberCount++)
		{
			m_playerIcons.at(teamCount).at(memberCount).Render();
		}
	}
}

void UIMobaMap::Select(POINT * p)
{

}

void UIMobaMap::AltSelect(POINT * p)
{
	if (IsPointInBounds(p))
	{

		m_targetPosition.x = ((p->x - m_mapOrigin.x) / m_mapSize.x) * m_positionMax.x;
		m_targetPosition.y = 0.1f;
		m_targetPosition.z = (1.0f - ((p->y - m_mapOrigin.z) / m_mapSize.z)) * m_positionMax.y;


		gameState->GetControlledCharacter()->ActionWalkOrBasicAttack(0.0f, &m_targetPosition);

	}
}

bool UIMobaMap::MouseOver(POINT * p)
{
	return false;
}

bool UIMobaMap::ActionAltSelect(POINT * p, Billboard * walkIndicator)
{
	if (IsPointInBounds(p))
	{
		m_targetPosition.x = ((p->x - m_mapOrigin.x) / m_mapSize.x) * m_positionMax.x;
		m_targetPosition.y = 0.0f;
		m_targetPosition.z = (1.0f - ((p->y - m_mapOrigin.z) / m_mapSize.z)) * m_positionMax.y;

		gameState->GetControlledCharacter()->ActionWalkOrBasicAttack(0.0f, &m_targetPosition);

		walkIndicator->GetPhysicsObject()->GetPosition()->x = m_targetPosition.x;
		walkIndicator->GetPhysicsObject()->GetPosition()->y = m_targetPosition.y + 0.1f;
		walkIndicator->GetPhysicsObject()->GetPosition()->z = m_targetPosition.z;

		return true;
	}

	return false;
}