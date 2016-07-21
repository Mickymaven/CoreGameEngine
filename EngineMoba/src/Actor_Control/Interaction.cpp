#include "Interaction.h"

#include "Windows.h"

Interaction::Interaction()
{
	m_owner = nullptr;
	m_ownerPosition = nullptr;
}

Interaction::~Interaction()
{

}

void Interaction::Update(float deltaTime)
{
	OutputDebugString("Interaction Update SHOULD NOT HAPPEN\n\n");
}

vector <InteractionZone*> * Interaction::GetInteractionZones()
{
	return &m_interactionZones;
}