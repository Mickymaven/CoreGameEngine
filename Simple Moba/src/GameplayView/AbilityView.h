#if !defined(ABILITYVIEW_H)
#define ABILITYVIEW_H

#include <d3dx9.h>
#include "../../../EngineMoba/src/Ability/Ability.h"

#include "../UI/Tooltips/TooltipInfoAbility.h"
#include "../UI/Tooltips/TooltipEffect.h"

class AbilityView
{
protected:
	Ability * m_ability;

	TooltipInfoAbility * m_tooltip;
	vector < TooltipEffect > * m_effects;

public:
	AbilityView();
	AbilityView(Ability * ability);
	~AbilityView();

	void virtual Render();

	Ability * GetAbility();

	bool IsActive();


	void SetTooltip(TooltipInfoAbility * tooltip);
	void SetEffects(vector<TooltipEffect> * effects);


	TooltipInfoAbility * GetTooltip();
	vector<TooltipEffect> * GetEffects();

};


#endif