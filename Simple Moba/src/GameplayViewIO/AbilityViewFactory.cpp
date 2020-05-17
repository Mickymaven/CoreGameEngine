#include "AbilityViewFactory.h"

AbilityView * m_abilityView;

AbilityViewFactory::AbilityViewFactory()
{
	m_abilityView = nullptr;
	
	m_abilityTooltips.resize(abilityCount, NULL);
	m_abilityEffects.resize(abilityCount);

}

AbilityViewFactory::~AbilityViewFactory()
{

}

bool AbilityViewFactory::ConstructAbilityViewVector(LPDIRECT3DDEVICE9 device, vector<AbilityView*> * abilityViewOut, vector<AbilityName> * names, vector<Ability*> * ability)
{
	//wont use this for now

	return true;
}

bool AbilityViewFactory::ConstructAbilityView(LPDIRECT3DDEVICE9 device, AbilityView ** abilityViewOut, AbilityName abilityName, Ability * ability)
{

	AbilityView * m_abilityView = nullptr;

	switch (abilityName)
	{
	case abilityBasicAttack: m_abilityView = new BasicAttackView(device, (BasicAttack*)ability); break;
	//case abilityRecall: m_abilityView = new RecallView(ability); break;
	//case abilitySleep: m_abilityView = new SleepView(ability);  break;
	//case abilityNomBarHeal: m_abilityView = new NomBarHealView(ability); break;
	//case abilityBudgetMenuBeverage: m_abilityView = new BudgetMenuBeverage(ability); break;
	//case abilityRideBike:break;
	case abilityRecall: m_abilityView = new AbilityView(ability); break;
	case abilitySleep: m_abilityView = new AbilityView(ability);  break;
	case abilityNomBarHeal: m_abilityView = new AbilityView(ability); break;
	case abilityBudgetMenuBeverage: m_abilityView = new AbilityView(ability); break;
	case abilityRideBike:m_abilityView = new AbilityView(ability); break;
	//that stuff was temp, we dont have members to render, just accesss to tooltip /effect info
	case abilityCosmicSpaghetti: m_abilityView = new CosmicSpaghettiView(device, (CosmicSpaghetti*)ability); break;
	case abilityHuntOfTheHaunted: m_abilityView = new HuntOfTheHauntedView(device, (HuntOfTheHaunted*)ability); break;
	case abilitySpookySpaceMeringue: m_abilityView = new SpookySpaceMeringueView(device, (SpookySpaceMeringue*)ability); break;
	case abilityTheSlurpening: m_abilityView = new TheSlurpeningView(device, (TheSlurpening*)ability); break;
	case abilityAntiFireball: m_abilityView = new AntiFireballView(device, (AntiFireball*)ability); break;
	case abilityMotoBoost: m_abilityView = new MotoBoostView(device, (MotoBoost*)ability); break;
	case abilityEternalLight: m_abilityView = new EternalLightView(device, (EternalLight*)ability); break;
	case abilityElixirBurst: m_abilityView = new ElixirBurstView(device, (ElixirBurst*)ability); break;
	case abilityHiddenPower: m_abilityView = new HiddenPowerView(device, (HiddenPower*)ability); break;
	case abilityValiantLeap: m_abilityView = new ValiantLeapView(device, (ValiantLeap*)ability); break;
	case abilityHealTurret: m_abilityView = new HealTurretView(device, (HealTurret*)ability); break;
	default:return false;
	}


	//init tooltip-for-ability


	if (m_abilityTooltips.at(abilityName) == NULL)
	{
		m_abilityTooltips.at(abilityName) = new TooltipInfoAbility();
		
		vector < TooltipEffect> * effectVector = &m_abilityEffects.at(abilityName);

		TooltipEffect effect1;
		TooltipEffect effect2;
		//TooltipEffect effect3;
		//TooltipEffect effect4;
		//TooltipEffect effect5;

		switch (abilityName)
		{
		case abilityBasicAttack: 

			
			break;
		case abilityRecall: 
			effect1.descFirst = "sends you back to base after";
			effect1.m_number = "4";
			effect1.m_type = "seconds.";
			effect1.descSecond = "";
			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilitySleep:

			effect1.descFirst = "sends you to sleep for";
			effect1.m_number = "15";
			effect1.m_type = "seconds.";
			effect1.descSecond = "";
			m_abilityEffects.at(abilityName).push_back(effect1);

			effect2.descFirst = "Your gain";
			effect2.m_number = "100";
			effect2.m_type = "Health Points";
			effect2.descSecond = "for the duration of ZZzzz.";
			m_abilityEffects.at(abilityName).push_back(effect2);

			break;
		case abilityNomBarHeal:

			effect1.descFirst = "Heals your hero for";
			effect1.m_number = "100";
			effect1.m_type = "Health points";
			effect1.descSecond = ". This item is consumed on use.";
			m_abilityEffects.at(abilityName).push_back(effect1);

			
			break;
		case abilityBudgetMenuBeverage:

			effect1.descFirst = "Heals your hero for";
			effect1.m_number = "100";
			effect1.m_type = "Health points";
			effect1.descSecond = ". Can be reused.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilityRideBike:
			effect1.descFirst = "Gives you a movespeed buff with some drawbacks";
			effect1.m_number = "";
			effect1.m_type = "";
			effect1.descSecond = "";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilityCosmicSpaghetti:

			effect1.descFirst = "fires a ball of spaghettti dealing";
			effect1.m_number = "100%";
			effect1.m_type = "Cat Voodoo";
			effect1.descSecond = "damage to the target.";
			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilityHuntOfTheHaunted: 
			
			effect1.descFirst = "releases three pet ghosts which deal";
			effect1.m_number = "100%";
			effect1.m_type = "Cat Voodoo";
			effect1.descSecond = "damage upon finding a nearby target.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilitySpookySpaceMeringue:
			

			effect1.descFirst = "places a trap which deals";
			effect1.m_number = "150%";
			effect1.m_type = "Cat Voodoo";
			effect1.descSecond = "damage when triggered by an opponent.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			effect2.descFirst = "When triggered, a ";
			effect2.m_number = "67%";
			effect2.m_type = "Movespeed";
			effect2.descSecond = "slow is applied to the target.";

			m_abilityEffects.at(abilityName).push_back(effect2);

			break;
		case abilityTheSlurpening:
			
			effect1.descFirst = "slurps a target dealing";
			effect1.m_number = "100%";
			effect1.m_type = "Cat Vooodoo";
			effect1.descSecond = "to the target";

			m_abilityEffects.at(abilityName).push_back(effect1);


			effect2.descFirst = "and healing yourself for";
			effect2.m_number = "50%";
			effect2.m_type = "Cat Voodoo";
			effect2.descSecond = "power for 10 seconds.";

			m_abilityEffects.at(abilityName).push_back(effect2);

			break;
		case abilityAntiFireball: 
			effect1.descFirst = "A Spamfireghettiball hurdles towards the poor unsuspecting newb dealing";
			effect1.m_number = "200%";
			effect1.m_type = "physical damage";
			effect1.descSecond = "to them.";
			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilityMotoBoost: 
			
			effect1.descFirst = "gives you a boost of ";
			effect1.m_number = "20";
			effect1.m_type = "Movespeed";
			effect1.descSecond = "for upto 5 seconds (an on collision debuff will apply).";

			m_abilityEffects.at(abilityName).push_back(effect1);


			effect2.descFirst = "Collision with an opponent ends your move speed and deals";
			effect2.m_number = "100%";
			effect2.m_type = "Physical";
			effect2.descSecond = "damage.";

			m_abilityEffects.at(abilityName).push_back(effect2);

			break;
		case abilityEternalLight:

			effect1.descFirst = "gives nearby players";
			effect1.m_number = "100%";
			effect1.m_type = "CatVoodoo";
			effect1.descSecond = "as health over 10 seconds.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;
		case abilityElixirBurst:

			effect1.descFirst = " is thrown giving nearby players";
			effect1.m_number = "30%";
			effect1.m_type = "Missing Health";
			effect1.descSecond = "over 5 seconds.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;

		case abilityHiddenPower:

			effect1.descFirst = " all stats boosted";
			effect1.m_number = "";
			effect1.m_type = "";
			effect1.descSecond = "over 30 seconds.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;


		case abilityValiantLeap:

			effect1.descFirst = " you jump ";
			effect1.m_number = "4m";
			effect1.m_type = "";
			effect1.descSecond = "and can then fire your thing.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;


		case abilityHealTurret:

			effect1.descFirst = " give nearby team members ";
			effect1.m_number = " 60 ";
			effect1.m_type = " health/second";
			effect1.descSecond = " for the life of the turret.";

			m_abilityEffects.at(abilityName).push_back(effect1);

			break;



		}

		m_abilityTooltips.at(abilityName)->SetName(ability->GetName());
		m_abilityTooltips.at(abilityName)->SetEffects(&m_abilityEffects.at(abilityName));


		
	}

	m_abilityView->SetTooltip(m_abilityTooltips.at(abilityName));
	m_abilityView->SetEffects(&m_abilityEffects.at(abilityName));
	
	*abilityViewOut = m_abilityView;
	return true;
}