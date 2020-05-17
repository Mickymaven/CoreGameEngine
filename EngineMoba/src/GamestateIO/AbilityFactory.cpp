#include "AbilityFactory.h"

AbilityFactory::AbilityFactory()
{

}

AbilityFactory::~AbilityFactory()
{

}

bool AbilityFactory::ConstructAbility(
	Ability ** abilityOut,
	AbilityName ability,
	Actor * actor,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors
	)
{
	switch (ability)
	{
	case abilityRecall: m_constructedAbility = new Recall(actor); break;
	case abilitySleep: m_constructedAbility = new ZZzzz(actor); break;
	case abilityNomBarHeal: m_constructedAbility = new NomBarHeal(actor); break;
	case abilityBudgetMenuBeverage: m_constructedAbility = new BudgetMenuBeverage(actor); break;
	case abilityRideBike: m_constructedAbility = new RideBike(actor); break;
	case abilityCosmicSpaghetti: m_constructedAbility = new CosmicSpaghetti(actor); break;
	case abilityHuntOfTheHaunted: m_constructedAbility = new HuntOfTheHaunted(actor); break;
	case abilitySpookySpaceMeringue: m_constructedAbility = new SpookySpaceMeringue(actor); break;
	case abilityTheSlurpening: m_constructedAbility = new TheSlurpening(actor); break;
	case abilityAntiFireball: m_constructedAbility = new AntiFireball(actor); break;
	case abilityMotoBoost: m_constructedAbility = new MotoBoost(actor); break;
	case abilityEternalLight: m_constructedAbility = new EternalLight(actor); break;
	case abilityElixirBurst: m_constructedAbility = new ElixirBurst(actor); break;
	case abilityHiddenPower: m_constructedAbility = new HiddenPower(actor); break;
	case abilityValiantLeap: m_constructedAbility = new ValiantLeap(actor); break;
	case abilityHealTurret: m_constructedAbility = new HealTurret(actor); break;
	default:return false;
	}
	
	m_constructedAbility->SetTeams(teamActors, opponentActors, neutralActors);

	*abilityOut = m_constructedAbility;
	return true;
}
