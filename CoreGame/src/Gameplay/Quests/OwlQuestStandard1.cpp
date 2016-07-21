#include "OwlQuestStandard1.h"

OwlQuestStandard1::OwlQuestStandard1()
{
}

OwlQuestStandard1::~OwlQuestStandard1()
{
}

bool OwlQuestStandard1::Init(OwlQuestStandard1Config * config)
{
	VitalEntity * ve = nullptr;

	m_items.m_items.resize(2);
	//m_items.m_isActive.resize(2);

	m_items.m_items.at(0).Init(
		itemOwlDrill,
		true,
		itemConditionAny);

	*m_items.m_items.at(0).GetVitalEntity() = VitalEntity(new ActorStats(),
		LMVector3(-5.0f, 0.2f, -5.0f),//pos
		LMVector3(0.0f, 0.0f, 0.0f),//rot
		LMVector3(1.0f, 1.0f, 1.0f),//sca
		LMVector3(0.0f, 0.0f, 0.0f),//vel
		LMVector3(0.0f, 0.0f, 0.0f),//spi
		LMVector3(0.0f, 0.0f, 0.0f),//res
		0.0f);//acc
	
	m_items.m_items.at(1).Init(
		itemOwlDrill,
		true,
		itemConditionAny);

	*m_items.m_items.at(1).GetVitalEntity() = VitalEntity(new ActorStats(),
		LMVector3(-5.0f, 0.200f, -5.0f),//pos
		LMVector3(0.0f, 0.0f, 0.0f),//rot
		LMVector3(1.0f, 1.0f, 1.0f),//sca
		LMVector3(0.0f, 0.0f, 0.0f),//vel
		LMVector3(0.0f, 0.0f, 0.0f),//spi
		LMVector3(0.0f, 0.0f, 0.0f),//res
		0.0f);//acc

	for (unsigned int i = 0; i < m_items.m_items.size(); i++)
	{
		m_items.m_items.at(i).GetVitalEntity()->GetPhysicsObject()->SetPosition(config->m_itemSpawns.at(i));
	}

	m_rewardInventory.GetInventory()->push_back(itemNomBar);
	m_rewardInventory.SetInventoryID(invOwlQuestS1Reward);
	m_inventories.push_back(&m_rewardInventory);

	return true;
}

void OwlQuestStandard1::ActionPreQuest()
{
	for (unsigned int i = 0; i < m_items.m_items.size(); i++)
	{
		m_items.m_items.at(i).SetIsActive(false);
		m_items.m_items.at(i).GetVitalEntity()->SetToState(vitalEntityStateInactive);
	}
}

void OwlQuestStandard1::ActionStartQuest()
{
	for (unsigned int i = 0; i < m_items.m_items.size(); i++)
	{
		m_items.m_items.at(i).SetIsActive(true);
		m_items.m_items.at(i).GetVitalEntity()->SetToState(vitalEntityStateActive);

	}
}

void OwlQuestStandard1::ActionEndQuest()
{
	for (unsigned int i = 0; i < m_items.m_items.size(); i++)
	{
		m_items.m_items.at(i).SetIsActive(false);
	}
}
