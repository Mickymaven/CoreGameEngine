#if !defined(ABILITYFACTORY_H)
#define ABILITYFACTORY_H

#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"//(forward dependency)
#include "../../../CoreGame/src/Gameplay/Abilities/AbilityName.h"//(forward dependency)

//Item Abilities
#include "../../../CoreGame/src/Gameplay/Abilities/NomBarHeal.h"
#include "../../../CoreGame/src/Gameplay/Abilities/BudgetMenuBeverage.h"
#include "../../../CoreGame/src/Gameplay/Abilities/RideBike.h"
#include "../../../CoreGame/src/Gameplay/Abilities/BasicAttack.h"
#include "../../../CoreGame/src/Gameplay/Abilities/Recall.h"
#include "../../../CoreGame/src/Gameplay/Abilities/ZZzzz.h"

//grey
#include "../../../CoreGame/src/Gameplay/Abilities/CosmicSpaghetti.h"
#include "../../../CoreGame/src/Gameplay/Abilities/HuntOfTheHaunted.h"
#include "../../../CoreGame/src/Gameplay/Abilities/SpookySpaceMeringue.h"
#include "../../../CoreGame/src/Gameplay/Abilities/TheSlurpening.h"

//Shork
#include "../../../CoreGame/src/Gameplay/Abilities/AntiFireball.h"
#include "../../../CoreGame/src/Gameplay/Abilities/MotoBoost.h"


#include "../../../CoreGame/src/Gameplay/Abilities/EternalLight.h"
#include "../../../CoreGame/src/Gameplay/Abilities/ElixirBurst.h"
#include "../../../CoreGame/src/Gameplay/Abilities/HiddenPower.h"

#include "../../../CoreGame/src/Gameplay/Abilities/ValiantLeap.h"

#include "../Item/Item.h"

class AbilityFactory
{
	Ability * m_constructedAbility;

public:

	AbilityFactory();
	~AbilityFactory();	

	bool ConstructAbility(Ability ** abilityOut, AbilityName ability,
		Actor * actor,
		vector<Actor*>* opponents,
		vector<Actor*>* playerTeam,
		vector<Actor*>* npctargets);

};


#endif