
#include "AbilityView.h"

AbilityView::AbilityView(){}

AbilityView::AbilityView(Ability * ability)
	: m_ability(ability)
{

}

AbilityView::~AbilityView(){}

void AbilityView::Render() {}

Ability * AbilityView::GetAbility() { return m_ability; }

bool AbilityView::IsActive()
{
	if (m_ability->GetState() == abilityInactive) return false;
	
	return true;
}

void AbilityView::SetTooltip(TooltipInfoAbility * tooltip) { m_tooltip = tooltip; }
void AbilityView::SetEffects(vector<TooltipEffect> * effects) { m_effects = effects; }
TooltipInfoAbility * AbilityView::GetTooltip() { return m_tooltip; }
vector<TooltipEffect> * AbilityView::GetEffects() { return m_effects; }
