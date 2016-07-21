#if !defined(CHARACTERVIEWFACTORY_H)
#define CHARACTERVIEWFACTORY_H

#include "../../../EngineMoba/src/Actors/Character.h"
#include "../../../CoreGame/src/Gameplay/Characters/AbilitySlotType.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"
#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"
#include "../../../CoreGame/src/Gameplay/Abilities/AbilityName.h"
#include "../GameplayView/CharacterView.h"
#include "AbilityViewFactory.h"
#include "ActorViewFactory.h"

class CharacterViewFactory
{
protected:
	ActorViewFactory * m_actorViewFactory;
	AbilityViewFactory * m_abilityViewFactory;
	CharacterData m_data;


	
	//PlayerCharacterView ** m_characterView;
	//ActorView * m_actorView;


public:
	CharacterViewFactory();
	~CharacterViewFactory();

	bool Init(ActorViewFactory * actorViewFactory, AbilityViewFactory * abilityViewFactory);

	bool ConstructCharacterView(
		LPDIRECT3DDEVICE9 device,
		CharacterView ** characterViewOut,
		Character * character,
		const CharacterClassName characterClass,
		vector<AbilityName> * customAbilities
	);

	bool ConstructCharacterAbilityViews(
		LPDIRECT3DDEVICE9 device,
		vector<Ability*> * abilities,
		vector<AbilityView*> * abilityViews,
		CharacterClassName name,
		vector<AbilityName> * customAbilityList);



};

#endif