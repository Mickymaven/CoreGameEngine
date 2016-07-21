#include "VitalEntity.h"


VitalEntity::VitalEntity()
{

}

VitalEntity::VitalEntity(
	ActorStats * stats,
	LMVector3 position,
	LMVector3 rotation,
	LMVector3 scale,
	LMVector3 velocity,
	LMVector3 spin,
	LMVector3 resize,
	float acceleration)
	:Sprite(position, rotation, scale, velocity, spin, resize, acceleration)
{
	m_controller = NULL;
	m_vitalEntityType = vitalEntityTypeVitalEntity;
	m_vitalEntityState = vitalEntityStateActive;
	m_stats = *stats;
	m_stats.CalcStatsFromBase();
	m_stats.SetHealth(m_stats.GetMaxHealth());
}

VitalEntity::~VitalEntity()
{


}

void VitalEntity::OnEnterVitalEntityStateActive()
{
	m_vitalEntityState = vitalEntityStateActive;

}

void VitalEntity::VitalEntityStateActiveBehaviour(float deltaTime)
{


}

void VitalEntity::OnExitVitalEntityStateActive()
{


}

void VitalEntity::OnEnterVitalEntityStateIntargetable()
{
	m_vitalEntityState = vitalEntityStateIntargetable;
}

void VitalEntity::VitalEntityStateIntargetableBehaviour(float deltaTime)
{
}

void VitalEntity::OnExitVitalEntityStateIntargetable()
{
}

void VitalEntity::OnEnterVitalEntityStateInactive()
{
	m_vitalEntityState = vitalEntityStateInactive;
}

void VitalEntity::VitalEntityStateInactiveBehaviour(float deltaTime)
{


}

void VitalEntity::OnExitVitalEntityStateInactive()
{


}

void VitalEntity::OnEnterForState(VitalEntityState state)
{

}

void VitalEntity::OnExitForState(VitalEntityState state)
{

}

void VitalEntity::ExitCurrentState()
{
	switch (m_vitalEntityState)
	{
	case vitalEntityStateActive: OnExitVitalEntityStateActive();
		break;
	case vitalEntityStateInactive: OnExitVitalEntityStateInactive();
		break;
	case vitalEntityStateCount:
	default:

		break;
	};
}

void VitalEntity::SetToState(VitalEntityState newState)
{
	switch (newState)
	{
	case vitalEntityStateActive:
		ExitCurrentState();
		OnEnterVitalEntityStateActive();

		break;
	case vitalEntityStateInactive:
	
		ExitCurrentState();
		OnEnterVitalEntityStateInactive();
		break;

	default:break;
	}
}

void VitalEntity::SetInactive()
{
	ExitCurrentState();
	OnEnterVitalEntityStateInactive();
}

void VitalEntity::SetIntargetable()
{
	ExitCurrentState();
	OnEnterVitalEntityStateIntargetable();
}

void VitalEntity::SetActive()
{
	ExitCurrentState();
	OnEnterVitalEntityStateActive();
}

void VitalEntity::OnHit(VitalEntity * owner)
{
	if (m_onHitCallback) m_onHitCallback(owner);
}

//Accessors //////////////////////
void * VitalEntity::GetVoidToController() { return m_controller; }

VitalEntityType VitalEntity::GetVitalEntityType() { return m_vitalEntityType; }

VitalEntityState VitalEntity::GetVitalEntityState() { return m_vitalEntityState; }

string * VitalEntity::GetVitalEntityClassName() { return &m_className; }

StatChangeObject * VitalEntity::GetStatChangeObject() { return &m_statChangeObject; }

ActorStats * VitalEntity::GetStats() { return &m_stats; }

string VitalEntity::GetUniqueName() { return m_uniqueName; }


// Mutators ////////////////////////

void VitalEntity::SetOnHitCallback(std::function<void(VitalEntity * owner)> f) { m_onHitCallback = f; }

void VitalEntity::SetVitalEntityType(VitalEntityType type) { m_vitalEntityType = type; }

void VitalEntity::SetVoidToController(void * controller) { m_controller = controller; }

void VitalEntity::SetName(string name) { m_className = name; }

void VitalEntity::SetStatChangeObject(StatChangeObject statChangeObject) { m_statChangeObject = statChangeObject; }

void VitalEntity::SetActorStats(ActorStats stats) { m_stats = stats; }

void VitalEntity::SetUniqueName(string uniqueName){ m_uniqueName = uniqueName; }
