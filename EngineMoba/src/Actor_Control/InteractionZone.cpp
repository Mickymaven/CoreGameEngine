#include "InteractionZone.h"

InteractionZone::InteractionZone()
{

}

InteractionZone::~InteractionZone()
{

}

bool InteractionZone::Init(InteractionZoneState interactionZoneState)
{
	m_interactionZoneState = interactionZoneState;

	return true;
}

void InteractionZone::Update(float deltaTime)
{
	switch (m_interactionZoneState)
	{
	case interactionZoneStateActive:Active(deltaTime); break;
	case interactionZoneStateInactive:Inactive(deltaTime); break;
	case interactionZoneStateCount:default: break;
	}
}

void InteractionZone::OnEnterActive()
{
	m_interactionZoneState = interactionZoneStateActive;
}

void InteractionZone::Active(float deltaTime)
{
	//
}

void InteractionZone::OnExitActive()
{

}

void InteractionZone::OnEnterInactive()
{
	m_interactionZoneState = interactionZoneStateInactive;
}

void InteractionZone::Inactive(float deltaTime)
{
	//
}

void InteractionZone::OnExitInactive()
{

}

void InteractionZone::ExitCurrentState()
{
	switch (m_interactionZoneState)
	{
	case interactionZoneStateActive:OnExitActive(); break;
	case interactionZoneStateInactive:OnExitInactive(); break;
	case interactionZoneStateCount:default: break;
	}
}

InteractionZoneState InteractionZone::GetInteractionZoneState()
{
	return m_interactionZoneState;
}

LMVector3 * InteractionZone::GetPosition()
{
	return &m_position;
}

float InteractionZone::GetRadius()
{
	return m_radius;
}

void InteractionZone::SetPosition(LMVector3 * position)
{
	m_position = *position;
}

void InteractionZone::SetRadius(float radius)
{
	m_radius = radius;
}