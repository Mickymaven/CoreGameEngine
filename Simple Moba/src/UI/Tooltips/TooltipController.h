#if !defined(TOOLTIPCONTROLLER_H)
#define TOOLTIPCONTROLLER_H

#include "../../../../EngineGameModel/src/Utility/LMTimer.h"
#include "../../../../EngineMoba/src/Ability/Ability.h"
#include "TooltipInfo.h"
#include "TooltipInfoItem.h"



enum TooltipState
{
	tooltipStateActive,
	tooltipStateInactive,
	tooltipCount
};

class TooltipController
{

protected:

	LMTimer m_timeout; //countdown when not in tooltip zone
	TooltipInfo * m_activeTooltip;
	Ability * m_abilityOwnsTooltip;
	TooltipState m_state;

public:
	TooltipController();
	~TooltipController();

	bool Init();
	
	void Update(float deltaTime);
	void Render();

	void ActivateTooltipItem(RECT * bounds, TooltipInfoItem * tooltipInfoItem, Ability * ability);
	void ActivateTooltipAbility(RECT * bounds, TooltipInfo * tooltipInfo, Ability * ability);
	void ActivateTooltipBuff(RECT * bounds, TooltipInfo * tooltipInfo);

	void ActiveTooltipSetup(RECT * bounds);

	//accessors
	Ability * GetAbilityOwner();
	LMTimer * GetTimer();

};

#endif