#include "ItemEntity.h"

ItemEntity::ItemEntity()
{
	m_itemClass = -1;
}

ItemEntity::ItemEntity(ItemEntity & i)
{
	m_itemClass = i.m_itemClass;
	m_vitalEntity = i.m_vitalEntity;
}

ItemEntity::~ItemEntity()
{
}

bool ItemEntity::Init(int itemClass,
	bool isActive, //bool m_isActive;
	ItemConditionScheme condition //ItemConditionScheme m_condition;
	)
{
	m_vitalEntity.SetToState(vitalEntityStateInactive);

	m_itemClass = itemClass;

	m_isActive = false;
	m_condition = condition;


	return true;
}

int ItemEntity::GetitemClass()
{
	return m_itemClass;
}

VitalEntity * ItemEntity::GetVitalEntity()
{
	return &m_vitalEntity;
}

ItemRecieveReturn ItemEntity::IsRecievable(Character * character)
{
	if (m_isActive == false)
	{
		return itemRecieveNo;
	}

	switch (m_condition)
	{
		case itemConditionAny:{

			return itemRecieveOK;
		
		} break;
		case itemConditionTeam:{
		
		
		}break;
		case itemConditionPlayerList:{
		
		
		}break;
		case itemConditionNone:{
		
		
		}break;

		default: return itemRecieveError;
	}

	return itemRecieveError;
}

bool ItemEntity::GetIsActive()
{
	return m_isActive;
}

void ItemEntity::SetIsActive(bool activeState)
{
	m_isActive = activeState;
}
