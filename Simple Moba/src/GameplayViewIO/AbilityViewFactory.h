#if !defined(ABILITYVIEWFACTORY_H)
#define ABILITYVIEWFACTORY_H

#include <vector>
using std::vector;

#include <d3d9.h>

#include "../../../EngineMoba/src/Ability/Ability.h"
#include "../../../CoreGame/src/Gameplay/Characters/AbilitySlotType.h"
#include "../../../CoreGame/src/Gameplay/Abilities/AbilityName.h"

#include "../GameplayView/AbilityView.h"
#include "../GameplayView/Abilities/AbilityViewHeaders.h"

#include "../UI/Tooltips/TooltipInfoAbility.h"
#include "../UI/Tooltips/TooltipEffect.h"

class AbilityViewFactory
{
private:
	vector<TooltipInfoAbility*> m_abilityTooltips;
	vector< vector < TooltipEffect> > m_abilityEffects;

public:
	AbilityViewFactory();
	~AbilityViewFactory();
	
	bool ConstructAbilityViewVector(LPDIRECT3DDEVICE9 device, vector<AbilityView*> * abilityViewOut, vector<AbilityName> * names, vector<Ability*> * ability);
	bool ConstructAbilityView(LPDIRECT3DDEVICE9 device, AbilityView ** abilityViewOut, AbilityName abilityName, Ability * ability);
};

#endif