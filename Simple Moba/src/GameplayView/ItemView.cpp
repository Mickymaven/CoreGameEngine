#include "ItemView.h"


ItemView::ItemView() {}
ItemView::~ItemView() {}

Item *  ItemView::GetItem() { return m_item; }
AbilityView * ItemView::GetAbilityView() { return m_abilityView;  }
UIElement * ItemView::GetIcon() { return &m_icon; }
TooltipInfoItem * ItemView::GetTooltip() { return &m_tooltip; }

void  ItemView::SetItem(Item * item) { m_item = item; }
void ItemView::SetAbilityView(AbilityView * abilityView) { m_abilityView = abilityView; }


void ItemView::PushTooltipStats()
{
	char bufferNumber[10];
	bool notZero = false;
	TootipItemStat * stat = new TootipItemStat();

	for (int index = 0; index <= statNameCount; index++)
	{
		notZero = false;

		switch (index)
		{
		case statArmor:
			if(m_item->m_armor != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_armor);
				stat->fNumber = m_item->m_armor;
				stat->name = "Armor";
				notZero = true;
			}
			break;
		case statAttackSpeed:
			if(m_item->m_attackSpeed != 0.0f)
			{
				sprintf_s(bufferNumber, "%.1f", m_item->m_attackSpeed);
				stat->fNumber = m_item->m_attackSpeed;
				stat->name = "Attack Speed";
				notZero = true;
			}
			break;
		case statCatVoodoo:
			if(m_item->m_catVoodoo != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_catVoodoo);
				stat->fNumber = m_item->m_catVoodoo;
				stat->name = "Cat Voodoo";
				notZero = true;
			}
			break;
		case statCatVoodooResist:
			if(m_item->m_catVoodooResist != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_catVoodooResist);
				stat->fNumber = m_item->m_catVoodooResist;
				stat->name = "Cat Voodoo Resist";
				notZero = true;
			}
			break;
		case statHealth:
			if(m_item->m_health != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_health);
				stat->fNumber = m_item->m_health;
				stat->name = "Health";
				notZero = true;
			}
			break;
		case statHealthRegen:
			if(m_item->m_healthRegen != 0.0f)
			{
				sprintf_s(bufferNumber, "%.1f", m_item->m_healthRegen);
				stat->fNumber = m_item->m_healthRegen;
				stat->name = "Health Regen";
				notZero = true;
			}
			break;
		case statMaxHealth:
			if(m_item->m_maxHealth != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_maxHealth);
				stat->fNumber = m_item->m_maxHealth;
				stat->name = "Maximum Health";
				notZero = true;
			}
			break;
		case statMoveSpeed:
			if(m_item->m_moveSpeed != 0.0f)
			{
				sprintf_s(bufferNumber, "%.1f", m_item->m_moveSpeed);
				stat->fNumber = m_item->m_moveSpeed;
				stat->name = "Move Speed";
				notZero = true;
			}
			break;
		case statPhysicalDamage:
			if(m_item->m_physicalDamage != 0.0f)
			{
				sprintf_s(bufferNumber, "%.0f", m_item->m_physicalDamage);
				stat->fNumber = m_item->m_physicalDamage;
				stat->name = "Physical Damage";
				notZero = true;
			}
			break;
		case statRange:
			if(m_item->m_range != 0.0f)
			{
				sprintf_s(bufferNumber, "%.1f", m_item->m_range);
				stat->fNumber = m_item->m_range;
				stat->name = "Range";
				notZero = true;
			}
			break;
		}

		if (notZero)
		{

			stat->number = bufferNumber;
			m_tooltipStats.push_back(*stat);
			stat = new TootipItemStat();
		}
	}
	
	m_tooltip.SetStats(&m_tooltipStats);
}