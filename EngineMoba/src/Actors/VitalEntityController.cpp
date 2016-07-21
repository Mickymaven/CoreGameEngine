#include "VitalEntityController.h"

VitalEntityController::VitalEntityController()
{

}

VitalEntityController::VitalEntityController(VitalEntity * vitalEntity)
{
	m_vitalEntity = vitalEntity;

	m_vitalEntity->SetVoidToController((void*)this);
}

VitalEntityController::~VitalEntityController()
{
	//toto potenetially delete everything in m_damageReceived

	for (unsigned int i = 0; i < m_damageReceived.size(); i++)
	{
		if (m_damageReceived.at(i) != nullptr)
		{
			delete m_damageReceived.at(i);
			m_damageReceived.at(i) = nullptr;
		}
	}

	for (unsigned int i = 0; i < m_healingReceived.size(); i++)
	{
		if (m_healingReceived.at(i) != nullptr)
		{
			delete m_healingReceived.at(i);
			m_healingReceived.at(i) = nullptr;
		}
	}
}

vector<Damage *> * VitalEntityController::GetDamageRecieved() { return &m_damageReceived; }
vector<Healing*>* VitalEntityController::GetHealingRecieved() { return &m_healingReceived; }
VitalEntity * VitalEntityController::GetVitalEntity() { return m_vitalEntity; }