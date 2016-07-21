#if !defined(ITEMVIEW_H)
#define ITEMVIEW_H

#include "../../../EngineMoba/src/Item/Item.h"
#include "../../../EngineMoba/src/Actors/StatName.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "../UI/Tooltips/TooltipInfoItem.h"
#include "../GameplayView/AbilityView.h"


class ItemView
{
private:
	Item * m_item;

	UIElement m_icon;
	TooltipInfoItem m_tooltip;

	vector < TootipItemStat > m_tooltipStats;

	AbilityView * m_abilityView;

public:
	ItemView();
	~ItemView();

	Item * GetItem();
	AbilityView * GetAbilityView();
	UIElement * GetIcon();
	TooltipInfoItem * GetTooltip();
	
	void SetItem(Item * item);
	void SetAbilityView(AbilityView * abilityView);
	void PushTooltipStats();

};

#endif
